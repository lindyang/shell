JavaScript并不强制要求在每个语句的结尾加;
//
/* comment
comment
*/

JavaScript严格区分大小写
JavaScript不区分整数和浮点数，统一用Number表示
NaN
1.2345e3
Infinity
0xff00
字符串是以单引号'或双引号"括起来的任意文本

&&
||
!

false == 0; // true
false === 0; // false
NaN === NaN; // false
isNaN(NaN); // true
1 / 3 === (1 - 2 / 3); // false
Math.abs(1 / 3 - (1 - 2 / 3)) < 0.0000001; // true
大多数情况下，我们都应该用null。undefined仅仅在判断函数参数是否传递的情况下有用

// 建议
[1, 2, 3.14, 'Hello', null, true];
new Array(1, 2, 3); // 创建了数组[1, 2, 3]
索引的起始值为0


对象
JavaScript对象的键都是字符串类型，值可以是任意数据类型
每个键又称为对象的属性
要获取一个对象的属性，我们用对象变量.属性名

变量在JavaScript中就是用一个变量名表示，变量名是大小写英文、数字、$和_的组合，且不能用数字开头
变量名也可以用中文，但是，请不要给自己找麻烦


JavaScript在设计之初，为了方便初学者学习，并不强制要求用var申明变量。这个设计错误带来了严重的后果：如果一个变量没有通过var申明就被使用，那么该变量就自动被申明为全局变量
i = 10; // i现在是全局变量

使用var申明的变量则不是全局变量，它的范围被限制在该变量被申明的函数体内

启用strict模式的方法是在JavaScript代码的第一行写上:
'use strict';

ReferenceError


'\x41'; // 完全等同于 'A'
'\u4e2d\u6587'; // 完全等同于 '中文'
`这是一个
多行
字符串`;

要把多个字符串连接起来，可以用+号连接

ES6新增了一种模板字符串
var name = '小明';
var age = 20;
var message = `你好, ${name}, 你今年${age}岁了!`;
alert(message);

操作字符串
var s = 'Hello, world!';
s.length; // 13
s[13]; // undefined 超出范围的索引不会报错，但一律返回undefined
字符串是不可变的，如果对字符串的某个索引赋值，不会有任何错误，但是，也没有任何效果
s.toUpperCase()
s.toLowerCase()
s.indexOf()
s.indexOf('World'); // 没有找到指定的子串，返回-1
var s = 'hello, world'
s.substring(0, 5); // 从索引0开始到5（不包括5），返回'hello'
s.substring(7); // 从索引7开始到结束，返回'world'
'

属性名不是一个有效的变量, 必须用['xxx']来访问

属性名尽量使用标准的变量名，这样就可以直接通过object.prop的形式访问一个属性了
访问不存在的属性不报错，而是返回undefined
var xiaoming = {
    name: '小明'
    };
xiaoming.age; // undefined
xiaoming.age = 18; // 新增一个age属性
xiaoming.age; // 18
delete xiaoming.age; // 删除age属性
xiaoming.age; // undefined
delete xiaoming['name']; // 删除name属性
xiaoming.name; // undefined
delete xiaoming.school; // 删除一个不存在的school属性也不会报错

是否拥有某一属性，可以用in操作符
如果in判断一个属性存在，这个属性不一定是xiaoming的，它可能是xiaoming继承得到的
自身拥有的，而不是继承得到的，可以用hasOwnProperty()方法

var arr = [1, 2, 3.14, 'Hello', null, true];
arr.length
直接给Array的length赋一个新的值会导致Array大小的变化
如果通过索引赋值时，索引超过了范围，同样会引起Array大小的变化
在编写代码时，不建议直接修改Array的大小，访问索引时要确保索引不会越界。

Array也可以通过indexOf()
slice()就是对应String的substring()版本
var aCopy = arr.slice();
aCopy === arr; // false

push()向Array的末尾添加若干元素，pop()则把Array的最后一个元素删除掉
如果要往Array的头部添加若干元素，使用unshift()方法，shift()方法则把Array的第一个元素删掉

