# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C04
# using the gcc compiler
# Note: does not make files that will 
# not compile with this compiler
# Invoke with: make -f gcc.makefile

CPP = g++
OFLAG = -o
.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) $(CPPFLAGS) -c $<
.c.o :
	$(CPP) $(CPPFLAGS) -c $<

all: \
	CLibTest \
	CppLibTest \
	Sizeof \
	StackTest \
	Scoperes 

test: all 
	CLibTest  
	CppLibTest  
	Sizeof  
	StackTest StackTest.cpp 
	Scoperes  

bugs: 
	@echo No compiler bugs in this directory!

CLibTest: CLibTest.o CLib.o 
	$(CPP) $(OFLAG)CLibTest CLibTest.o CLib.o 

CppLibTest: CppLibTest.o CppLib.o 
	$(CPP) $(OFLAG)CppLibTest CppLibTest.o CppLib.o 

Sizeof: Sizeof.o 
	$(CPP) $(OFLAG)Sizeof Sizeof.o 

StackTest: StackTest.o Stack.o 
	$(CPP) $(OFLAG)StackTest StackTest.o Stack.o 

Scoperes: Scoperes.o 
	$(CPP) $(OFLAG)Scoperes Scoperes.o 


CLib.o: CLib.cpp CLib.h 
CLibTest.o: CLibTest.cpp CLib.h 
CppLib.o: CppLib.cpp CppLib.h 
CppLibTest.o: CppLibTest.cpp CppLib.h ../require.h 
Sizeof.o: Sizeof.cpp CLib.h CppLib.h 
Stack.o: Stack.cpp Stack.h ../require.h 
StackTest.o: StackTest.cpp Stack.h ../require.h 
Scoperes.o: Scoperes.cpp 

