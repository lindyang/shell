time_t
#include <time.h>
srand((unsigned int)time(0));  // 0 is NULL, argument is time_t *

#include <stdlib.h>
srand, rand

extern int roll_count;  // 来自头文件
int roll_count = 0;  // 来自源文件
一个变量只可以有一个定义声明, 但使用extern的声明是一个引用声明, 这样的声明想用多少就用多少.

srand((unsigned int)time(0));
rand() % num + 1;

传统上曾将malloc定义为指向char类型的指针. ANSI C: void 指针.
malloc找不到所需的空间, 返回NULL.

创建数组的三种方式
    常量数组
    变长数组(C99)
    malloc(C99之前也可使用)

#include <stdlib.h>
malloc, free
exit
EXIT_FAILURE
EXIT_SUCCESS

C中类型指派是可选的, 但是C++是必须的
free()并不是总是必须, 程序终止会自动释放内存.

long * newmem;
newmem = (long *)calloc(100, sizeof(long));
calloc将快中全部的位都置为0(某些硬件系统, 浮点0不是用全0表示).

malloc定义二维数组
int (* p2)[6];
int (* p3)[m];
p2 = (int (*)[6])malloc(n * 6 * sizeof(int));  // n*6
p3 = (int (*)[m])malloc(n * m * sizeof(int));  // n*m, 不能在C90中使用, 因为变量m

动态内存分配所使用的内存部分肯能变成碎片化, 使用动态内存往往导致进程比使用堆栈内存慢.

ANSI C的类型限定词
    const
    volatile
    restrict(C99)

幂等: const const int n = 6 相当于 const int n = 6.

const float * pf;  /* pf指向一个常量浮点值, 但pf本身可以改变 */
float * const pt;  /* pt是一个常量指针, 但所指向的值可以改变 */

文件共享const数据
    一个文件定义, 一个文件使用extern引用声明
    放到include文件, 再使用static const. 缺点是不能通信, 包含巨大数组就是问题.

volatile
    val_0 = x;
    /* 一些不使用x的代码 */
    val_1 = x;
    ANSI以前, 编译器无从得知中间是否有改变x的代码, 为了安全起见, 编译器不使用缓存.
    而现在, 没有volatile关键字, 编译器进行优化.

一个值可以同时是const和volatile. 例如, 硬件时钟一般不能由程序改变(const), 但可以被程序以外的代理改变(volatile).
volatile const int loc;

restrict
    允许编译器优化某几种代码增强计算支持. 它只可以用于指针, 并且指针是访问数据的唯一且初始的方式.
    int ar[10];
    int * restrict restar = (int *)malloc(10 * sizeof(int));
    int * par = ar;
    可以将关键字restrict作为指针型函数参量的限定词使用.
    C库有两个函数可以从一个位置把字节复制到另一个位置.
    void * memcpy(void * restrict s1, const void * restrict s2, size_t n);  // 两个位置之间不能重叠
    void * memmove(void * s1, const void * s2, size_t n);
    1是告诉编译器优化, 2是让用户使用满足restrict的参数(不遵守, 那就是在冒险).

旧关键词的新位置
    void ofmouth(int * const a1, int * restrict a2, int n);  // 以前的风格
    void ofmouth(int a1[const], int a2[restrict], int n);  // C99允许
    static情形是不同的, 因为它引发一些新的问题.
    double stick(double ar[static 20]);  // 该数组至少有20个元素. 与restrict一样, 有两个读者.


第13章 文件的输入/输出

文本视图
    程序看到的内容和文件的内容有可能不同.(仅仅看到\n)
二进制视图
    可以看到\r\n

低级IO: 操作系统提供的基本I/O服务.
标准高级IO
C程序自动打开3个文件

fp并不指向实际的文件, 指向关于文件信息的数据包(包括缓冲区信息).
磁盘已满, 文件名非法, 存取权限不够或者硬件问题都会导致fopen失败.