arr.sort();
reverse()
splice()方法是修改Array的“万能方法”，它可以从指定的索引开始删除若干元素，然后再从该位置添加若干元素
concat()方法把当前的Array和另一个Array连接起来，并返回一个新的Array
concat()方法可以接收任意个元素和Array，并且自动把Array拆开，然后全部添加到新的Array里
join()方法是一个非常实用的方法，它把当前Array的每个元素都用指定的字符串连接起来，然后返回连接后的字符串
如果Array的元素不是字符串，将自动转换为字符串后再连接

其中else语句是可选的。如果语句块只包含一条语句，那么可以省略{}
else if
JavaScript把null、undefined、0、NaN和空字符串''视为false，其他值一概视为true
有时一个条件判断即可
JavaScript的循环有两种，一种是for循环，通过初始条件、结束条件和递增条件来循环执行语句块
for循环的一个变体是for ... in循环，它可以把一个对象的所有属性依次循环出来
for (var key in o) {
    alert(key); // 'name', 'age', 'city'
}
for (var key in o) {
    if (o.hasOwnProperty(key)) {
        alert(key); // 'name', 'age', 'city'
    }
}

var a = ['A', 'B', 'C'];
for (var i in a) {
    alert(i); // '0', '1', '2'
    alert(a[i]); // 'A', 'B', 'C'
}
请注意，for ... in对Array的循环得到的是String而不是Number
while
do ... while
用do { ... } while()循环要小心，循环体会至少执行1次，而for和while循环则可能一次都不执行
alert(`Hello, ${arr[str_idx]}`)
JavaScript的对象有个小问题，就是键必须是字符串。但实际上Number或者其他数据类型作为键也是非常合理的
为了解决这个问题，最新的ES6规范引入了新的数据类型Map

var m = new Map([['Michael', 95], ['Bob', 75], ['Tracy', 85]]);
m.get('Michael'); // 95
初始化Map需要一个二维数组，或者直接初始化一个空Map
set, has, delete, get
m.get('Adam'); // undefined

要创建一个Set，需要提供一个Array作为输入，或者直接创建一个空Set
Map和Set是ES6标准新增的数据类型
Map是一组键值对的结构，具有极快的查找速度

遍历Array可以采用下标循环，遍历Map和Set就无法使用下标。为了统一集合类型，ES6标准引入了新的iterable类型，Array、Map和Set都属于iterable类型

具有iterable类型的集合可以通过新的for ... of循环来遍历
for ... of循环是ES6引入的新的语法，请测试你的浏览器是否支持

x.toString()
for ... in循环由于历史遗留问题，它遍历的实际上是对象的属性名称。一个Array数组实际上也是一个对象，它的每个元素的索引被视为一个属性

var a = ['A', 'B', 'C'];
a.name = 'Hello';
for (var x in a) {
    alert(x); // '0', '1', '2', 'name'
}

for ... in循环将把name包括在内，但Array的length属性却不包括在内
for ... of循环则完全修复了这些问题，它只循环集合本身的元素

var a = ['A', 'B', 'C'];
a.name = 'Hello';
for (var x of a) {
    alert(x); // 'A', 'B', 'C'
}

var a = ['A', 'B', 'C'];
a.forEach(function (element, index, array) {
    // element: 指向当前元素的值
    // index: 指向当前索引
    // array: 指向Array对象本身
    alert(element);
});

Set与Array类似，但Set没有索引，因此回调函数的前两个参数都是元素本身
iterable内置的forEach方法，它接收一个函数，每次迭代就自动回调该函数
如果对某些参数不感兴趣，由于JavaScript的函数调用不要求参数必须一致，因此可以忽略它们

JavaScript的函数不但是“头等公民”，而且可以像变量一样使用，具有非常强大的抽象能力
如果没有return语句，函数执行完毕后也会返回结果，只是结果为undefined
由于JavaScript的函数也是一个对象，上述定义的abs()函数实际上是一个函数对象，而函数名abs可以视为指向该函数的变量
第二种定义函数的方式如下
var abs = function (x) {};
上述两种定义完全等价，注意第二种方式按照完整语法需要在函数体末尾加一个;，表示赋值语句结束

