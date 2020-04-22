# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C06
# using the Microsoft compiler
# Note: does not make files that will 
# not compile with this compiler
# Invoke with: make -f Microsoft.makefile

# Note: this requires the service Pack 3 from
# www.Microsoft.com for successful compilation!
# Also, you cannot run the "test" makefiles
# unless you go through and put 'return 0;' at
# the end of every main(), because VC++ does not
# follow the C++ Standard for defaulting return
# values from main().
CPP = cl
CPPFLAGS = -GX -GR
OFLAG = -o
.SUFFIXES : .obj .cpp .c
.cpp.obj :
	$(CPP) $(CPPFLAGS) -c $<
.c.obj :
	$(CPP) $(CPPFLAGS) -c $<

all: \
	Constructor1.exe \
	DefineInitialize.exe \
	Nojump.exe \
	Stash2Test.exe \
	Stack3Test.exe \
	Multiarg.exe \
	AutoDefaultConstructor.exe 

test: all 
	Constructor1.exe  
	DefineInitialize.exe  
	Nojump.exe  
	Stash2Test.exe  
	Stack3Test.exe Stack3Test.cpp 
	Multiarg.exe  
	AutoDefaultConstructor.exe  

bugs: 
	@echo No compiler bugs in this directory!

Constructor1.exe: Constructor1.obj 
	$(CPP) $(OFLAG)Constructor1.exe Constructor1.obj 

DefineInitialize.exe: DefineInitialize.obj 
	$(CPP) $(OFLAG)DefineInitialize.exe DefineInitialize.obj 

Nojump.exe: Nojump.obj 
	$(CPP) $(OFLAG)Nojump.exe Nojump.obj 

Stash2Test.exe: Stash2Test.obj Stash2.obj 
	$(CPP) $(OFLAG)Stash2Test.exe Stash2Test.obj Stash2.obj 

Stack3Test.exe: Stack3Test.obj Stack3.obj 
	$(CPP) $(OFLAG)Stack3Test.exe Stack3Test.obj Stack3.obj 

Multiarg.exe: Multiarg.obj 
	$(CPP) $(OFLAG)Multiarg.exe Multiarg.obj 

AutoDefaultConstructor.exe: AutoDefaultConstructor.obj 
	$(CPP) $(OFLAG)AutoDefaultConstructor.exe AutoDefaultConstructor.obj 


Constructor1.obj: Constructor1.cpp 
DefineInitialize.obj: DefineInitialize.cpp ..\require.h 
Nojump.obj: Nojump.cpp 
Stash2.obj: Stash2.cpp Stash2.h ..\require.h 
Stash2Test.obj: Stash2Test.cpp Stash2.h ..\require.h 
Stack3.obj: Stack3.cpp Stack3.h ..\require.h 
Stack3Test.obj: Stack3Test.cpp Stack3.h ..\require.h 
Multiarg.obj: Multiarg.cpp 
AutoDefaultConstructor.obj: AutoDefaultConstructor.cpp 

