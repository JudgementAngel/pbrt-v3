# C++知识点笔记

##### @cpp usage 

usage()一般是程序里自定义来提示用户怎么使用程序的。是一个自定义函数。



##### @cpp #include尖括号和双引号的区别

采用< >方式，表示让编译器在编译器的预设标准路径下去搜索相应的头文件，如果找不到则报错。

采用" "方式，表示先在工程所在路径下搜索，如果失败，再到系统标准路径下搜索。

所以，特别要注意的是，如果是标准库头文件，那么既可以采用<>的方式，又可以采用" "的方式，而用户自定义的头文件只能采用" "的方式。

例如，这两种方式都是正确的：`#include <iostream>`效率较高 `#include "iostream"` 效率较低



##### @cpp extern

extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义。此外extern也可用来进行链接指定。

参考：[C/C++中extern关键字详解](https://www.cnblogs.com/yuxingli/p/7821102.html)



##### @cpp NDEBUG

NDEBUG宏定义可以影响assert的行为，这个默认是没被定义的。当我们宏定义了NDEBUG，就屏蔽掉了assert的功能

我们可以使用一个#define语句定义NDEBUG，从而关闭调试状态。



##### @cpp fflush

此函数包含在stdio.h头文件中，用来强制将缓冲区中的内容写入文件。
函数原型：int fflush(FILE *stream) ;
函数功能：清除一个流，即清除文件缓冲区，当文件以写方式打开时，将缓冲区内容写入文件。也就是说，对于ANSI C规定的是缓冲文件系统，函数fflush用于将缓冲区的内容输出到文件中去。
函数返回值：如果成功刷新，fflush返回0。指定的流没有缓冲区或者只读打开时也返回0值。返回EOF指出一个错误。

`fflush(stdin)` 清理标准输入流，把多余的未被保存的数据丢掉

`fflush(stdout)` 清空输出缓冲区，并把缓冲区内容输出。对标准输出流的清理，但是它并不是把数据丢掉，而是及时地打印数据到屏幕上。标准输出是以行为单位进行的，也即碰到\n才打印数据到屏幕。这就可能造成延时,但是Windows平台上，似乎并看不出差别来。

fflush函数被广泛使用在多线程、网络编程的消息处理中



##### @cpp? unique_ptr

unique_ptr <>是c ++ 11提供的智能指针实现之一，用于防止内存泄漏。unique_ptr对象包含一个原始指针，并负责其生命周期。当这个对象被销毁的时候，它的析构函数会删除关联的原始指针。
unique_ptr有重载的- >和*运算符，所以它可以被用于类似于普通的指针。

`unique_ptr::reset(p)`是销毁由unique_ptr 当前管理的对象（如果有），并获取 p的所有权



##### @cpp `_MAX_***`

```c++
#define _MAX_PATH   260
#define _MAX_DRIVE  3
#define _MAX_DIR    256
#define _MAX_FNAME  256
#define _MAX_EXT    256
```

| 常数 | 值   | 说明 |
| ---- | ---- | ---- |
|`_MAX_PATH`|260|完整的路径和文件名，例如 "D:\\Victor Chen\\Programs\\FileName.cpp"|
|`_MAX_DRIVE`|3|驱动器名加冒号，例如 L"D:"|
|`_MAX_DIR`|256|路径，用反斜线分割的文件夹名的路径，包括前后反斜线，例如 "\\Victor Chen\\Programs\\"|
|`_MAX_FNAME`|256|文件名，例如 "FileName"|
|`_MAX_EXT`|256|后缀 (扩展名)，包括前面的小数点，例如 ".exe"|

注：Windows 允许超过 260 长度的路径和文件名，在路径前面加上 L"\\\\?\\" 前缀，最多可达到 32,000 个字符，
例如：L"\\\\?\\D:\\Victor Chen\\Programs\\FileName.cpp"



##### @cpp _splitpath_s

官方文档： [\_splitpath\_s、\_wsplitpath\_s](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/reference/splitpath-s-wsplitpath-s?view=vs-2019)

需要的头文件是:`<stdlib.h>`

函数原型如下：

```c
void _splitpath( const char *path, char *drive, char *dir, char *fname, char *ext);
```

*path*
完整路径。

*drive*
驱动器号，后跟冒号（ **：** ）。 如果不需要驱动器号，则可以为此参数传递**NULL** 。

*dir*
目录路径，包括尾部反斜杠。 可以使用正 **/** 斜杠（）、 **\\** 反斜杠（）或两者。 如果不需要目录路径，则可以为此参数传递**NULL** 。

*fname*
基文件名（无扩展名）。 如果不需要文件名，则可以为此参数传递**NULL** 。

*ext*
文件扩展名，包括前导句点（ **.** ）。 如果不需要文件扩展名，则可为此参数传递**NULL** 。

**_Splitpath**函数将路径分解为四个组件。 **_splitpath**会根据需要自动处理多字节字符串参数，根据当前使用的多字节代码页识别多字节字符序列。 **_wsplitpath**是 **_splitpath**的宽字符版本; **_wsplitpath**的参数是宽字符字符串。 否则这些函数具有相同行为。

对于不需要的*path*以外的任何参数，可以将**NULL**传递给 **_splitpath** 。

如果*path*为**NULL**，则将调用无效参数处理程序，如[参数验证](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/parameter-validation?view=vs-2019)中所述。 如果允许执行继续，则将**errno**设置为**EINVAL** ，并且函数将返回**EINVAL**。



##### @cpp errno

[errno、_doserrno、\_sys\_errlist 和\_sys\_nerr](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/errno-doserrno-sys-errlist-and-sys-nerr?view=vs-2019)

errno 在程序执行过程中设置的保存错误代码的全局宏，以及用于显示的错误代码的等效字符串

需要包含 `#include <errno.h>`

errno 值是在出现各种错误条件时分配给 [errno](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/errno-doserrno-sys-errlist-and-sys-nerr?view=vs-2019) 的常量。



##### @cpp _makepath_s

[\_makepath\_s、\_wmakepath\_s](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/reference/makepath-s-wmakepath-s?view=vs-2019)

从组件中创建新的路径名



##### @cpp 左值和右值

参考 ：[理解C和C++中的左值和右值](https://blog.csdn.net/xuwqiang1994/article/details/79924310)

左值 lvalue(locator value)代表一个在内存中占有确定位置的对象（即，有一个地址）

右值 rvalue 通过排他性定义，每个表达式不是lvalue就是rvalue。因此，rvalue 是不在内存中占有确定位置的表达式