fclose(fp)关闭fp指定的文件, 同时根据需求刷新缓冲区.
fclose()成功返回0, 失败返回EOF(磁盘已满, 磁盘移走或IO错误).

fgets()函数读取到它所遇到的第一个换行字符后面, 或者读取比字符串最大长度少一或者文件结尾. 然后添加一个空字符.
fgets()遇到文件结尾返回NULL值.

fgets(line, MAX, stdin) != NULL && line[0] != '\n')
fseek接受3个参数, 返回一个int. ftell返回long
fseek
    FILE
    offset: 正(前移), 负(后移), 0(不懂)
    SEEK_SET(开始), SEEK_CUR(当前), SEEK_END(结尾)
正常返回0, 超出文件范围, 返回-1.
ftell在stdio.h中
ANSI C规定, 对于文本模式, 返回值可以用作fseek的第2个参数.
MS-DOS, \r\n看作一个字节计数.
fsetpos, fgetpos, fpos_t(file position type).
fpos_t不能是数组类型.
int fgetpos(FILE * restrict stream, fpos_t * restrict pos);
int fsetpos(FILE * stream, const fpos_t * pos);
int ungetc(int c, FILE * fp);  // 队列
int fflush(FILE * fp);
int setvbuf(FILE * restrict fp, char * restrict buf, int mode, size_t size);
如果buf是NULL, 函数自动分配一个缓冲区.
mode:
    _IOFBF
    _IOLBF
    _IONBF

fread, fwrite提供二进制服务.

第14章 结构和其他数据形式
struct, union, typedef
. ->
struct [标记]
{
};

可以初始化一个结构变量(ANSI C之前的C, 不能是自动变量);
struct book library = {
    "The Pirate and the Devious Damsel",
    "Renee Vivotte",
    1.95
};
如果初始化一个具有静态存储时期的结构, 值必须是常量表达式.
C99 支持:
    struct book surprise = { .value = 10.99 };
    可以按照任意的顺序初始化项目.
    struct book gift = {
        .value = 18.90,
        .author = "Philionna Pestle",
        0.35
    };
静态的或外部的数据不放在堆栈中.
him->income, (*him).income
->与.优先级一样
结构的大小有可能大于个成员之和.
ANSI C允许把结构传给参数.
C允许把一个结构赋值给另一个结构.
struct pnames {
    char * first;
    char * last;
}
结构体存储字符串用指针有严重误用的可能

第16章节 5, 6, 7

C99复合文字:
    (struct book){"title", "author", 6.99}
C99伸缩型数组成员:
    struct flex {
        int count;
        double scores[];  //伸缩型数组成员
    }
    struct flex * pf;
    pf = (struct flex)malloc(sizeof(struct flex) + 5 * sizeof(double));
    pf->scores[2] = 22.0;
联合是能在同一个存储空间(但不是同时)存储不同类型数据的数据结构.
union hold {
    int digit;
    double bigfl;
    char letter;
};
union hold valA;
valA.letter = 'R';
union hold valB = valA;  //把一个联合初始化为另一个联合
union hold valC = {88};  //初始化联合的第一个成员
union hold valD = {.bigfl = 118.2};  //指定初始化项目(C99)
结构和联合体都可以使用., ->
enum spectrum {red, orange, yellow, green, blue, violet};
枚举常量较宽松的限定为任意整数类型, 只要该整数类型能保存改枚举类型.
C 允许枚举++, 但是 C++ 不允许, 所以用 int.
enum feline {cat, lynx=10, puma, tiger}

结构标记, 联合标记以及枚举标记共享同一命名空间, 并且这个名字空间和普通变量使用的名字空间不同.
struct rect {double x; double y};
int rect;  // 在C中不会引起冲突.
但是 C++不允许.

typedef和#define
    与#define不同, typedef 给出的符号名称仅限于类型, 而不是对值.
    typedef 的解释由编译器, 而不是预处理器执行.
    虽然它的范围有限, 但是在受限范围内, typedef 比 define 灵活.

