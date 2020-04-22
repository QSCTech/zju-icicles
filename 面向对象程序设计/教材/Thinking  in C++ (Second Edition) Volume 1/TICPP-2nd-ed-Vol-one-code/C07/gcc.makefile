# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C07
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
	Use \
	Stash3Test \
	UnionClass \
	SuperVar \
	AnonymousUnion \
	MemTest 

test: all 
	Use  
	Stash3Test  
	UnionClass  
	SuperVar  
	AnonymousUnion  
	MemTest  

bugs: 
	@echo No compiler bugs in this directory!

Use: Use.o Def.o 
	$(CPP) $(OFLAG)Use Use.o Def.o 

Stash3Test: Stash3Test.o Stash3.o 
	$(CPP) $(OFLAG)Stash3Test Stash3Test.o Stash3.o 

UnionClass: UnionClass.o 
	$(CPP) $(OFLAG)UnionClass UnionClass.o 

SuperVar: SuperVar.o 
	$(CPP) $(OFLAG)SuperVar SuperVar.o 

AnonymousUnion: AnonymousUnion.o 
	$(CPP) $(OFLAG)AnonymousUnion AnonymousUnion.o 

MemTest: MemTest.o Mem.o 
	$(CPP) $(OFLAG)MemTest MemTest.o Mem.o 


Def.o: Def.cpp 
Use.o: Use.cpp 
Stash3.o: Stash3.cpp Stash3.h ../require.h 
Stash3Test.o: Stash3Test.cpp Stash3.h ../require.h 
UnionClass.o: UnionClass.cpp 
SuperVar.o: SuperVar.cpp 
AnonymousUnion.o: AnonymousUnion.cpp 
Mem.o: Mem.cpp Mem.h 
MemTest.o: MemTest.cpp Mem.h 

