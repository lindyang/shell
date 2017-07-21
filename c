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
指针p 指向常量字符串(位于常量存储区),常量字符串的内容是不可以被修改的
