**直接运行run.sh来编译和运行卷积相关的程序即可，需要先设置riscv有关的路径**

**Usage: ./run.sh 1/2 k1 k2 k3**

#### 运行前需要先设置RV64和RV32的路径和python
```shell
# Setting 
RV32=$HOME/riscv32/riscv-tools/build/bin
RV64=$HOME/riscv64/riscv-tools/build/bin
py=python3
```

#### requirements
>* python3
>* python-pil
>* python-struct
>* bash

#### RGBA数据
编码方式为: w, h, 1024\*2048(r), 1024\*2048(g), 1024\*2048(b), 1024\*2048(a)
>* input.png 原始图片
>* func.c 用到的函数
>* func.h 头文件
>* main.c 主程序
>* read_bin.py 读取二进制文件,生成图片
>* read_image.py 读取图像rgb，生成二进制文件,编码方式为：w, h, 1024\*2048(r), 1024\*2048(g), 1024\*2048(b)

#### result
**RV64**
```shell
~/RV64/build/bin/riscv64-unknown-elf-gcc main.c
~/RV64/build/bin/spike ~/RV64/build/riscv64-unknown-elf/bin/pk -s a.out
```
47040200 ticks  
4604461711 cycles  
4604461710 instructions  
1.00 CPI  


**RV32**
```shell
~/RV32/build/bin/riscv32-unknown-elf-gcc main.c
~/RV32/build/bin/spike ~/RV32/build/riscv64-unknown-elf/bin/pk -s a.out
```
103678800 ticks  
1685615543 cycles  
1685615542 instructions  
1.00 CPI  

