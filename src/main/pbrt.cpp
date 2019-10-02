
/*
版权声明：
    pbrt source code is Copyright(c) 1998-2016
                        Matt Pharr, Greg Humphreys, and Wenzel Jakob.

    This file is part of pbrt.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    - Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.

    - Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */


// main/pbrt.cpp*
#include "pbrt.h"
#include "api.h"
#include "parser.h"
#include "parallel.h"
#include <glog/logging.h>

using namespace pbrt;

// @cpp usage
static void usage(const char *msg = nullptr) {
    if (msg)
        fprintf(stderr, "pbrt: %s\n\n", msg);

    fprintf(stderr, R"(usage: pbrt [<options>] <filename.pbrt...>
Rendering options:
渲染设置：
  --cropwindow <x0,x1,y0,y1> Specify an image crop window. 指定图像裁剪窗口
  --help               Print this help text. 打印帮助文本，即这条信息
  --nthreads <num>     Use specified number of threads for rendering. 
						指定渲染使用的线程数
  --outfile <filename> Write the final image to the given filename. 
						写入最终的图像到给定的文件，默认在pbrt.exe的目录
  --quick              Automatically reduce a number of quality settings to
                       render more quickly. 自动减少一些质量设置以更快地渲染。
  --quiet              Suppress all text output other than error messages. 
						禁止显示除错误消息以外的所有文本输出。						

Logging options:
日志信息设置：
  --logdir <dir>       Specify directory that log files should be written to.
						指定一个log文件的输出路径
                       Default: system temp directory (e.g. $TMPDIR or /tmp).
						默认：系统的temp目录（例如 $TMPDIR 或 /tmp）
  --logtostderr        Print all logging messages to stderr.
						打印所有的日志信息到 stderr
  --minloglevel <num>  Log messages at or above this level (0 -> INFO,
                       1 -> WARNING, 2 -> ERROR, 3-> FATAL). Default: 0.
						记录大于或等于这个等级的日志信息
						0 -> 普通，1 -> 警告，2 -> 错误，3 -> 致命，默认为 0
  --v <verbosity>      Set VLOG verbosity. 设置VLOG的详细程度

Reformatting options:
重新格式化设置：
  --cat                Print a reformatted version of the input file(s) to
                       standard output. Does not render an image.
						将输入文件的重新格式化版本打印到标准输出。 不渲染图像。
  --toply              Print a reformatted version of the input file(s) to
                       standard output and convert all triangle meshes to
                       PLY files. Does not render an image.
						将输入文件的重新格式化版本打印到标准输出，
						并将所有三角形网格转换为PLY文件。 不渲染图像。
)");
    exit(msg ? 1 : 0);
}

