# python笔记



动态类型, 不用声明, 变量类型可以随时改变.

是一个oop的语言.

### 数据类型

basic type : int/float/ complex , str . bool

container :  list/tuple,  dict/ set  

dict是用来存储键值对结构的数据的，set其实也是存储的键值对，只是默认键和值是相同的。Python中的dict和set都是通过散列表来实现的

tuple ,int , str是immutable的,值传递  list,dict是 mutable的, 引用传递.

list 的方法有: insert, remove, slice, index, interate,  



range(10)  产生一个0到9的 range object.`list(range(10))`

终止index是 左闭右开的. 比如`list(range(1,11))`  从1到10 

TypeError: 'int' object is not subscriptable此报错一般是在整数上加了下标：

#### list

list没泛型，leetcode的List有



list中加入tuple

```python
res += (i, j)是不对的, 就是加了两个int
res.append((i, j)) correct
xy = (i, j)
res.append(xy) correct

遍历list
for i in list
初始化list
li = [i for i in range(8)]
list中find查找:  if a in list :就可以了.
        找有几个dog:flashcard_list.count('dog')
```

负索引表示从末尾开始，-1 表示最后一个项目，-2 表示倒数第二个项目

```python
list 中元素个数 :  len(prices)
thislist[2:5])
获得最后一个
print(list1[-1])
print(len(thislist))
删除:
    thislist.remove("banana")remove方法只会删除掉该元素在列表中第一次出现的位置
    thislist.pop()有insert方法可以直接在对应下标处插入元素，pop方法也可以带参数使用，从而删除指定下标处的元素
    del thislist[0]
    del thislist
复制:
    mylist = list(thislist)
    mylist = thislist.copy()
    追加
    您可以使用 extend() 方法，其目的是将一个列表中的元素添加到另一列表中：
表示栈
st.append(str)
res += st.pop()
```

##### 错误

1 : Shadows built-in name 'list' 

意思是你的你的变量名起的不好；最好要具体有意思，不要太随意，起像str、list、len等太随意的名字。



#### dict

所有mutable object是不能做key的.

```python
大括号来产生一个dict
例如`band = {'drum': 'saya' , 'voacal' : 'kani'}`
get 也可以用[],但是如果用字典里没有的键访问数据，会输出错误
dict['Age'] = 8 # 更新
dict['School'] = "RUNOOB" # 添加
判断python字典中key是否存在
 d.has_key('name')
'name' in d.keys() 除了使用in还可以使用not in，判定这个key不存在
遍历 dict 
for key in dict: 或者for key in dict.keys():
for value in dict.values():
for key,value in dict.items():
删除元素
pop(key[,default])key: 要删除的键值default: 如果没有 key，返回 default 值
del dict['Name']  # 删除键是'Name'的条目
RuntimeError: dictionary changed size during iteration
    先复制再 b = a[:] 再把a指向b。 或者list可以倒序循环遍历
 找最大值
max(m.values())
统计list成dict
 freq = collections.Counter(tasks)
    freq = Counter([0])
```

##### defaultdict类

除了接受类型名称作为初始化函数的参数之外，还可以使用任何不带参数的可调用函数，到时该函数的返回结果作为默认值，这样使得默认值的取值更加灵活。

```python
from collections import defaultdict
>>> def zero():
...     return 0
>>> dd = defaultdict(zero)
>>> dd['foo']
0
接受类型名称作为初始化函数的参数
  freq = defaultdict(int)
  freq[0] =1
    
```

#### tuple

不可变的序列



#### set

```python
可以使用大括号 { } 或者 set() 函数创建集合，注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
>>> thisset = set(("Google", "Runoob", "Taobao"))
>>> thisset.update({1,3})
{1, 3, 'Google', 'Taobao', 'Runoob'}
>>> thisset.update([1,4],[5,6])  
{1, 3, 4, 5, 6, 'Google', 'Taobao', 'Runoob'}
或者可以thisset.add("Facebook")
s.remove( x )如果元素不存在，则会发生错误

```

#### 优先队列

`heapq`是二叉堆，通常用普通列表实现`heapq`模块是在Python中不错的优先级队列实现。由于heapq在技术上只提供最小堆实现，因此必须添加额外步骤来确保排序稳定性，以此来获得“实际”的优先级队列中所含有的预期特性。

