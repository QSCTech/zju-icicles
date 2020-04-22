# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C06
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
	Constructor1 \
	DefineInitialize \
	Nojump \
	Stash2Test \
	Stack3Test \
	Multiarg \
	AutoDefaultConstructor 

test: all 
	Constructor1  
	DefineInitialize  
	Nojump  
	Stash2Test  
	Stack3Test Stack3Test.cpp 
	Multiarg  
	AutoDefaultConstructor  

bugs: 
	@echo No compiler bugs in this directory!

Constructor1: Constructor1.o 
	$(CPP) $(OFLAG)Constructor1 Constructor1.o 

DefineInitialize: DefineInitialize.o 
	$(CPP) $(OFLAG)DefineInitialize DefineInitialize.o 

Nojump: Nojump.o 
	$(CPP) $(OFLAG)Nojump Nojump.o 

Stash2Test: Stash2Test.o Stash2.o 
	$(CPP) $(OFLAG)Stash2Test Stash2Test.o Stash2.o 

Stack3Test: Stack3Test.o Stack3.o 
	$(CPP) $(OFLAG)Stack3Test Stack3Test.o Stack3.o 

Multiarg: Multiarg.o 
	$(CPP) $(OFLAG)Multiarg Multiarg.o 

AutoDefaultConstructor: AutoDefaultConstructor.o 
	$(CPP) $(OFLAG)AutoDefaultConstructor AutoDefaultConstructor.o 


Constructor1.o: Constructor1.cpp 
DefineInitialize.o: DefineInitialize.cpp ../require.h 
Nojump.o: Nojump.cpp 
Stash2.o: Stash2.cpp Stash2.h ../require.h 
Stash2Test.o: Stash2Test.cpp Stash2.h ../require.h 
Stack3.o: Stack3.cpp Stack3.h ../require.h 
Stack3Test.o: Stack3Test.cpp Stack3.h ../require.h 
Multiarg.o: Multiarg.cpp 
AutoDefaultConstructor.o: AutoDefaultConstructor.cpp 

