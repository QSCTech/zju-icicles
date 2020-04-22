# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C11
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
	FreeStandingReferences.exe \
	Reference.exe \
	ConstReferenceArguments.exe \
	ReferenceToPointer.exe \
	PassingBigStructures.exe \
	HowMany.exe \
	HowMany2.exe \
	Linenum.exe \
	DefaultCopyConstructor.exe \
	NoCopyConstruction.exe \
	SimpleStructure.exe \
	PointerToMemberData.exe \
	PmemFunDefinition.exe \
	PointerToMemberFunction.exe \
	PointerToMemberFunction2.exe 

test: all 
	FreeStandingReferences.exe  
	Reference.exe  
	ConstReferenceArguments.exe  
	ReferenceToPointer.exe  
	PassingBigStructures.exe  
	HowMany.exe  
	HowMany2.exe  
	Linenum.exe Linenum.cpp 
	DefaultCopyConstructor.exe  
	NoCopyConstruction.exe  
	SimpleStructure.exe  
	PointerToMemberData.exe  
	PmemFunDefinition.exe  
	PointerToMemberFunction.exe  
	PointerToMemberFunction2.exe  

bugs: 
	@echo No compiler bugs in this directory!

FreeStandingReferences.exe: FreeStandingReferences.obj 
	$(CPP) $(OFLAG)FreeStandingReferences.exe FreeStandingReferences.obj 

Reference.exe: Reference.obj 
	$(CPP) $(OFLAG)Reference.exe Reference.obj 

ConstReferenceArguments.exe: ConstReferenceArguments.obj 
	$(CPP) $(OFLAG)ConstReferenceArguments.exe ConstReferenceArguments.obj 

ReferenceToPointer.exe: ReferenceToPointer.obj 
	$(CPP) $(OFLAG)ReferenceToPointer.exe ReferenceToPointer.obj 

PassingBigStructures.exe: PassingBigStructures.obj 
	$(CPP) $(OFLAG)PassingBigStructures.exe PassingBigStructures.obj 

HowMany.exe: HowMany.obj 
	$(CPP) $(OFLAG)HowMany.exe HowMany.obj 

HowMany2.exe: HowMany2.obj 
	$(CPP) $(OFLAG)HowMany2.exe HowMany2.obj 

Linenum.exe: Linenum.obj 
	$(CPP) $(OFLAG)Linenum.exe Linenum.obj 

DefaultCopyConstructor.exe: DefaultCopyConstructor.obj 
	$(CPP) $(OFLAG)DefaultCopyConstructor.exe DefaultCopyConstructor.obj 

NoCopyConstruction.exe: NoCopyConstruction.obj 
	$(CPP) $(OFLAG)NoCopyConstruction.exe NoCopyConstruction.obj 

SimpleStructure.exe: SimpleStructure.obj 
	$(CPP) $(OFLAG)SimpleStructure.exe SimpleStructure.obj 

PointerToMemberData.exe: PointerToMemberData.obj 
	$(CPP) $(OFLAG)PointerToMemberData.exe PointerToMemberData.obj 

PmemFunDefinition.exe: PmemFunDefinition.obj 
	$(CPP) $(OFLAG)PmemFunDefinition.exe PmemFunDefinition.obj 

PointerToMemberFunction.exe: PointerToMemberFunction.obj 
	$(CPP) $(OFLAG)PointerToMemberFunction.exe PointerToMemberFunction.obj 

PointerToMemberFunction2.exe: PointerToMemberFunction2.obj 
	$(CPP) $(OFLAG)PointerToMemberFunction2.exe PointerToMemberFunction2.obj 


FreeStandingReferences.obj: FreeStandingReferences.cpp 
Reference.obj: Reference.cpp 
ConstReferenceArguments.obj: ConstReferenceArguments.cpp 
ReferenceToPointer.obj: ReferenceToPointer.cpp 
PassingBigStructures.obj: PassingBigStructures.cpp 
HowMany.obj: HowMany.cpp 
HowMany2.obj: HowMany2.cpp 
Linenum.obj: Linenum.cpp ..\require.h 
DefaultCopyConstructor.obj: DefaultCopyConstructor.cpp 
NoCopyConstruction.obj: NoCopyConstruction.cpp 
SimpleStructure.obj: SimpleStructure.cpp 
PointerToMemberData.obj: PointerToMemberData.cpp 
PmemFunDefinition.obj: PmemFunDefinition.cpp 
PointerToMemberFunction.obj: PointerToMemberFunction.cpp 
PointerToMemberFunction2.obj: PointerToMemberFunction2.cpp 