使用#define 可以实现 typedef 的一部分功能. 例如:
#define BYTE unsigned char
但是也要#define实现不了的功能.
#define STRING char *
那么: STRING name, sign
将会变为 char * name, sign;
typedef struct {double x; double y;} rect;
如果两个结构的声明都不使用标记, 但是使用同样的成员(成员名和类型都匹配), 那么C认为这两个结构具有同样的类型.
tpedef char(* FRPTC())[5]; FRPTC声明函数类型, 该类型的函数返回一个指向含有5个元素的 char 数组的指针.
int (* rusks)[10];  // 指向具有10个元素的int 数组
int (* uof[3])[4];  // 一个具有3个元素的数组, 每个元素都是一个指向具有4个元素的int数组的指针.

[]和()具有同样的优先级.
char (* flump[3])();  // 由3个指针组成的数组, 每个指针指向返回类型为 char 的函数.

typedef int arr5[5];
typedef arr5 * p_arr5;
typedef p_arr5 arrp10[10];
arr5 togs;  // togs是具有5个元素的 int 数组
p_arr5 p2;  // p2是一个指针, 指向具有5个元素的 int 数组.
arrp10 ap;  // ap 是具有10个元素的指针数组, 每个指针指向具有5个元素的 int 数组.

C 库中的 qsort()函数.

void (* pf)(char *);  // pf 是一个指向函数的指针
pf = ToUpper;
(*pf)(mis);  // 语法1
pf(mis);  // 语法2, K&RC 不允许

typedef void (* V_FP_CHARP)(char *);
void show (V_FP_CHARP fp, char *);
V_FP_CHARP pfun;
V_FP_CHARP arpf[2] = {ToUpper, ToLower};

while(strchr("ulton", ans) == NULL)

第15章 位操作

负数:
    补码->原码: 先写负号, 然后翻转加1
小数乘以2的指数, 只改变指数部分.
掩码: 掩码中的0覆盖了 flags中相应的位. &= MASK
打开位: 或 |= MASK
关闭位: &= ~MASK
转置位: ^= MASK
查看一位的值: if((flag & MASK) == MASK)
为了避免信息漏过边界, 位掩码至少应该与其所屏蔽的值具有相同的宽度.

右移操作, 对于有符号的类型, 结果依赖于机器(用0或者1填充).

移位运算符能提供快捷, 高效(依赖于硬件)对2的幂的乘法和除法.
移位操作符从较大的单元中提取多组比特位.

while(bits-- > 0){
    mask |= bitval;
    bitval <<= 1;
}

位运算符和位字段

位字段是 signed int 或 unsigned int 中一组相邻的位( C99还允许_ Bool)

struct {
    unsigned int autfd: 1;
    unsigned int bldfc: 1;
    unsigned int undln: 1;
    unsigned int itals: 1;
} prnt;
变量被存储在 int 大小的单元中, 但是只有4位被使用.
字段不限于1位大小.

struct {
    unsigned int field1: 1;
    unsigned int       : 2;
    unsigned int field2: 1;
    unsigned int       : 0;
    unsigned int field3: 1;
} stuff;
field3 存储在下一个 int 中.
从左向右, 从右向左.

struct box_props {
    unsigned int opaque  :1;
    unsigned int fill_color: 3;
    unsigned int         : 4;
    unsigned int show_border: 1;
    unsigned int border_color: 3;
    unsigned int border_style: 2;
    unsigned int        : 2;
}

C 使用 unsigned int 作为字段结构的基本布局单元.
即使一个结构的唯一成员是1个字段, 该结构的大小也与一个 unsigned int 的大小相同.

联合允许其第一个成员被初始化.
#define FILL_BLUE 1<<11
1<<11是常量表达式, 在编译时对其求值.
enum { QPAQUE = 0x1, FILL_BLUE = 0x8, FILL_GREEN = 0x4 };
大端小端, 将一个数字的尾端放到高地址还是低地址.