由于JavaScript允许传入任意个参数而不影响调用，因此传入的参数比定义的参数多也没有问题，虽然函数内部并不需要这些参数
传入的参数比定义的少也没有问题
abs(); // 返回NaN

function abs(x) {
    if (typeof x !== 'number') {
        throw 'Not a number';
    }
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

JavaScript还有一个免费赠送的关键字arguments，它只在函数内部起作用，并且永远指向当前函数的调用者传入的所有参数。arguments类似Array但它不是一个Array
ES6标准引入了rest参数，上面的函数可以改写为
function foo(a, b, ...rest) {
    console.log('a = ' + a);
    console.log('b = ' + b);
    console.log(rest);
}
如果传入的参数连正常定义的参数都没填满，也不要紧，rest参数会接收一个空数组（注意不是undefined）

JavaScript引擎有一个在行末自动添加分号的机制
return; // 自动添加了分号，相当于return undefined;
变量提升
JavaScript的函数定义有个特点，它会先扫描整个函数体的语句，把所有申明的变量“提升”到函数顶部
JavaScript引擎自动提升了变量y的声明，但不会提升变量y的赋值

function foo() {
    var
        x = 1, // x初始化为1
        y = x + 1, // y初始化为2
        z, i; // z和i为undefined
    // 其他语句:
    for (i=0; i<100; i++) {
        ...
    }
}

JavaScript默认有一个全局对象window，全局作用域的变量实际上被绑定到window的一个属性
任何变量（函数也视为变量），如果没有在当前函数作用域中找到，就会继续往上查找，最后如果在全局作用域中也没有找到，则报ReferenceError错误

名字空间
由于JavaScript的变量作用域实际上是函数内部，我们在for循环等语句块中是无法定义具有局部作用域的变量的
为了解决块级作用域，ES6引入了新的关键字let，用let替代var可以申明一个块级作用域的变量
ES6标准引入了新的关键字const来定义常量，const与let都具有块级作用域

在一个对象中绑定函数，称为这个对象的方法
new Date().getFullYear()
在一个方法内部，this是一个特殊变量，它始终指向当前对象
JavaScript的函数内部如果调用了this，那么这个this到底指向谁？

如果以对象的方法形式调用，比如xiaoming.age()，该函数的this指向被调用的对象，也就是xiaoming，这是符合我们预期的。
如果单独调用函数，比如getAge()，此时，该函数的this指向全局对象，也就是window

```
var fn = xiaoming.age; // 先拿到xiaoming的age函数
fn(); // NaN
```
要保证this指向正确，必须用obj.xxx()的形式调用
ECMA决定，在strict模式下让函数的this指向undefined
原因是this指针只在age方法的函数内指向xiaoming，在函数内部定义的函数，this又指向undefined了

```
'use strict';

var xiaoming = {
    name: '小明',
    birth: 1990,
    age: function () {
        var that = this; // 在方法内部一开始就捕获this
        function getAgeFromBirth() {
            var y = new Date().getFullYear();
            return y - that.birth; // 用that而不是this
        }
        return getAgeFromBirth();
    }
};
```

虽然在一个独立的函数调用中，根据是否是strict模式，this指向undefined或window，不过，我们还是可以控制this的指向的
getAge.apply(xiaoming, []); // 25, this指向xiaoming, 参数为空

另一个与apply()类似的方法是call()，唯一区别是：

apply()把参数打包成Array再传入；

call()把参数按顺序传入。

Math.max.apply(null, [3, 5, 4]); // 5
Math.max.call(null, 3, 5, 4); // 5
对普通函数调用，我们通常把this绑定为null

一个函数就可以接收另一个函数作为参数，这种函数就称之为高阶函数
map()方法定义在JavaScript的Array, 就得到了一个新的Array作为结果
filter也是一个常用的操作，它用于把Array的某些元素过滤掉，然后返回剩下的元素
s && s.trim(); // 注意：IE9以下的版本没有trim()方法

回调函数还可以接收另外两个参数，表示元素的位置和数组本身
利用filter，可以巧妙地去除Array的重复元素
这是因为Array的sort()方法默认把所有元素先转换为String再排序，结果'10'排在了'2'的前面，因为字符'1'比字符'2'的ASCII码小
幸运的是，sort()方法也是一个高阶函数
最后友情提示，sort()方法会直接对Array进行修改，它返回的结果仍是当前Array

但是由于JavaScript语法解析的问题，会报SyntaxError错误，因此需要用括号把整个函数定义括起来
闭包就是携带状态的函数，并且它的状态可以完全对外隐藏起来

Arrow Function（箭头函数)
var fn = x => x * x;
只包含一个表达式，连{ ... }和return都省略掉了
包含多条语句，这时候就不能省略{ ... }和return
参数不是一个，就需要用括号()括起来
() => 3.14
(x, y, ...rest) =>
如果要返回一个对象，就要注意，如果是单表达式:
x => ({ foo: x })
箭头函数内部的this是词法作用域，由上下文确定
箭头函数完全修复了this的指向，this总是指向词法作用域，也就是外层调用者obj