```python
import heapq
q = []
heapq.heappush(q, (2, 'code'))
heapq.heappush(q, (1, 'eat'))
heapq.heappush(q, (3, 'sleep'))
while q:
    next_item = heapq.heappop(q)
    print(next_item)
# 结果：
#   (1, 'eat')
#   (2, 'code')
#   (3, 'sleep')
from queue import PriorityQueue as PQ
q = PriorityQueue()
>>> q.put((2, "Lisa"))
>>> q.put((1, "Lucy"))
>>> q.put((0, "Tom"))
The lowest valued entries are retrieved first 
与 heapq 模块不同的是，PriorityQueue 是基于类实现的，其提供的操作是同步的，提供锁操作，支持并发的生产者和消费者。
Queue objects (Queue, LifoQueue, or PriorityQueue) provide the public methods described below.
Queue.get(block=True, timeout=None)
Remove and return an item from the queue. 
Queue.put(item, block=True, timeout=None)
Put item into the queue.
```

#### deque

```python3
from collections import deque
d = deque(['a','b','c','d','e','f'])
d.extendleft
如果使用deque进行切片的话会抛出异常,比如print(d[:-1])不行
print(dq.count(1))
计算队列元素的个数是否等于1个，假设大于或等于都返回True。否则返回False
count不能用来求deque元素个数, 要用len
```

#### array

```python
array.index(x)  
# 方法返回x 在数组中第一次出现的下标, 下标从零开始,如果没有找到该元素会报异常.
ValueError: array.index(x): x not in list
其实这个没啥用,  因为只能一维, 一般都用二维的 np.array
```

循环

但是在for循环内修改i值，只会对当前一次的循环体内有效

跳跃的话, 要使用 while 替换 for

#### sort

```python
# 降序
vowels.sort(reverse=True)
a = [('b', 4), ('a', 12), ('d', 7), ('h', 6), ('j', 3)]
a.sort(key=lambda x: x[0])
list.sort(key=lambda x: (key1, key2))
```



### typing 数据类型

collections是Python内建的一个集合模块，提供了许多有用的集合类。

### typing模块的作用

1. 类型检查，防止运行时出现参数和返回值类型不符合。
2. 作为开发文档附加说明，方便使用者调用时传入和返回参数类型。
3. 该模块加入后并不会影响程序的运行，不会报正式的错误，只有提醒。

- 在传入参数时通过"参数名:类型"的形式声明参数的类型；
- 返回结果通过"-> 结果类型"的形式声明结果的类型。
- 

### 运算符

没有++ -- 

没有? :

 可以用两个乘表示平方, 两个除 表示整除, 可以用and ,or 

in 判断名字是否存在list之中.

is  判断是否为同一个对象.

is和 == 不同, 

pass // 还没想好写啥, 先pass.

for-in  for语句不需要int i 变量,

`for it in s`   类似于 cpp中的 `for(auto it : s)`

 可以同时返回多个值.

### 类

```python
class Circle:
    def __init__(self,v):
        self.__value=v
    def getArea(self):
        return 3.1415926*self.__value**2
    def getPerimeter(self):
        return 3.1415926*self.__value*2
c=Circle(5)
```

1.np.where(condition,x,y) 当where内有三个参数时，第一个参数表示条件，当条件成立时where方法返回x，当条件不成立时where返回y
2.np.where(condition) 当where内只有一个参数时，那个参数表示条件，当条件成立时，where返回的是每个符合condition条件元素的坐标,返回的是以元组的形式.

eq怎么用?

```python
print``(cat_1.__eq__(cat_2)) 
```

==  运算符是比较哪些?

- `is`比较的是两个整数对象的id值是否相等，也就是比较两个引用是否代表了内存中同一个地址。
- `==`比较的是两个整数对象的内容是否相等，使用`==`时其实是调用了对象的`__eq__()`方法。

对于整数对象，Python把一些频繁使用的整数对象缓存起来，保存到一个叫small_ints的链表中，在Python的整个生命周期内，任何需要引用这些整数对象的地方，都不再重新创建新的对象，而是直接引用缓存中的对象。Python把频繁使用的整数对象的值定在[-5, 256]这个区间，如果需要这个范围的整数，就直接从small_ints中获取引用而不是临时创建新的对象。因为大于256或小于-5的整数不在该范围之内，所以就算两个整数的值是一样，但它们是不同的对象。

所以python会显示:  `257 is not 257`

通过比较它的b属性建立堆排序::

```python
1.   def __lt__(self, other):
2.         if self.b<other.b:
3.             return True
a = P(3,1)
b = P(2,3)
c = P(10,0)
d = P(3,1)
 
h = []
heapq.heappush(h,a)
heapq.heappush(h,b)
heapq.heappush(h,c)
heapq.heappop(h)
就会把10,0 排在第一个,弹出
```

#### 类内方法

因为类里面调用属性需要先加实例化，那是不是写**Chinese().name**是的，这样写没有错，但是我们没必要这样写呢，我们上面说过self就是类的实例化，所以我们写成**self.name** 就可以调用属性了，类的属性调用前面加**self.属性名**就可以了。self在类中就是Chinese()，我们完全可以把全部的self写成Chinese()，传参时也不会传给他。

