## chipyard和一些任务

## chipyard

chipyard好像能直接配置一个cpu核

chipyard里面有  boom 和 rocket

documentation包含了chipyard的基本思想和用法，但没有chisel代码相关的内容。

需要用chisel写好各个基础部件（比如cpu、fpu等）然后在一个scala文件中进行组合（也称配置）。chipyard工具链可以编译该配置文件。

Chipyard’s documentation: https://chipyard.readthedocs.io/en/dev/index.html

- If you intend to run a simulation of one of the vanilla Chipyard examples, go to [Software RTL Simulation](https://chipyard.readthedocs.io/en/latest/Simulation/Software-RTL-Simulation.html#sw-rtl-sim-intro) and follow the instructions.
- If you intend to run a simulation of a custom Chipyard SoC Configuration, go to [Simulating A Custom Project](https://chipyard.readthedocs.io/en/latest/Simulation/Software-RTL-Simulation.html#simulating-a-custom-project) and follow the instructions.
- If you intend to add a new accelerator, go to [Basic customization](https://docs.python.org/3/reference/datamodel.html#customization) and follow the instructions.
- If you want to learn about the structure of Chipyard, go to [Chipyard Components](https://chipyard.readthedocs.io/en/latest/Chipyard-Basics/Chipyard-Components.html#chipyard-components).
- If you intend to change the generators (BOOM, Rocket, etc) themselves, see [Included RTL Generators](https://chipyard.readthedocs.io/en/latest/Generators/index.html#generator-index).
- If you intend to run a tutorial VLSI flow using one of the Chipyard examples, go to [ASAP7 Tutorial](https://chipyard.readthedocs.io/en/latest/VLSI/Tutorial.html#tutorial) and follow the instructions.
- If you intend to build a chip using one of the vanilla Chipyard examples, go to [Building A Chip](https://chipyard.readthedocs.io/en/latest/VLSI/Building-A-Chip.html#build-a-chip) and follow the instructions.

用Verilator编译生成可执行文件:https://www.veripool.org/verilator/

https://github.com/ucb-bar/riscv-sodor这是chipyard关于sodor的官方仓库

1.找到生成32位riscv文件的方法可参考网页

我使用的编译链接命令 https://blog.csdn.net/l471094842/article/details/108118939

报告可以参考这个:

https://blog.csdn.net/weixin_30832405/article/details/99880180

基于五阶段流水线的RISC-V CPU模拟器实现

github上相关的提问与解答

https://stackoverflow.com/questions/46732729/gcc-7-1-1-riscv-compilation-link-failures-incompatible-abi

https://github.com/riscv/riscv-tools/issues/310

https://github.com/riscv/riscv-tools/issues/287

测试的可能方向：

1.testbench自己能测出来各种指标，这个会导致testbench的接口更加复杂，testbench的汇编内容更复杂。且裁剪数据通路需要根据testbench进行裁剪。

问题：没有生成riscv32文件的工具，可能没办法测hazard之类的数据。  已经有了, 就gcc就可以生成,

2.使用现有的模拟器比如qemu进行测试。可能是用./qemu file.riscv这样的指令进行的，类似于这样的

这样的话就可以直接根据没有接口的矩阵乘法汇编进行数据通路裁剪。

问题：还不会使用，也不确定这种模拟器的功能能到哪种程度；同样需要riscv32位的工具生成矩阵乘法的可执行文件。 不用qemu,

所以无论哪个方向都需要生成32位riscv可执行文件的工具

3 一个人可以https://docs.boom-core.org/en/latest/sections/parameterization.html#sample-configurations

https://docs.boom-core.org/en/latest/sections/parameterization.html

hzp 乘法器用scala编译了,

estbench里面有mul是因为riscv32 tool的架构选的是rv32imc,

把架构换成rv32i重新编译一下工具链,.riscv里面没有mul和div了

6.14日, 可以testbench自己计时测得, 只能测cpi , 但是不是嵌在datapath里面的print , 只有用嵌在datapath里面的print，然后统计输出的命令，才能测分支预测这些

我们想测自己mul程序的brnach predict ,所以想要看一下怎么用嵌在datapath里面的print，然后统计输出的命令，才能测分支预测这些

我需要  看project1 ,这里有

最好能弄出这个4-Designing-a-custom-RISC-V-core-using-Chisel-Alex-Badicioiu-NXP



# 一些QA

1.没有chisel代码的细节  其实是有的, 就在源代码里, 然后文档也有.

2.使用chipyard的方法  文档里也有, 就是费时间多试试.

1. cpu需要自己写吗? 还是直接用已经有的代码?   cpu可以自己写,我们是用sodor 改进.  加个cache
2. **仿真工具的选择**Chipyard（包括Rocket-Chip）项目支持使用Verilator或Synopsys VCS进行精确到时钟周期的仿真。前者是可免费使用的开源软件，本文接下来介绍一下如何使用开源的Verilator进行仿真。 老师有推荐什么仿真吗？[RISC-V的“Demo”级项目——Rocket-chip](https://zhuanlan.zhihu.com/p/140360043)　 用spike测试.
3. chip yard自带的chisel代码都跑不通 ,make就会出问题.   虚拟机内存调大到16g才行.  其实文档里也都有, rocketchip就要 6.5gb 内存.

6.我不知道soc 生成器和加速器有什么区别？ 加速器是gimmi , 可以挂在cpu上. soc生成器可以直接生成cpu 的verilog代码.

1. 怎么精简指令集:    有一个生成riscv核心, 应该可以配置一下让他只生成需要的指令.  我们是打算精简数据通路, 然后
2. 怎么make