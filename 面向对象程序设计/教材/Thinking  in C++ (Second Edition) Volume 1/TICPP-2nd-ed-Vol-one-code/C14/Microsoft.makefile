# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C14
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
	Composition.exe \
	Composition2.exe \
	Inheritance.exe \
	PseudoConstructor.exe \
	Combined.exe \
	Order.exe \
	NameHiding.exe \
	InheritStack.exe \
	SynthesizedFunctions.exe \
	Car.exe \
	FName1.exe \
	FName2.exe \
	PrivateInheritance.exe \
	Protected.exe \
	OperatorInheritance.exe \
	Instrument.exe \
	CopyConstructor.exe \
	InheritStack2.exe 

test: all 
	Composition.exe  
	Composition2.exe  
	Inheritance.exe  
	PseudoConstructor.exe  
	Combined.exe  
	Order.exe  
	NameHiding.exe  
	InheritStack.exe  
	SynthesizedFunctions.exe  
	Car.exe  
	FName1.exe  
	FName2.exe  
	PrivateInheritance.exe  
	Protected.exe  
	OperatorInheritance.exe  
	Instrument.exe  
	CopyConstructor.exe  
	InheritStack2.exe  

bugs: 
	@echo No compiler bugs in this directory!

Composition.exe: Composition.obj 
	$(CPP) $(OFLAG)Composition.exe Composition.obj 

Composition2.exe: Composition2.obj 
	$(CPP) $(OFLAG)Composition2.exe Composition2.obj 

Inheritance.exe: Inheritance.obj 
	$(CPP) $(OFLAG)Inheritance.exe Inheritance.obj 

PseudoConstructor.exe: PseudoConstructor.obj 
	$(CPP) $(OFLAG)PseudoConstructor.exe PseudoConstructor.obj 

Combined.exe: Combined.obj 
	$(CPP) $(OFLAG)Combined.exe Combined.obj 

Order.exe: Order.obj 
	$(CPP) $(OFLAG)Order.exe Order.obj 

NameHiding.exe: NameHiding.obj 
	$(CPP) $(OFLAG)NameHiding.exe NameHiding.obj 

InheritStack.exe: InheritStack.obj 
	$(CPP) $(OFLAG)InheritStack.exe InheritStack.obj 

SynthesizedFunctions.exe: SynthesizedFunctions.obj 
	$(CPP) $(OFLAG)SynthesizedFunctions.exe SynthesizedFunctions.obj 

Car.exe: Car.obj 
	$(CPP) $(OFLAG)Car.exe Car.obj 

FName1.exe: FName1.obj 
	$(CPP) $(OFLAG)FName1.exe FName1.obj 

FName2.exe: FName2.obj 
	$(CPP) $(OFLAG)FName2.exe FName2.obj 

PrivateInheritance.exe: PrivateInheritance.obj 
	$(CPP) $(OFLAG)PrivateInheritance.exe PrivateInheritance.obj 

Protected.exe: Protected.obj 
	$(CPP) $(OFLAG)Protected.exe Protected.obj 

OperatorInheritance.exe: OperatorInheritance.obj 
	$(CPP) $(OFLAG)OperatorInheritance.exe OperatorInheritance.obj 

Instrument.exe: Instrument.obj 
	$(CPP) $(OFLAG)Instrument.exe Instrument.obj 

CopyConstructor.exe: CopyConstructor.obj 
	$(CPP) $(OFLAG)CopyConstructor.exe CopyConstructor.obj 

InheritStack2.exe: InheritStack2.obj 
	$(CPP) $(OFLAG)InheritStack2.exe InheritStack2.obj 


Composition.obj: Composition.cpp Useful.h 
Composition2.obj: Composition2.cpp Useful.h 
Inheritance.obj: Inheritance.cpp Useful.h 
PseudoConstructor.obj: PseudoConstructor.cpp 
Combined.obj: Combined.cpp 
Order.obj: Order.cpp 
NameHiding.obj: NameHiding.cpp 
InheritStack.obj: InheritStack.cpp ..\C09\Stack4.h ..\require.h 
SynthesizedFunctions.obj: SynthesizedFunctions.cpp 
Car.obj: Car.cpp 
FName1.obj: FName1.cpp ..\require.h 
FName2.obj: FName2.cpp ..\require.h 
PrivateInheritance.obj: PrivateInheritance.cpp 
Protected.obj: Protected.cpp 
OperatorInheritance.obj: OperatorInheritance.cpp ..\C12\Byte.h 
Instrument.obj: Instrument.cpp 
CopyConstructor.obj: CopyConstructor.cpp 
InheritStack2.obj: InheritStack2.cpp ..\C09\Stack4.h ..\require.h 