第16章 C 预处理器和 C 库
#define #include #ifdef #else #endif #ifndef #if #elif #line #error #pragma

sqrt, atan, atan2, exit, atexit, assert, memcpy, memmove, va_start,
va_arg, va_copy, va_end

翻译程序:
1.字符->源字符集
2.检查\后面紧跟的换行符的实例并删除
3.语言符号( token), 空白, 注释
    用一个空格代替每一个注释
4.找可能存在的预处理器指令

C有类对象宏, 类函数宏
总会用实体代替该宏(有一种例外)

预处理器不进行计算, 只是按照指令进行文字替换操作.

#define LIMIT 20
const int LIM = 50
static int data1[LIMIT];
static int data2[LIM];  // 无效
const int LIM2 = 2 * LIMIT;
const int LIM3 = 2 * LIM;  // 无效

#define EIGHT 4  *  8
字符型字符串, 预处理器用4  *  8代替 EIGHT( 额外的空格也当做替换文本的一部分).
用语言符号字符串的观点看, 空格只是分隔主体中语言符号的符号.

重定义常量, 新定义不同于旧的定义, ANSI 的编译器认为是错误.
#define SIX 2 * 3
#define SIX 2  *  3
#define SIX 2*3 /* 与前面2个定义不同, 可以用 #undef 重新定义宏 */

#define SQUARE (x) ((x) * (x))
SQUARE(x + 2) => ((x + 2) * (x + 2))
100/SQUARE(2) => 100 / ((2) * (2))
无法避免的问题
SQUARE(++x) => ++x * ++x, 数值不定.

#define PSQR (x) printf("The square of x is %d.\n", ((x) * (x)));
字符串中包含宏参数使用#. 如果 x 是一个宏参量, #x(stringizing)
#define PSQR (x) printf("The square of " #x " is %d.\n", ((x) * (x)));

预处理器的粘合剂: ##运算符.
会把两个语言符号组合成单个语言符号
#define XNAME(n) x ## n
XNAME(4) => x4

可变宏: ...和__VA_ARGS__
<stdvar.h>
#define PR(...) printf(__VA_ARGS__)
省略号只能代替最后的宏参数

宏与函数间的选择实际上是时间与空间的权衡.
宏的一个优点是它不检查其中变量的类型.
C99第三种选择: 内联函数
在嵌套循环中使用宏更有助于加速程序运行.

#include "mystuff.h"
#include "/usr/biff/p.h"
先在当前目录(或文件中指定的其它目录)中寻找文件, 然后在标准文件中查找.
    源代码所在的目录
    当前工作目录
    工程文件所在目录

BUFSIZE(标准I/O 缓冲区的大小)
time_t

使用 static 后, 每个包含该头文件的文件都获得一份该常量的拷贝.

时期
    自动, 静态
作用域
    代码块, 文件
链接
    空, 内部, 外部

#line 用于重置行和文件信息
#error 用于给出错误消息
#pragma 向编译器发出指令

#define LIMIT 400
#undef LIMIT
即使没有定义 LIMIT, undef 都是合法的.

#define LIMIT 1000
#define GOOD
#define A(X) ((-(X)) * (X))
int q;  // q 不是一个宏, 因此是未定义的
#undef GOOD

__DATE__ 和 __FILE__ 是已经定义的, 并且不能被取消

条件编译
#ifdef
#else
#endif

#ifdef MAVIS
#include "horse.h"
#define STABLES 5
#else
#include "cow.h"
#define STABLES 15
#endif

#ifndef SIZE
    #define SIZE 100
#endif

ifndef 防止多次包含同一文件
头文件的有些语句在一个文件中只能出现一次(如结构类型声明).

#ifndef _STDIO_H
用下划线(可能用两条下划线)作前缀和后缀.

#include <stdio.h>
#include "names_st.h"
#include "names_st.h"

