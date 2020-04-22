# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C11
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
	FreeStandingReferences \
	Reference \
	ConstReferenceArguments \
	ReferenceToPointer \
	PassingBigStructures \
	HowMany \
	HowMany2 \
	Linenum \
	DefaultCopyConstructor \
	NoCopyConstruction \
	SimpleStructure \
	PointerToMemberData \
	PmemFunDefinition \
	PointerToMemberFunction \
	PointerToMemberFunction2 

test: all 
	FreeStandingReferences  
	Reference  
	ConstReferenceArguments  
	ReferenceToPointer  
	PassingBigStructures  
	HowMany  
	HowMany2  
	Linenum Linenum.cpp 
	DefaultCopyConstructor  
	NoCopyConstruction  
	SimpleStructure  
	PointerToMemberData  
	PmemFunDefinition  
	PointerToMemberFunction  
	PointerToMemberFunction2  

bugs: 
	@echo No compiler bugs in this directory!

FreeStandingReferences: FreeStandingReferences.o 
	$(CPP) $(OFLAG)FreeStandingReferences FreeStandingReferences.o 

Reference: Reference.o 
	$(CPP) $(OFLAG)Reference Reference.o 

ConstReferenceArguments: ConstReferenceArguments.o 
	$(CPP) $(OFLAG)ConstReferenceArguments ConstReferenceArguments.o 

ReferenceToPointer: ReferenceToPointer.o 
	$(CPP) $(OFLAG)ReferenceToPointer ReferenceToPointer.o 

PassingBigStructures: PassingBigStructures.o 
	$(CPP) $(OFLAG)PassingBigStructures PassingBigStructures.o 

HowMany: HowMany.o 
	$(CPP) $(OFLAG)HowMany HowMany.o 

HowMany2: HowMany2.o 
	$(CPP) $(OFLAG)HowMany2 HowMany2.o 

Linenum: Linenum.o 
	$(CPP) $(OFLAG)Linenum Linenum.o 

DefaultCopyConstructor: DefaultCopyConstructor.o 
	$(CPP) $(OFLAG)DefaultCopyConstructor DefaultCopyConstructor.o 

NoCopyConstruction: NoCopyConstruction.o 
	$(CPP) $(OFLAG)NoCopyConstruction NoCopyConstruction.o 

SimpleStructure: SimpleStructure.o 
	$(CPP) $(OFLAG)SimpleStructure SimpleStructure.o 

PointerToMemberData: PointerToMemberData.o 
	$(CPP) $(OFLAG)PointerToMemberData PointerToMemberData.o 

PmemFunDefinition: PmemFunDefinition.o 
	$(CPP) $(OFLAG)PmemFunDefinition PmemFunDefinition.o 

PointerToMemberFunction: PointerToMemberFunction.o 
	$(CPP) $(OFLAG)PointerToMemberFunction PointerToMemberFunction.o 

PointerToMemberFunction2: PointerToMemberFunction2.o 
	$(CPP) $(OFLAG)PointerToMemberFunction2 PointerToMemberFunction2.o 


FreeStandingReferences.o: FreeStandingReferences.cpp 
Reference.o: Reference.cpp 
ConstReferenceArguments.o: ConstReferenceArguments.cpp 
ReferenceToPointer.o: ReferenceToPointer.cpp 
PassingBigStructures.o: PassingBigStructures.cpp 
HowMany.o: HowMany.cpp 
HowMany2.o: HowMany2.cpp 
Linenum.o: Linenum.cpp ../require.h 
DefaultCopyConstructor.o: DefaultCopyConstructor.cpp 
NoCopyConstruction.o: NoCopyConstruction.cpp 
SimpleStructure.o: SimpleStructure.cpp 
PointerToMemberData.o: PointerToMemberData.cpp 
PmemFunDefinition.o: PmemFunDefinition.cpp 
PointerToMemberFunction.o: PointerToMemberFunction.cpp 
PointerToMemberFunction2.o: PointerToMemberFunction2.cpp 

