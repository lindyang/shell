"math/rand"
rand.Intn(10)

程序运行的入口是包 main
圆括号组合了导入,
编写多个导入语句
在 Go 中，首字母大写的名称是被导出的
函数: 注意类型在变量名 之后
func add(x int, y int) int {
	return x + y
}

x int, y int
被缩写为 x, y int
当两个或多个连续的函数命名参数是同一类型，则除了最后一个类型之外，其他都可以省略

func swap(x, y string) (string, string) {
    return y, x
}

a, b := swap("hello", "world")
func split(sum int) (x, y int) { return }
var 语句定义了一个变量的列表；跟函数的参数列表一样，类型在后面
var c, python, java bool
var 语句可以定义在包或函数级别
初始化是使用表达式，则可以省略类型

函数中, 明确类型, `短声明变量`
[u]int32, [u]intptr
byte // uint8
rune // int32, 代表一个Unicode码
float32, float64
complex64, complex128

"math/cmplx"
const f = "%T(%v)\n"
fmt.Printf(f, ToBe, ToBe)

零值:
    数值类型为 0
    布尔类型为 false
    字符串为 "" （空字符串）
与 C 不同的是 Go 的在不同类型之间的项目赋值时需要显式转换
当右值定义了类型时，新变量的类型与其相同
一个未指定类型的常量由上下文来决定其类型

Go 只有一种循环结构—— for 循环
for i := 0; i < 10; i++ { }
初始化语句一般是一个短变量声明，这里声明的变量仅在整个 for 循环语句可见
for 语句的三个组成部分 并不需要用括号括起来，但循环体必须用 { } 括起来

for sum < 1000 {}  // while
for {}  // 死循环
if 语句也不要求用 ( ) 将条件括起来，同时， { } 还是必须有的
fmt.Sprint  // string
if 语句可以在条件之前执行一个简单语句, 这个语句定义的变量的作用域仅在 if 范围之内

%T, %v, %g float64


witch os := runtime.GOOS; os {
fallthrough

"runtime"
"time"

today = time.Now().Weekday()
time.Saturday
case today + 0
t.Hour()
没有条件的 switch 同 switch true 一样

延迟调用的参数会立刻生成, defer 语句会延迟函数的执行直到上层函数返回
: defer 栈

Go 没有指针运算
p := &i
var p *int

type Vertex struct {
    X int
    Y int
}

Vertex{1, 2}
(&v).X = 1e9

使用 Name: 语法可以仅列出部分字段
v2 = Vertex{X: 1, Y:100}
类型 [n]T 是一个有 n 个类型为 T 的值的数组

s := []int{2, 3, 5, 7, 11, 13}
len(s)
%d

"strings"
strings.Join

strings.Join(s[i], " ")
[][]string{
}
s[lo:hi], 不含hi
s[lo:lo+1] 有一个元素

a := make([]int, 5)
b := make([]int, 0, 5) // len(b)=0, cap(b)=5

一个 nil 的 slice 的长度和容量是 0
var z []int, z == nil

a := make([]int, 5)  // five zeros
var a []int  // nil
a = append(a, 0)
a = append(a, 2, 3, 4)
func append(s []T, vs ...T) []T
如果 s 的底层数组太小，而不能容纳所有值时，会分配一个更大的数组

for i, v := range pow {}
第一个是当前下标（序号），第二个是该下标所对应元素的一个拷贝
如果只需要索引值，去掉 “ , value ” 的部分即可
可以通过赋值给 _ 来忽略序号和值

map 在使用之前必须用 make 来创建；值为 nil 的 map 是空的，并且不能对其赋值

var m map[string]Vertex
m = make(map[string]Vertex)
map 的文法跟结构体文法相似，不过必须有键名
若顶级类型只是一个类型名，你可以在文法的元素中省略它

删除元素
delete(m, key)

elem, ok = m[key]
ok: true/false
false 时 elem 是 map 的元素类型的零值

func adder() func(int) int {
    sum := 0
    return func(x int) int {
        sum += x
        return sum
    }
}

Go 没有类
方法接收者 出现在 func 关键字和方法名之间的参数中

func (v Vertex) Abs() float64 {
}

fmt.Println(math.Sqrt2)
你可以对包中的 任意 类型定义任意方法，而不仅仅是针对结构体

指针接收者:
    避免拷贝值
    修改接收者指向的值

接口类型是由一组方法定义的集合
type Abser interface {
    Abs() float64
}

type Reader interface {
    Read(b []byte) (n int, err error)
}

type Write interface {
    Write(b []byte) (n int, err error)
}

type ReadWriter interface {
    Reader
    Writer
}

fmt.Fprintf(w, "hell, writer\n")
// os.Stdout 实现了 Writer
var w Writer
w = os.Stdout

type Stringer interface {
    String() string
}

type error interface {
    Error() string
}

strconv.Atoi("42")

package main
import (
    "fmt"
    "time"
)

type MyError struct {
    when time.Time
    what string
}

func (e *MyError) Error() string {
    return ...
}

i, err := strconv.Atoi("42")

func (e ErrNegativeSqrt) Error() string {
    return fmt.Sprintf("%v", float64(e))
}

io.EOF

%q
strings.NewReader

io.Copy(os.Stdout, &r)
"net/http"

type Handler interface {
    ServeHTTP(w ResponseWriter, r *Request)

}

http.ListenAndServe
fmt.Fprint


annel 是有类型的管道，可以用 channel 操作符 <- 对其发送或者接收值

和 map 与 slice 一样，channel 使用前必须创建
缓冲 channel: ch := make(chan int, 100)
满的时候才会阻塞, 空的时候接收操作会阻塞

cap(c)
close(c)