\#写了self就隔离开,不写就可以通用? 为啥n可以传入sum不行? 因为n是比较, sum不能在类内改变.



```
    def waysToBuildRooms(self, prevRoom: List[int]) -> int:
        n =  len(prevRoom) #写了self就隔离开,不写就可以通用
        sum = 0 
        def dfs(num:int) -> None:
            if num == n:
                sum +=1
                return 
```



综上，所以我们说self代表的是类的实例本身，方便数据的流转。对此，我们需要记住两点：

第一点：只要在类中用def创建方法时，就必须把第一个参数位置留给 self，并在调用方法时忽略它（不用给self传参）。

第二点**：当在类的方法内部想调用类属性或其他方法时，就要采用self.属性名或self.方法名的格式。**

接下来我们说说类中的初始化

定义初始化方法的格式是def init(self)，是由init加左右两边的【双】下划线组成（ initialize “初始化”的缩写）。

初始化方法的作用在于：实例对象创建时，该方法内的代码无须调用就会自动运行。

### 矩阵

TypeError: list indices must be integers or slices, not tuple

在取矩阵某一列时会出现报错,这是因为此时矩阵存储在列表(list)中，而列表中的每一个元素大小可能不同，因此不能直接取其某一列进行操作

可以利用`numpy.array`函数将其转变为标准矩阵，再对其进行取某一列的操作：

matrix = [[0, 1, 2], [3, 4, 5]] 

matrix = numpy.array(matrix)

 vector = matrix[:, 0] 

print(vector)

运行时处理的时候把self.cx赋成list或者array 非常容易出错!!!

### 切片

https://www.liaoxuefeng.com/wiki/1016959663602400/1017269965565856

 取前3个元素`L[0:3]` 左闭右开

```python
>>> L[-2:] 后两个数
['Bob', 'Jack']
>>> L[-2:-1]
['Bob']
前10个数，每两个取一个：
>>> L[:10:2]
[0, 2, 4, 6, 8]
所有数，每5个取一个：
>>> L[::5]
L[::-1]反转
childs.append(curr_state[:idx - 1] + curr_state[idx:idx + 1] + curr_state[idx - 1:idx] + curr_state[idx + 1:]) 
两行交换, 越界了也不会报错.
交换二维list中两个元素,和np中array不一样.
      curr_state.state[:row] + [
            curr_state.state[row][:col] + curr_state.state[row + 1][col:col + 1] + curr_state.state[row][col + 1:]] + [curr_state.state[row + 1][:col] + curr_state.state[row][col:col + 1] + curr_state.state[row + 1][ col + 1:]] + curr_state.state[row + 2:]
```

### 垃圾回收

python采用的是引用计数机制为主，标记-清除和分代收集（隔代回收）两种机制为辅的策略。

PyObject是每个对象必有的内容，其中ob_refcnt就是做为引用计数。当一个对象有新的引用时，它的ob_refcnt就会增加，当引用它的对象被删除，它的ob_refcnt就会减少

#### **导致引用计数+1的情况**

- 对象被创建，例如a=23
- 对象被引用，例如b=a
- 对象被作为参数，传入到一个函数中，例如`func(a)`
- 对象作为一个元素，存储在容器中，例如`list1=[a,a]`

#### **导致引用计数-1的情况**

- 对象的别名被显式销毁，例如`del a`
- 对象的别名被赋予新的对象，例如`a=24`
- 一个对象离开它的作用域，例如:func函数执行完毕时，func函数中的局部变量（全局变量不会）
- 对象所在的容器被销毁，或从容器中删除对象

#### **分代回收**

- 分代回收是一种以空间换时间的操作方式，Python将内存根据对象的存活时间划分为不同的集合，每个集合称为一个代，Python将内存分为了3“代”，分别为年轻代（第0代）、中年代（第1代）、老年代（第2代），他们对应的是3个链表，它们的垃圾收集频率随着对象存活时间的增大而减小。
- 新创建的对象都会分配在**年轻代**，年轻代链表的总数达到上限时，Python垃圾收集机制就会被触发，把那些可以被回收的对象回收掉，而那些不会回收的对象就会被移到**中年代**去，依此类推，**老年代**中的对象是存活时间最久的对象，甚至是存活于整个系统的生命周期内。
- 同时，分代回收是建立在标记清除技术基础之上。分代回收同样作为Python的辅助垃圾收集技术处理那些容器对象

交换

Python中没有swap()函数,交换两个数的方式

```python
a,b = b,a
```

pycharm 一键注释: ctrl +/

pycharm无法最大化, pycharm最小化打不开。

解决方法: 重装pycharm也不行, 换个项目就可以了.

