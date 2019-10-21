# PBRT 笔记

## @! GoogleLogging

此文件包含 #include 日志相关内容 的信息。

几乎每个文件都需要 #include 此文件，以便记录各种事件

关于 glog 的更多介绍参考 [glog](../src/ext/glog/doc/glog.html)

中文相关参考资料：

[google-glog 开源库分析(一)：glog介绍 - 天使的秘密](http://www.cnblogs.com/davidyang2415/p/3861109.html)

[google-glog 开源库分析(二)：glog用法 - 天使的秘密](http://www.cnblogs.com/davidyang2415/p/3861112.html)
[google-glog 开源库分析(三)：glog核心类结构 - 天使的秘密](http://www.cnblogs.com/davidyang2415/p/3861118.html)

[google-glog 开源库分析(四)：glog宏技巧 - 天使的秘密](http://www.cnblogs.com/davidyang2415/p/3861120.html)

[C++的开源跨平台日志库glog学习研究(一) - lizhenghn](http://www.cnblogs.com/lizhenghn/p/3704749.html)

[C++的开源跨平台日志库glog学习研究(二)--宏的使用 - lizhenghn](http://www.cnblogs.com/lizhenghn/archive/2014/05/03/3705410.html)

[C++的开源跨平台日志库glog学习研究(三)--杂项 - lizhenghn](
http://www.cnblogs.com/lizhenghn/p/3720508.html)

[如何使用Google日志库 (glog) - chenguangxing3的专栏](http://blog.csdn.net/chenguangxing3/article/details/17150069)

[glog使用与功能修改](http://www.cppfans.org/1566.html)

[glog多线程下按照指定条件创建新的日志文件 - lijingpeng的专栏](
http://blog.csdn.net/lijingpengchina/article/details/9050539)

[window环境下glog的安装 - lijingpeng的专栏](http://blog.csdn.net/lijingpengchina/article/details/9047777)

[google glog 简单使用小结](https://www.jianshu.com/p/762b9602e07b)

[Google glog 使用](https://www.cnblogs.com/zhoug2020/p/5884598.html)



## @! 32-bits

构建的 32-bits 的pbrt 程序，在渲染高复杂度的场景时可能会Crash



## @! options 

用-help的命令参数运行pbrt.exe，可以看到所有pbrt程序可指定的参数

## @? Tokenizer



##  @? MemoryArena

pbrt 提供了MemoryArena 类来实现基于区域的分配。它支持从Arena进行大小可变的分配。

该内存分配的优势有：1、分配非常快，通常只需要增加一个指针；2、它可以改善引用的局部性，减少缓存丢失。因为分配的对象在内存中是连续的。更通用的动态内存分配器通常会为它返回的每个块预先准备一个 bookkeeping 结构体，这对引用的局部性有不利影响。

## @? GraphicsState 

http://www.pbr-book.org/3ed-2018/Scene_Description_Interface/Scene_Definition.html#GraphicsState

GraphicsState 的 vector 用作堆栈来执行分层状态管理。调用`pbrtAttributeBegin()`时，将复制当前GraphicsState将其推入次堆栈。然后，`pbrtAttributeEnd()`将从该堆栈弹出状态。