由于this在箭头函数中已经按照词法作用域绑定了，所以，用call()或者apply()调用箭头函数时，无法对this进行绑定，即传入的第一个参数被忽略

更坑爹的是，如果这么写
var fn = xiaoming.age; // 先拿到xiaoming的age函数
fn(); // NaN
要保证this指向正确，必须用obj.xxx()的形式调用
在strict模式下让函数的this指向undefined
重构内层方法:
xiaoming.age(); // Uncaught TypeError: Cannot read property 'birth' of undefined
修复的办法也不是没有，我们用一个that变量首先捕获this

函数末尾如果没有return，就是隐含的return undefined;generator由function*定义（注意多出的*号)
第二个方法是直接用for ... of循环迭代generator对象，这种方式不需要我们自己判断done
n ++;
generator还有另一个巨大的好处，就是把异步回调代码变成“同步”代码
看上去是同步的代码，实际执行是异步的。
typeof操作符获取对象的类型，它总是返回一个字符串

typeof将无法区分出null、Array和通常意义上的object——{}

包装对象用new创建
虽然包装对象看上去和原来的值一模一样，显示出来也是一模一样，但他们的类型已经变为object了！所以，包装对象和原始值用===比较会返回false

判断Array要使用Array.isArray(arr)
判断某个全局变量是否存在用typeof window.myVar === 'undefined'
函数内部判断某个变量是否存在用typeof myVar === 'undefined'
String(), toString()
null和undefined就没有toString()
number对象调用toString():
    123..toString()
    (123).toString()

now.getMonth(); // 5, 月份，注意月份范围是0~11，5表示六月
new Date
Date.parse 时间戳
var d = new Date(1435146562875);
d.toLocaleString();
d.toUTCString();
时间戳是一个自增的整数，它表示从1970年1月1日零时整的GMT时区开始的那一刻，到现在的毫秒数
(new Date()).getTime()
Date.now()

'-'是特殊字符，在正则表达式中，要用'\'转义
[a-zA-Z\_\$][0-9a-zA-Z\_\$]*
/正则表达式/
new RegExp('正则表达式')
var re1 = /ABC\-001/;
var re2 = new RegExp('ABC\\-001');
RegExp对象的test()

'a b   c'.split(/\s+/); // ['a', 'b', 'c']
RegExp对象上用exec()方法提取出子串来
exec()方法在匹配失败时返回null
g，表示全局匹配
var r1 = /test/g;
// 等价于:
var r2 = new RegExp('test', 'g');
全局匹配类似搜索，因此不能使用/^...$/，那样只会最多匹配一次
正则表达式还可以指定i标志，表示忽略大小写，m标志，表示执行多行匹配
\w可以匹配一个字母或数字或下划线
[\w]仍然具有意义
[.]失去意义

JavaScript Object Notation

JSON.stringify(xiaoming, null, '  ');
第二个参数用于控制如何筛选对象的键值，如果我们只想输出指定的属性，可以传入Array

JSON.stringify(xiaoming, convert(key, value), '  ');

toJSON()
JSON.parse()
JSON.parse()还可以接收一个函数
JSON.parse(
    '{"name":"小明","age":14}',
    function (key, value) {
        // 把number * 2:
        if (key === 'name') {
        return value + '同学';
        }
        return value;
    }
); // Object {name: '小明同学', age: 14}

