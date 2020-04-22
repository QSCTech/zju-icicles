# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C14
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
	Composition \
	Composition2 \
	Inheritance \
	PseudoConstructor \
	Combined \
	Order \
	NameHiding \
	InheritStack \
	SynthesizedFunctions \
	Car \
	FName1 \
	FName2 \
	PrivateInheritance \
	Protected \
	OperatorInheritance \
	Instrument \
	CopyConstructor \
	InheritStack2 

test: all 
	Composition  
	Composition2  
	Inheritance  
	PseudoConstructor  
	Combined  
	Order  
	NameHiding  
	InheritStack  
	SynthesizedFunctions  
	Car  
	FName1  
	FName2  
	PrivateInheritance  
	Protected  
	OperatorInheritance  
	Instrument  
	CopyConstructor  
	InheritStack2  

bugs: 
	@echo No compiler bugs in this directory!

Composition: Composition.o 
	$(CPP) $(OFLAG)Composition Composition.o 

Composition2: Composition2.o 
	$(CPP) $(OFLAG)Composition2 Composition2.o 

Inheritance: Inheritance.o 
	$(CPP) $(OFLAG)Inheritance Inheritance.o 

PseudoConstructor: PseudoConstructor.o 
	$(CPP) $(OFLAG)PseudoConstructor PseudoConstructor.o 

Combined: Combined.o 
	$(CPP) $(OFLAG)Combined Combined.o 

Order: Order.o 
	$(CPP) $(OFLAG)Order Order.o 

NameHiding: NameHiding.o 
	$(CPP) $(OFLAG)NameHiding NameHiding.o 

InheritStack: InheritStack.o 
	$(CPP) $(OFLAG)InheritStack InheritStack.o 

SynthesizedFunctions: SynthesizedFunctions.o 
	$(CPP) $(OFLAG)SynthesizedFunctions SynthesizedFunctions.o 

Car: Car.o 
	$(CPP) $(OFLAG)Car Car.o 

FName1: FName1.o 
	$(CPP) $(OFLAG)FName1 FName1.o 

FName2: FName2.o 
	$(CPP) $(OFLAG)FName2 FName2.o 

PrivateInheritance: PrivateInheritance.o 
	$(CPP) $(OFLAG)PrivateInheritance PrivateInheritance.o 

Protected: Protected.o 
	$(CPP) $(OFLAG)Protected Protected.o 

OperatorInheritance: OperatorInheritance.o 
	$(CPP) $(OFLAG)OperatorInheritance OperatorInheritance.o 

Instrument: Instrument.o 
	$(CPP) $(OFLAG)Instrument Instrument.o 

CopyConstructor: CopyConstructor.o 
	$(CPP) $(OFLAG)CopyConstructor CopyConstructor.o 

InheritStack2: InheritStack2.o 
	$(CPP) $(OFLAG)InheritStack2 InheritStack2.o 


Composition.o: Composition.cpp Useful.h 
Composition2.o: Composition2.cpp Useful.h 
Inheritance.o: Inheritance.cpp Useful.h 
PseudoConstructor.o: PseudoConstructor.cpp 
Combined.o: Combined.cpp 
Order.o: Order.cpp 
NameHiding.o: NameHiding.cpp 
InheritStack.o: InheritStack.cpp ../C09/Stack4.h ../require.h 
SynthesizedFunctions.o: SynthesizedFunctions.cpp 
Car.o: Car.cpp 
FName1.o: FName1.cpp ../require.h 
FName2.o: FName2.cpp ../require.h 
PrivateInheritance.o: PrivateInheritance.cpp 
Protected.o: Protected.cpp 
OperatorInheritance.o: OperatorInheritance.cpp ../C12/Byte.h 
Instrument.o: Instrument.cpp 
CopyConstructor.o: CopyConstructor.cpp 
InheritStack2.o: InheritStack2.cpp ../C09/Stack4.h ../require.h 

