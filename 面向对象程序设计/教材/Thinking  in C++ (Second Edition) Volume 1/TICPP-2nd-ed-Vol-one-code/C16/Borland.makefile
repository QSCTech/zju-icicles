# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C16
# using the Borland compiler
# Note: does not make files that will 
# not compile with this compiler
# Invoke with: make -f Borland.makefile

CPP = Bcc32
CPPFLAGS = -w-inl -w-csu -wnak
OFLAG = -e
.SUFFIXES : .obj .cpp .c
.cpp.obj :
	$(CPP) $(CPPFLAGS) -c $<
.c.obj :
	$(CPP) $(CPPFLAGS) -c $<

all: \
	IntStack.exe \
	Array.exe \
	Array2.exe \
	StackTemplateTest.exe \
	Array3.exe \
	TStackTest.exe \
	TPStashTest.exe \
	OwnerStackTest.exe \
	ValueStackTest.exe \
	IterIntStack.exe \
	NestedIterator.exe \
	IterStackTemplateTest.exe \
	TStack2Test.exe \
	TPStash2Test.exe \
	Drawing.exe 

test: all 
	IntStack.exe  
	Array.exe  
	Array2.exe  
	StackTemplateTest.exe  
	Array3.exe  
	TStackTest.exe TStackTest.cpp 
	TPStashTest.exe  
	OwnerStackTest.exe  
	ValueStackTest.exe  
	IterIntStack.exe  
	NestedIterator.exe  
	IterStackTemplateTest.exe  
	TStack2Test.exe  
	TPStash2Test.exe  
	Drawing.exe  

bugs: 
	@echo No compiler bugs in this directory!

IntStack.exe: IntStack.obj fibonacci.obj 
	$(CPP) $(OFLAG)IntStack.exe IntStack.obj fibonacci.obj 

Array.exe: Array.obj 
	$(CPP) $(OFLAG)Array.exe Array.obj 

Array2.exe: Array2.obj 
	$(CPP) $(OFLAG)Array2.exe Array2.obj 

StackTemplateTest.exe: StackTemplateTest.obj fibonacci.obj 
	$(CPP) $(OFLAG)StackTemplateTest.exe StackTemplateTest.obj fibonacci.obj 

Array3.exe: Array3.obj 
	$(CPP) $(OFLAG)Array3.exe Array3.obj 

TStackTest.exe: TStackTest.obj 
	$(CPP) $(OFLAG)TStackTest.exe TStackTest.obj 

TPStashTest.exe: TPStashTest.obj AutoCounter.obj 
	$(CPP) $(OFLAG)TPStashTest.exe TPStashTest.obj AutoCounter.obj 

OwnerStackTest.exe: OwnerStackTest.obj AutoCounter.obj 
	$(CPP) $(OFLAG)OwnerStackTest.exe OwnerStackTest.obj AutoCounter.obj 

ValueStackTest.exe: ValueStackTest.obj SelfCounter.obj 
	$(CPP) $(OFLAG)ValueStackTest.exe ValueStackTest.obj SelfCounter.obj 

IterIntStack.exe: IterIntStack.obj fibonacci.obj 
	$(CPP) $(OFLAG)IterIntStack.exe IterIntStack.obj fibonacci.obj 

NestedIterator.exe: NestedIterator.obj fibonacci.obj 
	$(CPP) $(OFLAG)NestedIterator.exe NestedIterator.obj fibonacci.obj 

IterStackTemplateTest.exe: IterStackTemplateTest.obj fibonacci.obj 
	$(CPP) $(OFLAG)IterStackTemplateTest.exe IterStackTemplateTest.obj fibonacci.obj 

TStack2Test.exe: TStack2Test.obj 
	$(CPP) $(OFLAG)TStack2Test.exe TStack2Test.obj 

TPStash2Test.exe: TPStash2Test.obj 
	$(CPP) $(OFLAG)TPStash2Test.exe TPStash2Test.obj 

Drawing.exe: Drawing.obj 
	$(CPP) $(OFLAG)Drawing.exe Drawing.obj 


IntStack.obj: IntStack.cpp fibonacci.h ..\require.h 
fibonacci.obj: fibonacci.cpp ..\require.h 
Array.obj: Array.cpp ..\require.h 
Array2.obj: Array2.cpp ..\require.h 
StackTemplateTest.obj: StackTemplateTest.cpp fibonacci.h StackTemplate.h 
Array3.obj: Array3.cpp ..\require.h 
TStackTest.obj: TStackTest.cpp TStack.h ..\require.h 
AutoCounter.obj: AutoCounter.cpp AutoCounter.h 
TPStashTest.obj: TPStashTest.cpp AutoCounter.h TPStash.h 
OwnerStackTest.obj: OwnerStackTest.cpp AutoCounter.h OwnerStack.h ..\require.h 
SelfCounter.obj: SelfCounter.cpp SelfCounter.h 
ValueStackTest.obj: ValueStackTest.cpp ValueStack.h SelfCounter.h 
IterIntStack.obj: IterIntStack.cpp fibonacci.h ..\require.h 
NestedIterator.obj: NestedIterator.cpp fibonacci.h ..\require.h 
IterStackTemplateTest.obj: IterStackTemplateTest.cpp fibonacci.h IterStackTemplate.h 
TStack2Test.obj: TStack2Test.cpp TStack2.h ..\require.h 
TPStash2Test.obj: TPStash2Test.cpp TPStash2.h ..\require.h 
Drawing.obj: Drawing.cpp TPStash2.h TStack2.h Shape.h 