// 主程序入口
// main program
int main(int argc, char *argv[]) {
	// @! GoogleLogging
    google::InitGoogleLogging(argv[0]); // 初始化google的日志记录库
    FLAGS_stderrthreshold = 1; // Warning and above. // 级别 大于等于 此标志 的日志消息除了日志文件外，还会自动发送到stderr

	// @! options
    Options options; // 根据命令参数设置的PBRT选项
    std::vector<std::string> filenames; // 存放用于渲染的场景文件的绝对路径
    
	// 解析命令行参数，填充上面的option结构体 和 filenames
	// Process command-line arguments
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "--nthreads") || !strcmp(argv[i], "-nthreads")) {
            if (i + 1 == argc)
                usage("missing value after --nthreads argument");
            options.nThreads = atoi(argv[++i]);
        } else if (!strncmp(argv[i], "--nthreads=", 11)) {
            options.nThreads = atoi(&argv[i][11]);
        } else if (!strcmp(argv[i], "--outfile") || !strcmp(argv[i], "-outfile")) {
            if (i + 1 == argc)
                usage("missing value after --outfile argument");
            options.imageFile = argv[++i];
        } else if (!strcmp(argv[i], "--cropwindow") || !strcmp(argv[i], "-cropwindow")) {
            if (i + 4 >= argc)
                usage("missing value after --cropwindow argument");
            options.cropWindow[0][0] = atof(argv[++i]);
            options.cropWindow[0][1] = atof(argv[++i]);
            options.cropWindow[1][0] = atof(argv[++i]);
            options.cropWindow[1][1] = atof(argv[++i]);
        } else if (!strncmp(argv[i], "--outfile=", 10)) {
            options.imageFile = &argv[i][10];
        } else if (!strcmp(argv[i], "--logdir") || !strcmp(argv[i], "-logdir")) {
            if (i + 1 == argc)
                usage("missing value after --logdir argument");
            FLAGS_log_dir = argv[++i];
        } else if (!strncmp(argv[i], "--logdir=", 9)) {
            FLAGS_log_dir = &argv[i][9];
        } else if (!strcmp(argv[i], "--minloglevel") ||
                   !strcmp(argv[i], "-minloglevel")) {
            if (i + 1 == argc)
                usage("missing value after --minloglevel argument");
            FLAGS_minloglevel = atoi(argv[++i]);
        } else if (!strncmp(argv[i], "--minloglevel=", 14)) {
            FLAGS_minloglevel = atoi(&argv[i][14]);
        } else if (!strcmp(argv[i], "--quick") || !strcmp(argv[i], "-quick")) {
            options.quickRender = true;
        } else if (!strcmp(argv[i], "--quiet") || !strcmp(argv[i], "-quiet")) {
            options.quiet = true;
        } else if (!strcmp(argv[i], "--cat") || !strcmp(argv[i], "-cat")) {
            options.cat = true;
        } else if (!strcmp(argv[i], "--toply") || !strcmp(argv[i], "-toply")) {
            options.toPly = true;
        } else if (!strcmp(argv[i], "--v") || !strcmp(argv[i], "-v")) {
            if (i + 1 == argc)
                usage("missing value after --v argument");
            FLAGS_v = atoi(argv[++i]);
        } else if (!strncmp(argv[i], "--v=", 4)) {
          FLAGS_v = atoi(argv[i] + 4);
        }
        else if (!strcmp(argv[i], "--logtostderr")) {
          FLAGS_logtostderr = true;
        } else if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-help") ||
                   !strcmp(argv[i], "-h")) {
            usage();
            return 0;
        } else
            filenames.push_back(argv[i]);
    }

	// 打印欢迎横幅
    // Print welcome banner
    if (!options.quiet && !options.cat && !options.toPly) {
        // #@!['32-bits']
		if (sizeof(void *) == 4)
            printf("*** WARNING: This is a 32-bit build of pbrt. It will crash "
                   "if used to render highly complex scenes. ***\n");
        printf("pbrt version 3 (built %s at %s) [Detected %d cores]\n",
               __DATE__, __TIME__, NumSystemCores());
// @cpp NDEBUG
#ifndef NDEBUG
		// @?  GoogleLOG 和 Printf的区别
        LOG(INFO) << "Running debug build";
        printf("*** DEBUG BUILD ***\n");
#endif // !NDEBUG
        printf(
            "Copyright (c)1998-2018 Matt Pharr, Greg Humphreys, and Wenzel "
            "Jakob.\n");
        printf(
            "The source code to pbrt (but *not* the book contents) is covered "
            "by the BSD License.\n");
        printf("See the file LICENSE.txt for the conditions of the license.\n");
        fflush(stdout); // @cpp fflush
    }
	// 使用options 初始化 pbrt
    pbrtInit(options);

	// 处理场景描述
	// 这里是主循环的入口，跑完这里意味着渲染结束
    // Process scene description
    if (filenames.empty()) {
		// 从标准输入解析场景
        // Parse scene from standard input
        pbrtParseFile("-");
    } else {
		// 从输入的文件解析场景
        // Parse scene from input files
        for (const std::string &f : filenames)
            pbrtParseFile(f);
    }
    pbrtCleanup(); // pbrt相关清理工作
    return 0;
}
