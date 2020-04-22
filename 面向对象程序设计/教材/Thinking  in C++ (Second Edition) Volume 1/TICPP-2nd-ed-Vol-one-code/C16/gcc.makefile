# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C16
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
	IntStack \
	Array \
	Array2 \
	StackTemplateTest \
	Array3 \
	TStackTest \
	TPStashTest \
	OwnerStackTest \
	ValueStackTest \
	IterIntStack \
	NestedIterator \
	IterStackTemplateTest \
	TStack2Test \
	TPStash2Test \
	Drawing 

test: all 
	IntStack  
	Array  
	Array2  
	StackTemplateTest  
	Array3  
	TStackTest TStackTest.cpp 
	TPStashTest  
	OwnerStackTest  
	ValueStackTest  
	IterIntStack  
	NestedIterator  
	IterStackTemplateTest  
	TStack2Test  
	TPStash2Test  
	Drawing  

bugs: 
	@echo No compiler bugs in this directory!

IntStack: IntStack.o fibonacci.o 
	$(CPP) $(OFLAG)IntStack IntStack.o fibonacci.o 

Array: Array.o 
	$(CPP) $(OFLAG)Array Array.o 

Array2: Array2.o 
	$(CPP) $(OFLAG)Array2 Array2.o 

StackTemplateTest: StackTemplateTest.o fibonacci.o 
	$(CPP) $(OFLAG)StackTemplateTest StackTemplateTest.o fibonacci.o 

Array3: Array3.o 
	$(CPP) $(OFLAG)Array3 Array3.o 

TStackTest: TStackTest.o 
	$(CPP) $(OFLAG)TStackTest TStackTest.o 

TPStashTest: TPStashTest.o AutoCounter.o 
	$(CPP) $(OFLAG)TPStashTest TPStashTest.o AutoCounter.o 

OwnerStackTest: OwnerStackTest.o AutoCounter.o 
	$(CPP) $(OFLAG)OwnerStackTest OwnerStackTest.o AutoCounter.o 

ValueStackTest: ValueStackTest.o SelfCounter.o 
	$(CPP) $(OFLAG)ValueStackTest ValueStackTest.o SelfCounter.o 

IterIntStack: IterIntStack.o fibonacci.o 
	$(CPP) $(OFLAG)IterIntStack IterIntStack.o fibonacci.o 

NestedIterator: NestedIterator.o fibonacci.o 
	$(CPP) $(OFLAG)NestedIterator NestedIterator.o fibonacci.o 

IterStackTemplateTest: IterStackTemplateTest.o fibonacci.o 
	$(CPP) $(OFLAG)IterStackTemplateTest IterStackTemplateTest.o fibonacci.o 

TStack2Test: TStack2Test.o 
	$(CPP) $(OFLAG)TStack2Test TStack2Test.o 

TPStash2Test: TPStash2Test.o 
	$(CPP) $(OFLAG)TPStash2Test TPStash2Test.o 

Drawing: Drawing.o 
	$(CPP) $(OFLAG)Drawing Drawing.o 


IntStack.o: IntStack.cpp fibonacci.h ../require.h 
fibonacci.o: fibonacci.cpp ../require.h 
Array.o: Array.cpp ../require.h 
Array2.o: Array2.cpp ../require.h 
StackTemplateTest.o: StackTemplateTest.cpp fibonacci.h StackTemplate.h 
Array3.o: Array3.cpp ../require.h 
TStackTest.o: TStackTest.cpp TStack.h ../require.h 
AutoCounter.o: AutoCounter.cpp AutoCounter.h 
TPStashTest.o: TPStashTest.cpp AutoCounter.h TPStash.h 
OwnerStackTest.o: OwnerStackTest.cpp AutoCounter.h OwnerStack.h ../require.h 
SelfCounter.o: SelfCounter.cpp SelfCounter.h 
ValueStackTest.o: ValueStackTest.cpp ValueStack.h SelfCounter.h 
IterIntStack.o: IterIntStack.cpp fibonacci.h ../require.h 
NestedIterator.o: NestedIterator.cpp fibonacci.h ../require.h 
IterStackTemplateTest.o: IterStackTemplateTest.cpp fibonacci.h IterStackTemplate.h 
TStack2Test.o: TStack2Test.cpp TStack2.h ../require.h 
TPStash2Test.o: TPStash2Test.cpp TPStash2.h ../require.h 
Drawing.o: Drawing.cpp TPStash2.h TStack2.h Shape.h 

