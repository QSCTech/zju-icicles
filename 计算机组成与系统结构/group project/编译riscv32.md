# 编译riscv32

怎么编译https://blog.csdn.net/l471094842/article/details/108118939

https://www.riscv-mcu.com/article-article-show-id-122.html

https://www.sohu.com/a/394843697_505803

riscv gcc可以编译成以下几个版本

- riscv32-unknown-elf-gcc
- riscv64-unknown-elf-gcc
- riscv32-unknown-linux-gnu-gcc 这个报错 can't link soft-float modules with double-float modules
- riscv64-unknown-linux-gnu-gcc
- riscv64-multilib-elf-gcc 这个据说可以32位
- riscv64-liunx-multilib-gcc

```c
riscv32-unknown-elf-gcc 用这个编译
```

### riscv32-unknown-linux-gnu-gcc

该工具针对riscv32架构的编译器，使用的C运行库为linux中的标准glibc。我也不知道和 -elf有啥区别?

区别: elf-gcc是静态链接，linux-gnu-gcc是动态链接

```c
root@f550c67bf4ea:/opt/riscv/bin# riscv32-unknown-linux-gnu-gcc -v
Using built-in specs.
COLLECT_GCC=riscv32-unknown-linux-gnu-gcc
COLLECT_LTO_WRAPPER=/opt/riscv/libexec/gcc/riscv32-unknown-linux-gnu/10.2.0/lto-wrapper
Target: riscv32-unknown-linux-gnu
Configured with: /riscv-gnu-toolchain/riscv-gcc/configure --target=riscv32-unknown-linux-gnu --prefix=/opt/riscv --with-sysroot=/opt/riscv/sysroot --with-system-zlib --enable-shared --enable-tls --enable-languages=c,c++,fortran --disable-libmudflap --disable-libssp --disable-libquadmath --disable-libsanitizer --disable-nls --disable-bootstrap --src=.././riscv-gcc --disable-multilib --with-abi=ilp32d --with-arch=rv32gc --with-tune=rocket 'CFLAGS_FOR_TARGET=-O2   -mcmodel=medlow' 'CXXFLAGS_FOR_TARGET=-O2   -mcmodel=medlow'
Thread model: posix
Supported LTO compression algorithms: zlib
gcc version 10.2.0 (GCC)
march=rv32imac -mabi=ilp32 -o file file.c
```

报错

/opt/riscv/lib/gcc/riscv32-unknown-linux-gnu/10.2.0/../../../../riscv32-unknown-linux-gnu/bin/ld: /tmp/cc9EwS9A.o: can't link soft-float modules with double-float modules /opt/riscv/lib/gcc/riscv32-unknown-linux-gnu/10.2.0/../../../../riscv32-unknown-linux-gnu/bin/ld: failed to merge target specific data of file /tmp/cc9EwS9A.o collect2: error: ld returned 1 exit status

github有issue: It's because your C library still using hard floating-point instruction, so I would suggest you re-build toolchain with --with-arch=rv32i --with-abi=ilp32 or enable multi-lib via

[can't link double-float modules with soft-float modules riscv compiler](https://stackoverflow.com/questions/65036779/cant-link-double-float-modules-with-soft-float-modules-riscv-compiler)

readelf -h 可以看the exact arch and ABI（应用程序二进制接口）of your library . 看到了abi是 unix-system V. version 0. 但是不知道arch看哪个.  也有一个回答说加参数msoft-float 有用, 但是不知道怎么加. -msoft-float 不行 ,  mfloat-abi=softfp 也不行

### 尝试2

```c
矩阵相乘代码
#include<stdio.h>
int main(){
  printf("hello world!\\n");
}
```

clang好像也不太行,问题是sysroot不存在,  所以缺乏依赖, link时出错

```c
root@77e8d4f6684c:~# clang-9 -v
clang version 9.0.0 ([<https://github.com/llvm/llvm-project.git>](<https://github.com/llvm/llvm-project.git>) 0399d5a9682b3cef71c653373e38890c63c4c365)
Target: riscv32-unknown-unknown-elf
Thread model: posix
InstalledDir: /opt/riscv32-unknown-elf/bin
报错 
/usr/riscv32-unknown-elf/bin/riscv32-unknown-elf-ld: cannot find crt0.o: No such file or directory
/usr/riscv32-unknown-elf/bin/riscv32-unknown-elf-ld: cannot find crtbegin.o: No such file or directory
/usr/riscv32-unknown-elf/bin/riscv32-unknown-elf-ld: cannot find -lc
/usr/riscv32-unknown-elf/bin/riscv32-unknown-elf-ld: cannot find -lgloss
clang-9: error: ld command failed with exit code 1 (use -v to see invocation)
```

### 尝试3

clang hello.c -o hello

欸怎么可以了.神奇.c我把编译不出来的部分都删除了.产生可执行的.但是不知道是不是一样

不尝试了, 都做出来了. 是直接用riscv-test自带的makefile 修改了一些option生成的

下了riscv-gnu-toolchain，编译了riscv32-unknown-elf-gcc

接下来就是需要 接口函数,  某些能够通过串口打印出cpu运行状态的函数.原来32位的makefile不考虑那些接口函数的位置, 还得改