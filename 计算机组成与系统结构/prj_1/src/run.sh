#! /bin/bash

if [ $# != 4 ]
then
  echo -e "\033[35mPlease input the type of compiler, k1, k2, k3,\033[0m"
  echo -e "\033[36mUsgae: ./run.sh 1(riscv32-gcc)/2(riscv64-gcc) 0.4 0.2 0.4\033[0m"
  exit
fi

# Setting 
RV32=$HOME/riscv32/riscv-tools/build/bin
RV64=$HOME/riscv64/riscv-tools/build/bin
py=python3


# 1. 从图像读取rgb值到文件中
echo -e "\033[31mSection.1 Reading RGB data frome input.png... \033[0m"
$py read_image.py input.png in.bin



# 2. 编译c程序
echo -e "\033[31mSection.2 Compiling source codes... \033[0m"
if [ $1 == 1 ]
then
  $RV32/riscv32-unknown-elf-gcc main.c -o conv_32.app  
  $RV32/riscv32-unknown-elf-gcc -S main.c
  mv main.s conv_32.s
else
  $RV64/riscv64-unknown-elf-gcc main.c -o conv_64.app  
  $RV64/riscv64-unknown-elf-gcc -S main.c  
  mv main.s conv_64.s
fi



# 3. 运行c程序
echo -e "\033[31mSection.3 Running conv.app... \033[0m"
touch y.bin
echo -e "\033[47;34m"
if [ $1 == 1 ] 
then
  time $RV32/spike pk conv_32.app in.bin y.bin $2 $3 $4
else 
  time $RV64/spike pk conv_64.app in.bin y.bin $2 $3 $4
fi
echo -e "\033[0m"
rm -rf in.bin
rm -rf output
mkdir output
echo ""



# 4. 生成图像
echo -e "\033[31mSection.4 Building image... \033[0m"
$py read_bin.py y.bin
rm -rf y.bin




# 5. 显示结果
echo ""
echo -e '\033[47;34m$ ls --color=auto -t\033[0m'
ls --color=auto -t 
echo ""
echo -e "\033[31mThe processed images are now in the output directory.\033[0m"
echo -e '\033[47;34m$ ls --color=auto -t output/\033[0m'
ls --color=auto -t output/
