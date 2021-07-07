# scala

Scala分为变量（var）跟常量（val） :

在Scala中每次赋值都会加载到内存中，如果每次都是一大段字符串的内容，都全部加载到内存中，那么内存势必都会卡爆，影响机子性能，所以Scala出现了一种==“惰性赋值”==方式，
作用：使用的时候，才会真正的加载到内存中去。
用法：提前加上lazy的关键字，只能在常量（val）中用，不能变量（var）中用（适合于大段的常量内容）
格式：lazy val 名称：类型 = 值（注意：scala中可以不用写数据类型，Scala编译器可以自己推导出来）

Scala的数据类型和Java几乎一样，但是Scala的类型名都是以**大写字母**开头。


Bundle

Bundle与Vec也是Chisel定义的数据类型。Bundle是一些元素的集合，每个元素都有一个变量名，类似于C语言中的结构体。用户可以通过定义Bundle的子类来定义一个Bundle类型的变量

创建map时使用，表示映射

```Scala
val score = Map("小明" -> 50, "小红" -> 60)
```

字符串"小明"映射成50，"小红"映射成60

### trait

Scala Trait(特征) 相当于 Java 的接口，实际上它比接口还功能强大。

与接口不同的是，它还可以定义属性和方法的实现。

一般情况下Scala的类只能够继承单一父类，但是如果是 Trait(特征) 的话就可以继承多个，从结果来看就是实现了多重继承。Trait(特征) 定义的方式与类类似，但它使用的关键字是 **trait**

#### case class

实例化案例类`Book`时，并没有使用关键字`new`，这是因为案例类有一个默认的`apply`方法来负责对象的创建。

当你创建包含参数的案例类时，这些参数是公开（public）的`val`

(x:Int) => x +1 ，就等同于下面的Java方法：

```scala
public int function(int x) {
    return x+1;
}
```

var list = Array(1,2,3,4) for (aa <- list) {  printf(aa+"   ") }集合遍历

:::三个冒号运算符表示List的连接操作。(类似于Java中的 `list1.addAll(list2)`)
::两个冒号运算符表示普通元素与list的连接操作。(类似于Java中的`list1.add(A)`

val arrBuf1 = new ArrayBuffer[Int]() arrBuf1+= 11 // 添加一个元素

如果实例化了子类的对象，但是将其赋予了父类类型的变量，在后续的过程中，又需要将父类类型的变量转换为子类类型的变量，应该如何做？

Ø  首先，需要使用isInstaceOf 判断对象是否为指定类的对象，如果是的话，则可以使用 asInstanceOf 将对象转换为指定类型；

Go是**静态类型语言**，变量要声明了再用，声明变量的时候要指定类型，像C那样，可以知道分配多少内存

```go
var a int
a = 1
```

Go也支持**短变量声明**（就是带冒号的），编译器可以**推断类型**（通过后面的赋值自动推断出类型），不用我们**显式声明**了当然主要针对局部作用域临时变量

```go
a := 1
```

**case object** 

相比于case class Person(age:Int,name:String)缺少了apply、unapply方法，因为case object是没有参数输入的，所以对于apply 和unapply的方法也自然失去。

2、因为class 和 object 在编译的时候，object是只有一个编译文件，而当两者加上case之后发现两者都是有2个编译文件，也就是说case object 不在像object那样仅仅是一个单列对象，而是有像类（class）一样的特性。

3、都有toString,hashCode,copy,equals方法和继承了Product和Serializable（implements Product, Serializable）

当Person有参数的时候，用case class ，当Person没有参数的时候那么用case object。這一样意义在于区分 有参和无参

Some

Option有两个子类别，Some和None。当程序回传Some的时候，代表这个函式成功地给了你一个String，而你可以透过get()函数拿到那个String，如果程序返回的是None，则代表没有字符串可以给你。

Scala程序使用Option非常频繁，在Java中使用null来表示空值，代码中很多地方都要添加null关键字检测，不然很容易出现NullPointException。因此Java程序需要关心那些变量可能是null,而这些变量出现null的可能性很低，但一但出现，很难查出为什么出现NullPointerException。
 Scala的Option类型可以避免这种情况，因此Scala应用推荐使用Option类型来代表一些可选值。使用Option类型，读者一眼就可以看出这种类型的值可能为None。

实际上，多亏Scala的静态类型，你并不能错误地尝试在一个可能为null的值上调用方法。虽然在Java中这是个很容易犯的错误，它在Scala却通不过编译，这是因为Java中没有检查变量是否为null的编程作为变成Scala中的类型错误（不能将Option[String]当做String来使用）。所以，Option的使用极强地鼓励了更加弹性的编程习惯。

foreach

 val f = List(1,2,3,4,5,6)

  f.foreach(x=>print(" "+x))

 names zip scores res1: Array[(String, Int)] = Array((zhangsan,60), (lisi,70), (wangmazi,90))

我们调用poke来驱动输入，调用expect来检查输出。如果不使用expect来比较期望值的话（没有断言的话），也可以使用peek来读出输出值。
