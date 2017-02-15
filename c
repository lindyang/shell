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