#### numpy库

```python
np.zeros(shape=(4, 4)) 
x.shape
x = np.array([[1, 2, 3], [4, 5, 6]], np.int32)
y = x[:,1]  就是array([2, 5])
y[0] = 9 # this also changes the corresponding element in x
y
array([9, 5])
x
array([[1, 9, 3],
       [4, 5, 6]])
x.sum(axis=0)
```

 ValueError: operands could not be broadcast together with shapes (0,) (3,)

### 画图

```python
```

### 读取文件夹

```python
import string
import os
for root, dirs, files in os.walk("./data/"):  # os.walk会该目录下的所有文件
    print(files)
    for file in files:
        name = file.split("_")
        score = float(name[0])
        print(score)
```



### 字符串

```python
# 把字符串分割，
>>>['https:', '', 'www.baidu.com', 'pdf', 'abcdefg.pdf']* print(str.split('/'))
# 输出第一段字符串,>>>https:
print(str.split('/')[0])
#合并字符
" ".join(["A","B","C","D"])
'A B C D'
# 翻转字符串三种方法:
str='Runoob'
print(str[::-1])
str='Runoob'
print(''.join(reversed(str)))
str='Runoob'
from functools import reduce
print(reduce(lambda x, y: y + x, str)) #
strip() It returns a new string after removing any leading and trailing whitespaces including tabs (\t).
rstrip():  去除右边空格
排序:
s="abxc"
l1=list(s)     #['a', 'b', 'x', 'c']
l1.sort()      #['a', 'b', 'c', 'x']
s1="".join(l1) #'abcx'
str = '128-312-156'
char_ = '-' # 从头开始找第一个匹配的字符位置
nPos = str.find(char_ )
print(nPos)# 输出 3
# 从尾开始找第一个匹配的字符位置
nPos = str.rfind(char_ )

转ascii码
int()方法将字符转换成ASCII码
可以使用ord()函数和chr()函数进行ASCII码转换。
```

#### 报错

【python报错】Non-ASCII character '\xe5' 

解决方法：
在Python源文件的最开始一行，加入一句：

coding=UTF-8 或者 -*- coding:UTF-8 -*-

[python报错]"IndentationError: unexpected indent"的两三解决方法

这个是缩进错误，我们可以通过下面几步解决他：
首先检查代码是不是有错误的索引
如果没有，全都正确，可以看看是不是使用'''进行了整段的注释，如果是，一定要保证其与上下相邻代码缩进一致，而#就无所谓
如果还有错，使用notepad++打开文件，选择视图->显示符号->显示空格和制表符，然后查看是不是有空格与制表符混用的情况
vim可以用: set list 显示空格和制表符.
unexpected indent 就是说“n”是一个“意外的”缩进。也就是说，这里的问题就是指“n”是一个意外的缩进。通过查看源代码可知这里的确是缩进了一个字符位。
据此推断，我们把这句话的缩进取消，也就是顶格写，

[python报错]出现了AttributeError: object 'L2Cache' has no attribute 'connectCPUSideBus'

  (C++ object is not yet constructed, so wrapped C++ methods are unavail
对象“l2cache”没有属性 ,很多是说不要用跟系统库同样名字,这里则是因为之前的顶格写,导致没有定义到class中去.

【python报错】TypeError: super(type, obj): obj must be an instance or subtype of type

class FooChild(FooParent):
    def __init__(self):
         super(FooChild,self)
 #首先找到 FooChild 的父类（就是类 FooParent），然后把类 FooChild 的对象转换为类 FooParent 的对象

TypeError: 'type' object is not subscriptable

该对象是不可进行下标操作的.NameError: name 'List' is not defined

#### Sccons

Scons是一个开放源码、以Python语言编码的自动化构建工具，可用来替代make编写复杂的makefile。并且scons是跨平台的，只要scons脚本写的好，可以在Linux和Windows下随意编译。
在Java的集成开发环境中，比如Eclipse、IDEA中，有常常有三种与编译相关的选项Compile、Make、Build三个选项。这三个选项最基本的功能都是完成编译过程。但又有很大的区别，区别如下：
1、Compile：只编译选定的目标，不管之前是否已经编译过。

2、Make：编译选定的目标，但是Make只编译上次编译变化过的文件，减少重复劳动，节省时间。（具体怎么检查未变化，这个就不用考虑了，IDE自己内部会搞定这些的）

3、Build：是对整个工程进行彻底的重新编译，而不管是否已经编译过。Build过程往往会生成发布包，这个具体要看对IDE的配置了，Build在实际中应用很少，因为开发时候基本上不用，发布生产时候一般都用ANT等工具来发布。Build因为要全部编译，还要执行打包等额外工作，因此时间较长。
