关于大作业中遇到一些笔记,从0教你怎么编译sodor

sodor

### makefile

automake 读取 Makefile.am 来产生 Makefile.in,
configure 读取 Makefile.in 来产生 Makefile
configure 脚本通常由 autoconf 读取 configure.in 产生
还有aclocal....

目的就是让程序员只写一个规则:.am文件/或.in文件，
就能生成适合各种配置/平台的Makfiles。
如果你写过Makefile，你就知道手工写一个放之四海而皆准的Makefile是多痛苦了。
当然这个Makefile的目的不是编译helloworld之类的小程序，呵呵。

有多个“target”，target之间可以独立，也可以相互关联/依赖，但只能从某一个开始执行，默认情况下就第一个target执行,不过这里第一个target是 all:包含了后面的一些东西 。这里参数 all_targets由一堆子target组成。

```makefile
hello:hello.c
	$(CXX) $^ -o $@    
	翻译出来是“g++ hello.c -o hello”，其中$(CXX) 默认是g++，此处也可以用 $(CC) 默认是cc命令。
	
115行出错 	emulator/%/emulator: $(prerequisites)
	$(MAKE) -C $(dir $@)
	${MAKE} 就是预设的 make 这个命令的名称（或者路径）。这里的 $ (MAKE)就相当于make，-C 选项的作用是指将当前工作目录转移到你所指定的位置。make -p 可以查看所有预定义的变量的当前值。
	"如何让某些命令比如执行但不显示命令的内容？"
	@echo running basedir/Makefile: make run-emulator 就前面加@
```

[Linux 命令详解（三）./configure、make、make install 命令 - Tinywan - 博客园 (cnblogs.com)](https://www.cnblogs.com/tinywan/p/7230039.html)

　　Linux的用户可能知道，在Linux下安装一个应用程序时，一般先运行脚本configure，然后用make来编译源程序，在运行make install，最后运行make clean删除一些临时文件。使用上述三个自动工具，就可以生成configure脚本。运行configure脚本，就可以生成Makefile文件，然后就可以运行make、make install和make clean。



1、configure命令

　　这一步一般用来生成 Makefile，为下一步的编译做准备，你可以通过在 configure 后加上参数来对安装进行控制，比如代码:./configure –prefix=/usr 意思是将该软件安装在 /usr 下面，执行文件就会安装在 /usr/bin （而不是默认的 /usr/local/bin),资源文件就会安装在 /usr/share（而不是默认的/usr/local/share）。同时一些软件的配置文件你可以通过指定 –sys-config= 参数进行设定。有一些软件还可以加上 –with、–enable、–without、–disable 等等参数对编译加以控制，你可以通过允许 ./configure –help 察看详细的说明帮助。

.configure 是有说明书的, 你看到陌生的 .configure就可以 ./configure –help 看他的说明

左键选中, 然后右键就可以 复制bash中的输出. 

make insatll

　　这条命令来进行安装（当然有些软件需要先运行 make check 或 make test 来进行一些测试），这一步一般需要你有 root 权限（因为要向系统写入文件）。

make clean：清除编译产生的可执行文件及目标文件(object file，*.o)。

make 需要 sbt , **`sbt`** 全称为 **`Simple Build Tool`**,是 **`Scala`** 项目中的标准构建工具,类似于 **`Java`** 下的 **`Maven/Groovy`** 中的 **`Gradle`**。由于SBT默认从国外下载依赖，导致第一次构建非常缓慢，使用体验非常糟糕



make run 做了什么:

运行 sbt，Scala 构建工具，选择 rv32 1stage 项目，并运行生成处理器的 Verilog RTL 描述的 Chisel 代码。 生成的 Verilog 代码可以在 emulator/rv32_1stage/generated-src/ 中找到。

 运行verilator，一种将Verilog 编译为周期精确的C++ 仿真代码的开源工具

 将生成的C++ 代码编译为称为模拟器的二进制文件。 

 运行仿真器二进制文件，将提供的 RISC-V 二进制文件加载到模拟内存中。 所有 RISC-V 测试和基准测试都将在调用 \make run 时执行。

有几个方向:

1. 写15行内C语言来编译
2.  定义 一个微码 