#ifdef VAL
新的实现采用另一种方法
#if defined(VAX)
defined是预处理器运算符

#if defined(VAL)
#elif defined(KEY)
#else defined(ITEM)
#endif

__DATE__
__FILE__
__LINE__
__STDC__
__STDC_HOSTED__
__STDC_VERSION__
__TIME__
__func__(C99)

#line 1000 "cool.c"
把行号重置为10, 文件名重置为 cool.c;

#if __STDC_VERSION__ != 199901L
    #error Not C99
#endif

#pragma c9x on
C99标准提供了3个标准编译指示

C99提供了_Pragma预处理运算符.
_Pragma("nonstandardtreatmenttypeB on")
等价于
#pragma nonstandardtreatmenttypeB on

#define PRAGMA(X) _Pragma(#X)
#define LIMGR(X) PRAGMA(STDC CX_LIMITED_RANGE X)
LIMGR(ON)

直到预处理过程完成后编译器才连接字符串.

执行调用
    建立调用
    传递参数
    跳转到函数
    返回

把函数变为内联函数将近建议编译器尽可能快地快速地调用该函数.
上述建议效果由定义来实现.

编译器看到内联声明后会用 eatline() 函数体代替函数调用.
内联函数的定义和对该函数的调用必须在同一文件中(内部链接).
一般不在头文件中放置可执行代码, 但内联函数是个例外.
与 C++ 不同, C 允许混合使用内联函数定义和外部函数定义.

extern double square(double);
inline double square(double);
double q = square(1.3) + square(1.5);  // 哪一个 square 都有可能.

头文件: 函数的声明或原型
库: 告诉系统到哪里寻找函数代码

比如 fread() 的描述
最早:
    #include <stdio.h
    fread(ptr, sizeof(*ptr), nitems, stream)
    FILE * stream;
后来
    #include <stdio.h>
    int fread(ptr, size, nitems, stream)
    char *ptr;
    int size, nitems;
    FiLE * steam;
ANSI C
    #include <stdio.h>
    size_t fread(void * ptr, size_t size, size_t nmemb, FILE * stream);
C99
    #include <stdio.h>
    size_t fread(void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);

atexit()
ANSI C保证 atexit 至少可以放置32个参数, 并且函数应为不接受任何参数的 void 函数.

exit()
    刷新所有输出流
    关闭所有打开的流
    并关闭调用标准 I/O 函数 tmpfile() 创建的临时文件

void qsort(void * base, size_t nmemb, size_t size,
    int (* compar)(const void *, const void *));

stddef.h 含有 size_t类型的 typedef 或#define定义.

const double * a1 = (const double *) p1;
(const double *) 在 c++ 中必须有.


assert.h assert 宏
写 stderr 并 abort 函数.
stdlib.h 中定义 abort
#define NDEBUG

strcpy, srncpy 复制字符数组.
memcpy, memmove 函数为复制其它类型的数组提供了类似的便利工具.
void * memcpy(void * restrict s1, const void * restrict s2, size_t n);
void * memmove(void * s1, const void * s2, size_t n);

可变参数: stdarg.h
    1. 在函数原型中使用省略号
    2. 在函数定义中创建一个va_list参数列表
    3. 用宏将该变量初始化为一个参数列表.
    4. 用宏访问这个参宿列表
    5. 用宏完成清理工作

double sum(int lim, ...){
    double tic;
    int toc;
    va_list ap;  // 声明用于存放参数的变量
    va_list apcopy;
    va_start(ap, lim)  // 把 ap 初始化为参数列表
    va_copy(apcopy, ap);  // apcopy 是 ap 的一个副本
    /* 实际参数的类型必须与说明符类型向匹配
     不会进行自动
    tic = va_arg(ap, double);
    toc = va_arg(ap, int);
    va_end(ap);  // 释放动态分配的用于存放参数的内存
    va_end(ap);
}


