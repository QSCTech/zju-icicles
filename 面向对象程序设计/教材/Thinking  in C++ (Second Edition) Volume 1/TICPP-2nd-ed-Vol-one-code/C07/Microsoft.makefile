# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C07
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
	Use.exe \
	Stash3Test.exe \
	UnionClass.exe \
	SuperVar.exe \
	AnonymousUnion.exe 

test: all 
	Use.exe  
	Stash3Test.exe  
	UnionClass.exe  
	SuperVar.exe  
	AnonymousUnion.exe  

bugs: \
	MemTest.exe 

Use.exe: Use.obj Def.obj 
	$(CPP) $(OFLAG)Use.exe Use.obj Def.obj 

Stash3Test.exe: Stash3Test.obj Stash3.obj 
	$(CPP) $(OFLAG)Stash3Test.exe Stash3Test.obj Stash3.obj 

UnionClass.exe: UnionClass.obj 
	$(CPP) $(OFLAG)UnionClass.exe UnionClass.obj 

SuperVar.exe: SuperVar.obj 
	$(CPP) $(OFLAG)SuperVar.exe SuperVar.obj 

AnonymousUnion.exe: AnonymousUnion.obj 
	$(CPP) $(OFLAG)AnonymousUnion.exe AnonymousUnion.obj 

MemTest.exe: MemTest.obj Mem.obj 
	$(CPP) $(OFLAG)MemTest.exe MemTest.obj Mem.obj 


Def.obj: Def.cpp 
Use.obj: Use.cpp 
Stash3.obj: Stash3.cpp Stash3.h ..\require.h 
Stash3Test.obj: Stash3Test.cpp Stash3.h ..\require.h 
UnionClass.obj: UnionClass.cpp 
SuperVar.obj: SuperVar.cpp 
AnonymousUnion.obj: AnonymousUnion.cpp 
Mem.obj: Mem.cpp Mem.h 
MemTest.obj: MemTest.cpp Mem.h 

