# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C09
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
	MacroSideEffects.exe \
	Inline.exe \
	Access.exe \
	Rectangle.exe \
	Rectangle2.exe \
	Cpptime.exe \
	Stash4Test.exe \
	Stack4Test.exe \
	EvaluationOrder.exe \
	Hidden.exe \
	Noinsitu.exe \
	ErrTest.exe 

test: all 
	MacroSideEffects.exe  
	Inline.exe  
	Access.exe  
	Rectangle.exe  
	Rectangle2.exe  
	Cpptime.exe  
	Stash4Test.exe  
	Stack4Test.exe Stack4Test.cpp 
	EvaluationOrder.exe  
	Hidden.exe  
	Noinsitu.exe  
	ErrTest.exe ErrTest.cpp 

bugs: 
	@echo No compiler bugs in this directory!

MacroSideEffects.exe: MacroSideEffects.obj 
	$(CPP) $(OFLAG)MacroSideEffects.exe MacroSideEffects.obj 

Inline.exe: Inline.obj 
	$(CPP) $(OFLAG)Inline.exe Inline.obj 

Access.exe: Access.obj 
	$(CPP) $(OFLAG)Access.exe Access.obj 

Rectangle.exe: Rectangle.obj 
	$(CPP) $(OFLAG)Rectangle.exe Rectangle.obj 

Rectangle2.exe: Rectangle2.obj 
	$(CPP) $(OFLAG)Rectangle2.exe Rectangle2.obj 

Cpptime.exe: Cpptime.obj 
	$(CPP) $(OFLAG)Cpptime.exe Cpptime.obj 

Stash4Test.exe: Stash4Test.obj Stash4.obj 
	$(CPP) $(OFLAG)Stash4Test.exe Stash4Test.obj Stash4.obj 

Stack4Test.exe: Stack4Test.obj 
	$(CPP) $(OFLAG)Stack4Test.exe Stack4Test.obj 

EvaluationOrder.exe: EvaluationOrder.obj 
	$(CPP) $(OFLAG)EvaluationOrder.exe EvaluationOrder.obj 

Hidden.exe: Hidden.obj 
	$(CPP) $(OFLAG)Hidden.exe Hidden.obj 

Noinsitu.exe: Noinsitu.obj 
	$(CPP) $(OFLAG)Noinsitu.exe Noinsitu.obj 

ErrTest.exe: ErrTest.obj 
	$(CPP) $(OFLAG)ErrTest.exe ErrTest.obj 


MacroSideEffects.obj: MacroSideEffects.cpp ..\require.h 
Inline.obj: Inline.cpp 
Access.obj: Access.cpp 
Rectangle.obj: Rectangle.cpp 
Rectangle2.obj: Rectangle2.cpp 
Cpptime.obj: Cpptime.cpp Cpptime.h 
Stash4.obj: Stash4.cpp Stash4.h 
Stash4Test.obj: Stash4Test.cpp Stash4.h ..\require.h 
Stack4Test.obj: Stack4Test.cpp Stack4.h ..\require.h 
EvaluationOrder.obj: EvaluationOrder.cpp 
Hidden.obj: Hidden.cpp 
Noinsitu.obj: Noinsitu.cpp 
ErrTest.obj: ErrTest.cpp ..\require.h 

