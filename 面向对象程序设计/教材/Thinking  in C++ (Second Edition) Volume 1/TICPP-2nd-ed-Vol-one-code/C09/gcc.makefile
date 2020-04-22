# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C09
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
	MacroSideEffects \
	Inline \
	Access \
	Rectangle \
	Rectangle2 \
	Cpptime \
	Stash4Test \
	Stack4Test \
	EvaluationOrder \
	Hidden \
	Noinsitu \
	ErrTest 

test: all 
	MacroSideEffects  
	Inline  
	Access  
	Rectangle  
	Rectangle2  
	Cpptime  
	Stash4Test  
	Stack4Test Stack4Test.cpp 
	EvaluationOrder  
	Hidden  
	Noinsitu  
	ErrTest ErrTest.cpp 

bugs: 
	@echo No compiler bugs in this directory!

MacroSideEffects: MacroSideEffects.o 
	$(CPP) $(OFLAG)MacroSideEffects MacroSideEffects.o 

Inline: Inline.o 
	$(CPP) $(OFLAG)Inline Inline.o 

Access: Access.o 
	$(CPP) $(OFLAG)Access Access.o 

Rectangle: Rectangle.o 
	$(CPP) $(OFLAG)Rectangle Rectangle.o 

Rectangle2: Rectangle2.o 
	$(CPP) $(OFLAG)Rectangle2 Rectangle2.o 

Cpptime: Cpptime.o 
	$(CPP) $(OFLAG)Cpptime Cpptime.o 

Stash4Test: Stash4Test.o Stash4.o 
	$(CPP) $(OFLAG)Stash4Test Stash4Test.o Stash4.o 

Stack4Test: Stack4Test.o 
	$(CPP) $(OFLAG)Stack4Test Stack4Test.o 

EvaluationOrder: EvaluationOrder.o 
	$(CPP) $(OFLAG)EvaluationOrder EvaluationOrder.o 

Hidden: Hidden.o 
	$(CPP) $(OFLAG)Hidden Hidden.o 

Noinsitu: Noinsitu.o 
	$(CPP) $(OFLAG)Noinsitu Noinsitu.o 

ErrTest: ErrTest.o 
	$(CPP) $(OFLAG)ErrTest ErrTest.o 


MacroSideEffects.o: MacroSideEffects.cpp ../require.h 
Inline.o: Inline.cpp 
Access.o: Access.cpp 
Rectangle.o: Rectangle.cpp 
Rectangle2.o: Rectangle2.cpp 
Cpptime.o: Cpptime.cpp Cpptime.h 
Stash4.o: Stash4.cpp Stash4.h 
Stash4Test.o: Stash4Test.cpp Stash4.h ../require.h 
Stack4Test.o: Stack4Test.cpp Stack4.h ../require.h 
EvaluationOrder.o: EvaluationOrder.cpp 
Hidden.o: Hidden.cpp 
Noinsitu.o: Noinsitu.cpp 
ErrTest.o: ErrTest.cpp ../require.h 

