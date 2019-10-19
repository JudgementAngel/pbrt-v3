# C++知识点笔记

## @cpp usage 

usage()一般是程序里自定义来提示用户怎么使用程序的。是一个自定义函数。



## @cpp #include尖括号和双引号的区别

采用< >方式，表示让编译器在编译器的预设标准路径下去搜索相应的头文件，如果找不到则报错。

采用" "方式，表示先在工程所在路径下搜索，如果失败，再到系统标准路径下搜索。

所以，特别要注意的是，如果是标准库头文件，那么既可以采用<>的方式，又可以采用" "的方式，而用户自定义的头文件只能采用" "的方式。

例如，这两种方式都是正确的：`#include <iostream>`效率较高 `#include "iostream"` 效率较低



## @cpp extern

extern可以置于变量或者函数前，以标示变量或者函数的定义在别的文件中，提示编译器遇到此变量和函数时在其他模块中寻找其定义。此外extern也可用来进行链接指定。

参考：[C/C++中extern关键字详解](https://www.cnblogs.com/yuxingli/p/7821102.html)



## @cpp NDEBUG

NDEBUG宏定义可以影响assert的行为，这个默认是没被定义的。当我们宏定义了NDEBUG，就屏蔽掉了assert的功能

我们可以使用一个#define语句定义NDEBUG，从而关闭调试状态。



## @cpp fflush

此函数包含在stdio.h头文件中，用来强制将缓冲区中的内容写入文件。
函数原型：int fflush(FILE *stream) ;
函数功能：清除一个流，即清除文件缓冲区，当文件以写方式打开时，将缓冲区内容写入文件。也就是说，对于ANSI C规定的是缓冲文件系统，函数fflush用于将缓冲区的内容输出到文件中去。
函数返回值：如果成功刷新，fflush返回0。指定的流没有缓冲区或者只读打开时也返回0值。返回EOF指出一个错误。

`fflush(stdin)` 清理标准输入流，把多余的未被保存的数据丢掉

`fflush(stdout)` 清空输出缓冲区，并把缓冲区内容输出。对标准输出流的清理，但是它并不是把数据丢掉，而是及时地打印数据到屏幕上。标准输出是以行为单位进行的，也即碰到\n才打印数据到屏幕。这就可能造成延时,但是Windows平台上，似乎并看不出差别来。

fflush函数被广泛使用在多线程、网络编程的消息处理中



## @cpp? unique_ptr

unique_ptr <>是c ++ 11提供的智能指针实现之一，用于防止内存泄漏。unique_ptr对象包含一个原始指针，并负责其生命周期。当这个对象被销毁的时候，它的析构函数会删除关联的原始指针。
unique_ptr有重载的- >和*运算符，所以它可以被用于类似于普通的指针。

`unique_ptr::reset(p)`是销毁由unique_ptr 当前管理的对象（如果有），并获取 p的所有权



## @cpp `_MAX_***`

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



## @cpp _splitpath_s

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



## @cpp errno

[errno、_doserrno、\_sys\_errlist 和\_sys\_nerr](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/errno-doserrno-sys-errlist-and-sys-nerr?view=vs-2019)

errno 在程序执行过程中设置的保存错误代码的全局宏，以及用于显示的错误代码的等效字符串

需要包含 `#include <errno.h>`

errno 值是在出现各种错误条件时分配给 [errno](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/errno-doserrno-sys-errlist-and-sys-nerr?view=vs-2019) 的常量。



## @cpp _makepath_s

[\_makepath\_s、\_wmakepath\_s](https://docs.microsoft.com/zh-cn/cpp/c-runtime-library/reference/makepath-s-wmakepath-s?view=vs-2019)

从组件中创建新的路径名



## @cpp 左值和右值

参考 ：[理解C和C++中的左值和右值](https://blog.csdn.net/xuwqiang1994/article/details/79924310)

左值 lvalue(locator value)代表一个在内存中占有确定位置的对象（即，有一个地址）

右值 rvalue 通过排他性定义，每个表达式不是lvalue就是rvalue。因此，rvalue 是不在内存中占有确定位置的表达式



## @cpp EOF

EOF是一个计算机术语，为End Of File的缩写，在操作系统中表示资料源无更多的资料可读取。资料源通常称为档案或串流。通常在文本的最后存在此字符表示资料结束。

在Doc窗口中 ctrl+z 输入文件结束标志



## @cpp push_back

string::push_back 表示在字符串末尾再添加 单个字符



## @cpp? C++11 引用折叠



## @cpp? std::move()

[C++11 std::move和std::forward](https://www.jianshu.com/p/b90d1091a4ff)

`std::move`和`std::forward`本质就是一个转换函数，`std::move`执行到右值的无条件转换，`std::forward`执行到右值的有条件转换，在参数都是右值时，二者就是等价的。

其实std::move和std::forward就是在C++11基本规则之上封装的语法糖。

```c++
class Foo
{
public:
    std::string member;

    // Copy member.
    Foo(const std::string& m): member(m) {}

    // Move member.
    Foo(std::string&& m): member(std::move(m)) {}
};
```

上述`Foo(std::string&& member)`中的member是rvalue reference，但是member却是一个左值lvalue，因此在初始化列表中需要使用`std::move`将其转换成rvalue。

标准库中`move`的定义如下：

```C++
template<typename T>
typename remove_reference<T>::type && move(T&& t)
{
    return static_cast<typename remove_reference<T>::type &&>(t);
}
```



##### @cpp 默认函数default

[c++11 类默认函数的控制："=default" 和 "=delete"函数](https://www.cnblogs.com/lsgxeva/p/7787438.html)

```c++
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>
#include <map>

//c++11 类默认函数的控制："=default" 和 "=delete"函数

/*
C++ 的类有四类特殊成员函数，它们分别是：默认构造函数、析构函数、拷贝构造函数以及拷贝赋值运算符。
这些类的特殊成员函数负责创建、初始化、销毁，或者拷贝类的对象。
如果程序员没有显式地为一个类定义某个特殊成员函数，而又需要用到该特殊成员函数时，则编译器会隐式的为这个类生成一个默认的特殊成员函数。
*/

// C++11 标准引入了一个新特性："=default"函数。程序员只需在函数声明后加上“=default;”，就可将该函数声明为 "=default"函数，编译器将为显式声明的 "=default"函数自动生成函数体。
class X
{ 
public: 
    X() = default; //该函数比用户自己定义的默认构造函数获得更高的代码效率
    X(int i)
    { 
        a = i; 
    }

private: 
    int a; 
}; 

X obj;

// "=default"函数特性仅适用于类的特殊成员函数，且该特殊成员函数没有默认参数。
class X1
{
public:
    int f() = default;      // err , 函数 f() 非类 X 的特殊成员函数
    X1(int, int) = default;  // err , 构造函数 X1(int, int) 非 X 的特殊成员函数
    X1(int = 1) = default;   // err , 默认构造函数 X1(int=1) 含有默认参数
};

// "=default"函数既可以在类体里（inline）定义，也可以在类体外（out-of-line）定义。
class X2
{
public:
    X2() = default; //Inline defaulted 默认构造函数
    X2(const X&);
    X2& operator = (const X&);
    ~X2() = default;  //Inline defaulted 析构函数
};

X2::X2(const X&) = default;  //Out-of-line defaulted 拷贝构造函数
X2& X2::operator= (const X2&) = default;   //Out-of-line defaulted  拷贝赋值操作符


// 为了能够让程序员显式的禁用某个函数，C++11 标准引入了一个新特性："=delete"函数。程序员只需在函数声明后上“=delete;”，就可将该函数禁用。
class X3
{
public:
    X3();
    X3(const X3&) = delete;  // 声明拷贝构造函数为 deleted 函数
    X3& operator = (const X3 &) = delete; // 声明拷贝赋值操作符为 deleted 函数
};

// "=delete"函数特性还可用于禁用类的某些转换构造函数，从而避免不期望的类型转换
class X4
{
public:
    X4(double)
    {

    }

    X4(int) = delete;
};

// "=delete"函数特性还可以用来禁用某些用户自定义的类的 new 操作符，从而避免在自由存储区创建类的对象
class X5
{
public:
    void *operator new(size_t) = delete;
    void *operator new[](size_t) = delete;
};


void mytest()
{
    X4 obj1;
    X4 obj2=obj1;   // 错误，拷贝构造函数被禁用

    X4 obj3;
    obj3=obj1;     // 错误，拷贝赋值操作符被禁用

    X5 *pa = new X5;      // 错误，new 操作符被禁用
    X5 *pb = new X5[10];  // 错误，new[] 操作符被禁用

    return;
}


int main()
{
    mytest();

    system("pause");
    return 0;
}
```



## @cpp? C++11 lambda

[Lambda expressions](https://en.cppreference.com/w/cpp/language/lambda)

[Under the hood of lambdas and std::function](https://shaharmike.com/cpp/lambdas-and-functions/)

C++ 11 中的 Lambda 表达式用于定义并创建匿名的函数对象，以简化编程工作。
Lambda 的语法形式如下：

```C++
[函数对象参数] (操作符重载函数参数) mutable 或 exception 声明 -> 返回值类型 {函数体}
```

可以看到，Lambda 主要分为五个部分：[函数对象参数]、(操作符重载函数参数)、mutable 或 exception 声明、-> 返回值类型、{函数体}.

`[&](){i=0;j=0;}`是一个lambda，它捕获`i`和`j`作为参考。`[&]`表示“通过引用捕获函数中正在使用的所有变量”



## @cpp LPSTR

Long Pointer String 

LPSTR和LPWSTR是 Win32 和 VC++ 所使用的一种字符串数据类型。LPSTR被定义成是一个指向以NULL(‘\0’)结尾的32位ANSI 字符 数组指针，而LPWSTR是一个指向以NULL结尾的64位双字节字符数组指针。CString与LPSTR转换。

参考[cstring、string、lpwstr、lpstr、char*之间相互转换](https://blog.csdn.net/xiake001/article/details/79899065)



## @cpp FormatMessageA

[FormatMessageA function](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-formatmessagea)

格式化消息字符串。该功能需要消息定义作为输入。

消息定义可以来自传递给函数的缓冲区。 它可以来自已加载模块中的消息表资源。

或者，调用者可以要求函数在系统的消息表资源中搜索消息定义。

 该函数根据消息标识符和语言标识符在消息表资源中找到消息定义。

 该函数将格式化的消息文本复制到输出缓冲区，如果需要，则处理所有嵌入的插入序列。

```C++
DWORD FormatMessageA(
  DWORD   dwFlags,
  LPCVOID lpSource,
  DWORD   dwMessageId,
  DWORD   dwLanguageId,
  LPSTR   lpBuffer,
  DWORD   nSize,
  va_list *Arguments
);
```

`dwFlags`：格式化选项，以及如何解释`LpSood`参数。`dwflags`的低位字节指定函数如何处理输出缓冲区中的换行符。低阶字节还可以指定格式化输出线的最大宽度。

`lpSource`： 消息定义的位置。此参数的类型取决于dwflags参数中的设置。如果在`dwflags`中未设置这两个标志，则忽略`lpsource`。

`dwMessageId`：所请求消息的消息标识符。 如果`dwFlags`包含**`FORMAT_MESSAGE_FORM_STRING`**，则忽略此参数

`dwLanguageId`：请求消息的语言标识符。如果`dwFlags`包含**`FORMAT_MESSAGE_FORM_STRING`**，则忽略此参数

`lpBuffer`：指向缓冲区的指针，该缓冲区接收以null为终止的字符串，该字符串指定格式化的西信息。如果`dwflags`包含**`FORMAT_MESSAGE_ALLOCATE_BUFFER`**，则函数使用`localalloc`函数分配缓冲区，并将指向缓冲区的指针放在lpbuffer中指定的地址。

该缓冲区不能大于64K字节。

`nSize`：如果未设置**`FORMAT_MESSAGE_ALLOCATE_BUFFER`**标志，则此参数以**`TCHARs`**指定输出缓冲区的大小。 如果设置了**`FORMAT_MESSAGE_ALLOCATE_BUFFER`**，则此参数指定分配给输出缓冲区的最小**`TCHAR`**数。

该输出缓冲区不能大于64K字节。

`Arguments`：值数组，用作格式化消息中的插入值。格式字符串中的％1表示Arguments数组中的第一个值； ％2表示第二个参数； 等等。

每个值的解释取决于与消息定义中的插入关联的格式信息。 默认值是将每个值都视为指向以空字符结尾的字符串的指针。

默认情况下，Arguments参数的类型为va_list *，这是一种语言和实现特定的数据类型，用于描述可变数量的参数。 从函数返回时，va_list参数的状态未定义。 要再次使用va_list，请使用va_end销毁变量参数列表指针，然后使用va_start对其进行初始化。

如果没有类型为va_list *的指针，则指定FORMAT_MESSAGE_ARGUMENT_ARRAY标志并将指针传递给DWORD_PTR值数组； 这些值被输入到格式化为插入值的消息中。 每个插入在数组中必须有一个对应的元素。

**返回值**

如果函数成功，则返回值是存储在输出缓冲区中的TCHAR数量，不包括终止的空字符。

如果函数失败，则返回值为零。 要获取扩展的错误信息，请调用[GetLastError](https://docs.microsoft.com/zh-cn/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror)。



## @cpp GetLastError

[GetLastError](https://docs.microsoft.com/zh-cn/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror)

检索调用线程的最后一个错误代码值。最后错误代码是基于每个线程维护的。多个线程不会覆盖彼此的最后错误代码。



##  @cpp LocalFree function

[LocalFree function](https://docs.microsoft.com/zh-cn/windows/win32/api/winbase/nf-winbase-localfree?redirectedfrom=MSDN)

释放指定的本地内存对象并使其句柄无效。

注意local functions 比其他内存管理功能具有更大的开销并提供更少的功能。 除非文档指出应使用local function，否则新应用程序应使用堆函数[heap functions](https://docs.microsoft.com/windows/desktop/Memory/heap-functions) 。 有关更多信息，请参见全局和局部函数 [Global and Local Functions](https://docs.microsoft.com/windows/desktop/Memory/global-and-local-functions)。



## @cpp string::c_str()

`c_str()` 返回一个指向正规C字符串的指针常量，该指针保证指向一个 `size() + 1` 长度的空间，而且最后一个字符肯定是 `\0` ；

而 `data()` 返回的指针则保证指向一个`size()`长度的空间，不保证有没有null-terminate，可能有，可能没有，看库的实现了。



## @cpp CreateFileA

[CreateFileA function](https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea)

创建或打开 一个文件或I/O设备。

 最常用的I / O设备如下：文件，文件流，目录，物理磁盘，卷，控制台缓冲区，磁带驱动器，通信资源，邮筒和管道。 

该函数返回一个句柄，根据文件或设备以及指定的标志和属性，该句柄可用于访问各种类型的I / O的文件或设备。

要将此操作作为事务处理操作执行，从而产生可用于事务处理I / O的句柄，请使用CreateFileTransacted函数。



## @cpp LARGE_INTEGER

[LARGE_INTEGER union](https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-large_integer~r1)

表示64位有符号整数值。

注意您的C编译器可能本地支持64位整数。 例如，Microsoft Visual C ++支持__int64大小的整数类型。 有关更多信息，请参见C编译器随附的文档。

**LARGE_INTEGER**结构实际上是一个联合。 如果您的编译器具有对64位整数的内置支持，请使用**QuadPart**成员存储64位整数。 否则，请使用**LowPart**和**HighPart**成员存储64位整数。





## @cpp GetFileSizeEx

[GetFileSizeEx function](https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesizeex)

检索指定文件的大小

```C++
BOOL GetFileSizeEx(
  HANDLE         hFile,
  PLARGE_INTEGER lpFileSize
);
```

`hFile` ：文件的句柄。 必须已使用**`FILE_READ_ATTRIBUTES`**访问权限或等效访问权限创建了该句柄，否则调用方必须对包含该文件的目录具有足够的权限。

`lpFileSize`：指向[LARGE_INTEGER](https://docs.microsoft.com/windows/win32/api/winnt/ns-winnt-large_integer~r1)结构的指针，该结构接收文件大小（以字节为单位）。



如果函数成功，则返回值为非零。

如果函数失败，则返回值为零。要获取扩展错误信息，请调用GetLasterror。



## @cpp size_t

size_t是标准C库中定义的，应为unsigned int，在64位系统中为 long unsigned int。

使用size_t可能会提高代码的可移植性、有效性或者可读性，或许同时提高这三者。

[size_t](https://blog.csdn.net/fanhaifeng66/article/details/52168157)



## @cpp CreateFileMapping

[Creating a File Mapping Object](https://docs.microsoft.com/en-us/windows/win32/memory/creating-a-file-mapping-object)

[CreateFileMappingA function](https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga)

为指定文件 创建或打开 命名或未命名文件映射对象。



## @cpp MapViewOfFile

[MapViewOfFile function](https://docs.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-mapviewoffile)

将文件映射的视图映射到调用进程的地址空间

如果函数成功，则返回值是映射视图的起始地址。

如果函数失败，则返回值为**NULL**。要获取扩展的错误信息，请调用[GetLastError](https://docs.microsoft.com/windows/desktop/api/errhandlingapi/nf-errhandlingapi-getlasterror)。



## @cpp vector

[std::vector简介及其使用](https://www.cnblogs.com/leaves1024/p/10245688.html)

[std::vector](http://www.cplusplus.com/reference/vector/vector/)

```c++
template <class T，class Alloc = allocator <T> > class vector; //通用模板
```

C++11标准中的`std::vector`

vector是表示可以改变大小的数组的序列容器。就像数组一样，vector使用连续存储空间存储元素，这意味着它们的元素也可以使用指向其元素的指针进行偏移来访问，并与数组一样高效。但与数组不同的是， vector的大小可以动态变化，并且是由容器自动处理的。

在内部实现上，vector使用动态分配的数组来存储它们的元素。在插入新元素时，vector的大小增大，可能需要重新分配数组，这意味着可能要分配新数组并将原有数组中所有元素移动到这个新数组中。重新分配数组的时间成本相对高昂，因此，vector不会在每次向容器添加元素时都重新分配数组。vector容器可能会分配一些额外的存储空间来适应可能的增长，因此容器的实际容量可能比其包含的元素个数要大。不同库可以实现不同的增长策略以在使用现有内存和 重新分配内容之间取得平衡，但无论如何，重新分配内存时的数组大小应以对数增长，这样在vector末端插入单个元素时就可以得到平摊的常数时间复杂度。

　　因此，与数组相比，vector消耗更多内存，以换取以更有效的方式管理存储空间。

　　与其他动态序列容器（deques，lists和forward_lists）相比，vector可以非常高效地访问其元素（就像数组一样）并且相对高效地从其末尾添加或删除元素。 对于涉及在末尾以外的位置插入或删除元素的操作，性能比其他序列容器要差，并且与lists和forward_lists相比具有更少的迭代器和引用一致性。

### Member functions

[**(constructor)**](http://www.cplusplus.com/reference/vector/vector/vector/)  Construct vector (public member function ) 

[**(destructor)**](http://www.cplusplus.com/reference/vector/vector/~vector/) Vector destructor (public member function )

[**operator=**](http://www.cplusplus.com/reference/vector/vector/operator=/) Assign content (public member function )

**Iterators**

[**end**](http://www.cplusplus.com/reference/vector/vector/end/) Return iterator to end (public member function )

[**rbegin**](http://www.cplusplus.com/reference/vector/vector/rbegin/) Return reverse iterator to reverse beginning (public member function )

[**rend**](http://www.cplusplus.com/reference/vector/vector/rend/) Return reverse iterator to reverse end (public member function )

[**cbegin** ](http://www.cplusplus.com/reference/vector/vector/cbegin/) Return const_iterator to beginning (public member function )

[**cend** ](http://www.cplusplus.com/reference/vector/vector/cend/) Return const_iterator to end (public member function )

[**crbegin** ](http://www.cplusplus.com/reference/vector/vector/crbegin/) Return const_reverse_iterator to reverse beginning (public member function )

[**crend** ](http://www.cplusplus.com/reference/vector/vector/crend/) Return const_reverse_iterator to reverse end (public member function )

**Capacity**

[**max_size**](http://www.cplusplus.com/reference/vector/vector/max_size/) Return maximum size (public member function )

[**resize**](http://www.cplusplus.com/reference/vector/vector/resize/) Change size (public member function )

[**capacity**](http://www.cplusplus.com/reference/vector/vector/capacity/) Return size of allocated storage capacity (public member function )

[**empty**](http://www.cplusplus.com/reference/vector/vector/empty/) Test whether vector is empty (public member function )

[**reserve**](http://www.cplusplus.com/reference/vector/vector/reserve/) Request a change in capacity (public member function )

[**shrink_to_fit** ](http://www.cplusplus.com/reference/vector/vector/shrink_to_fit/) Shrink to fit (public member function )

**Element access**

[**at**](http://www.cplusplus.com/reference/vector/vector/at/) Access element (public member function )

[**front**](http://www.cplusplus.com/reference/vector/vector/front/) Access first element (public member function )

[**back**](http://www.cplusplus.com/reference/vector/vector/back/) Access last element (public member function )

[**data** ](http://www.cplusplus.com/reference/vector/vector/data/) Access data (public member function )

**Modifiers**

[**push_back**](http://www.cplusplus.com/reference/vector/vector/push_back/) Add element at the end (public member function )

[**pop_back**](http://www.cplusplus.com/reference/vector/vector/pop_back/) Delete last element (public member function )

[**insert**](http://www.cplusplus.com/reference/vector/vector/insert/) Insert elements (public member function )

[**erase**](http://www.cplusplus.com/reference/vector/vector/erase/) Erase elements (public member function )

[**swap**](http://www.cplusplus.com/reference/vector/vector/swap/) Swap content (public member function )

[**clear**](http://www.cplusplus.com/reference/vector/vector/clear/) Clear content (public member function )

[**emplace** ](http://www.cplusplus.com/reference/vector/vector/emplace/) Construct and insert element (public member function )

[**emplace_back** ](http://www.cplusplus.com/reference/vector/vector/emplace_back/) Construct and insert element at the end (public member function )

**Allocator**

[**relational operators**](http://www.cplusplus.com/reference/vector/vector/operators/) Relational operators for vector (function template )

[**swap**](http://www.cplusplus.com/reference/vector/vector/swap-free/) Exchange contents of vectors (function template )

### Template specializations

[**vector**](http://www.cplusplus.com/reference/vector/vector-bool/) Vector of bool (class template specialization )



## @cpp? std::function

[std::function](http://www.cplusplus.com/reference/functional/function/)

[std::function](https://en.cppreference.com/w/cpp/utility/functional/function?)

在C++11中，callable object 包括传统C函数，C++成员函数，函数对象（实现了（）运算符的类的实例），lambda表达式（特殊函数对象）共4种。程序设计，特别是程序库设计时，经常需要涉及到回调，如果针对每种不同的callable object单独进行声明类型，代码将会非常散乱，也不灵活。

将其当做`std::string`、`std::vector<>` 、这样的类型就可以了。只不过其值为函数指针，但比函数指针更灵活。因为`std::function`  是一种模板，所以要传入类型，就如`std::vector<int>`  传入类型`int`一样，不过,`std::function`传入的是函数类型  返回值 （参数类型） 如：`std::function<void (int)>`



## @cpp G1og Check宏

常做状态检查以尽早发现错误是一个很好的编程习惯。 `CHECK` 宏和标准库中的 `assert` 宏类似，可以在给定的条件不满足时终止程序。

`CHECK` 和 `assert` 不同的是，它不由 `NDEBUG` 控制，所以一直有效。因此下面的 `fp->Write(x)` 会一直执行：

```
CHECK(fp->Write(x) == 4) << "Write failed!";
```

有各种用于相等/不等检查的宏： `CHECK_EQ, CHECK_NE, CHECK_LE, CHECK_LT, CHECK_GE, CHECK_GT` 。它们比较两个值，在不满足期望时打印包括这两个值的 `FATAL` 日志。注意这里的值需要定义了 `operator<<(ostream, ...)` 。

比如：

```
CHECK_NE(1, 2) << ": The world must be ending!";
```

每个参数都可以保证只用一次，所以任何可以做为函数参数的都可以传给它。参数也可以是临时的表达式，比如：

```
CHECK_EQ(string("abc")[1], 'b');
```

如果一个参数是指针，另一个是 `NULL` ，编译器会报错。可以给 `NULL` 加上对应类型的 `static_cast` 来绕过。

```
CHECK_EQ(some_ptr, static_cast<SomeType*>(NULL));
```

更好的办法是用 `CHECK_NOTNULL` 宏：

```
CHECK_NOTNULL(some_ptr);
some_ptr->DoSomething();
```

该宏会返回传入的指针，因此在构造函数的初始化列表中非常有用。

```
struct S {
  S(Something* ptr) : ptr_(CHECK_NOTNULL(ptr)) {}
  Something* ptr_;
};
```

因为该特性，这个宏不能用作C++流。如果需要额外信息，请使用 `CHECK_EQ` 。

如果是需要比较C字符串（ `char*` ），可以用 `CHECK_STREQ, CHECK_STRNE, CHECK_STRCASEEQ, CHECK_STRCASENE` 。 `CASE` 的版本是不区分大小写的。这里可以传入 `NULL` 。 `NULL` 和任何非 `NULL` 的字符串是不等的，两个 `NULL` 是相等的。

这里的参数都可以是临时字符串，比如 `CHECK_STREQ(Foo().c_str(), Bar().c_str())` 。

`CHECK_DOUBLE_EQ` 宏可以用来检查两个浮点值是否等价，允许一点误差。 `CHECK_NEAR` 还可以传入第三个浮点参数，指定误差。



## @cpp /n/r 

[C++中回车换行（\n\r）和换行(\r)的区别](https://blog.csdn.net/xiaofei2010/article/details/8458605)

回车换行（`\n\r`）：每次光标移到下一行的行首位置处；

换行（`\r`）：每次光标移到本行的行首位置处。

```C++

#include <iostream>
using namespace std;
 
int main()
{
	cout << "this is the first line\n";
	cout << "this is the second line\r";
	cout << "this is the third line\n";
	cout << "this is the fouth line\r";
	cout << "this is the fifth line\n";
	cout << "end" ;
	return 0;
}
// 输出结果
/*
this is the first line
this is the third linee
this is the fifth line
*/
    
```

## @cpp constexpr

**constexpr**是[C++11](https://zh.wikipedia.org/wiki/C%2B%2B11)引入的[关键字](https://zh.wikipedia.org/wiki/關鍵字)，用于[编译时](https://zh.wikipedia.org/wiki/编译时)的常量与常量函数。

声明为constexpr函数的意义是：如果其参数均为合适的编译期常量，则对这个constexpr函数的调用就可用于期望常量表达式的场合（如模板的非类型参数，或枚举常量的值）。如果参数的值在运行期才能确定，或者虽然参数的值是编译期常量，但不匹配这个函数的要求，则对这个函数调用的求值只能在运行期进行。



## @cpp `std::<max>`

 返回给定值中的较大者 

```C++
template<class T> 
const T& max(const T& a, const T& b)
{
    return (a < b) ? b : a;
}

template<class T, class Compare> 
const T& max(const T& a, const T& b, Compare comp)
{
    return (comp(a, b)) ? b : a;
}

template< class T >
T max( std::initializer_list<T> ilist)
{
    return *std::max_element(ilist.begin(), ilist.end());
}

template< class T, class Compare >
T max( std::initializer_list<T> ilist, Compare comp )
{
    return *std::max_element(ilist.begin(), ilist.end(), comp);
}
```



## @cpp memcpy()

` void *memcpy(void*dest, const void *src, size_t n); `

 由src指向地址为起始地址的连续n个字节的数据复制到以destin指向地址为起始地址的空间内。 

　　1.source和destin所指内存区域不能重叠，函数返回指向destin的指针。

　　2.与strcpy相比，memcpy并不是遇到'\0'就结束，而是一定会拷贝完n个字节。



## @cpp strtol

 将一个字符串转换为长整型long，其函数原型为 :

`long int strtol (const char* str, char** endptr, int base);`

str是要转换的字符

enptr是指向第一个不可转换的字符位置的指针

base的基数，表示转换成为几进制的数

两点注意：

- 当 base 的值为 0 时，默认采用 10 进制转换，但如果遇到 '0x' / '0X' 前置字符则会使用 16 进制转换，遇到 '0' 前置字符则会使用 8 进制转换。
- 若endptr 不为NULL，则会将遇到的不符合条件而终止的字符指针由 endptr 传回；若 endptr 为 NULL，则表示该参数无效，或不使用该参数。