# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C12
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
	OperatorOverloadingSyntax.exe \
	OverloadingUnaryOperators.exe \
	IntegerTest.exe \
	ByteTest.exe \
	SmartPointer.exe \
	NestedSmartPointer.exe \
	PointerToMemberOperator.exe \
	IostreamOperatorOverloading.exe \
	CopyingVsInitialization.exe \
	SimpleAssignment.exe \
	CopyingWithPointers.exe \
	ReferenceCounting.exe \
	AutomaticOperatorEquals.exe \
	AutomaticTypeConversion.exe \
	ExplicitKeyword.exe \
	OperatorOverloadingConversion.exe \
	ReflexivityInOverloading.exe \
	Strings1.exe \
	Strings2.exe \
	TypeConversionAmbiguity.exe \
	TypeConversionFanout.exe \
	CopyingVsInitialization2.exe 

test: all 
	OperatorOverloadingSyntax.exe  
	OverloadingUnaryOperators.exe  
	IntegerTest.exe  
	ByteTest.exe  
	SmartPointer.exe  
	NestedSmartPointer.exe  
	PointerToMemberOperator.exe  
	IostreamOperatorOverloading.exe  
	CopyingVsInitialization.exe  
	SimpleAssignment.exe  
	CopyingWithPointers.exe  
	ReferenceCounting.exe  
	AutomaticOperatorEquals.exe  
	AutomaticTypeConversion.exe  
	ExplicitKeyword.exe  
	OperatorOverloadingConversion.exe  
	ReflexivityInOverloading.exe  
	Strings1.exe  
	Strings2.exe  
	TypeConversionAmbiguity.exe  
	TypeConversionFanout.exe  
	CopyingVsInitialization2.exe  

bugs: \
	OverloadingOperatorComma.exe 

OperatorOverloadingSyntax.exe: OperatorOverloadingSyntax.obj 
	$(CPP) $(OFLAG)OperatorOverloadingSyntax.exe OperatorOverloadingSyntax.obj 

OverloadingUnaryOperators.exe: OverloadingUnaryOperators.obj 
	$(CPP) $(OFLAG)OverloadingUnaryOperators.exe OverloadingUnaryOperators.obj 

IntegerTest.exe: IntegerTest.obj Integer.obj 
	$(CPP) $(OFLAG)IntegerTest.exe IntegerTest.obj Integer.obj 

ByteTest.exe: ByteTest.obj 
	$(CPP) $(OFLAG)ByteTest.exe ByteTest.obj 

OverloadingOperatorComma.exe: OverloadingOperatorComma.obj 
	$(CPP) $(OFLAG)OverloadingOperatorComma.exe OverloadingOperatorComma.obj 

SmartPointer.exe: SmartPointer.obj 
	$(CPP) $(OFLAG)SmartPointer.exe SmartPointer.obj 

NestedSmartPointer.exe: NestedSmartPointer.obj 
	$(CPP) $(OFLAG)NestedSmartPointer.exe NestedSmartPointer.obj 

PointerToMemberOperator.exe: PointerToMemberOperator.obj 
	$(CPP) $(OFLAG)PointerToMemberOperator.exe PointerToMemberOperator.obj 

IostreamOperatorOverloading.exe: IostreamOperatorOverloading.obj 
	$(CPP) $(OFLAG)IostreamOperatorOverloading.exe IostreamOperatorOverloading.obj 

CopyingVsInitialization.exe: CopyingVsInitialization.obj 
	$(CPP) $(OFLAG)CopyingVsInitialization.exe CopyingVsInitialization.obj 

SimpleAssignment.exe: SimpleAssignment.obj 
	$(CPP) $(OFLAG)SimpleAssignment.exe SimpleAssignment.obj 

CopyingWithPointers.exe: CopyingWithPointers.obj 
	$(CPP) $(OFLAG)CopyingWithPointers.exe CopyingWithPointers.obj 

ReferenceCounting.exe: ReferenceCounting.obj 
	$(CPP) $(OFLAG)ReferenceCounting.exe ReferenceCounting.obj 

AutomaticOperatorEquals.exe: AutomaticOperatorEquals.obj 
	$(CPP) $(OFLAG)AutomaticOperatorEquals.exe AutomaticOperatorEquals.obj 

AutomaticTypeConversion.exe: AutomaticTypeConversion.obj 
	$(CPP) $(OFLAG)AutomaticTypeConversion.exe AutomaticTypeConversion.obj 

ExplicitKeyword.exe: ExplicitKeyword.obj 
	$(CPP) $(OFLAG)ExplicitKeyword.exe ExplicitKeyword.obj 

OperatorOverloadingConversion.exe: OperatorOverloadingConversion.obj 
	$(CPP) $(OFLAG)OperatorOverloadingConversion.exe OperatorOverloadingConversion.obj 

ReflexivityInOverloading.exe: ReflexivityInOverloading.obj 
	$(CPP) $(OFLAG)ReflexivityInOverloading.exe ReflexivityInOverloading.obj 

Strings1.exe: Strings1.obj 
	$(CPP) $(OFLAG)Strings1.exe Strings1.obj 

Strings2.exe: Strings2.obj 
	$(CPP) $(OFLAG)Strings2.exe Strings2.obj 

TypeConversionAmbiguity.exe: TypeConversionAmbiguity.obj 
	$(CPP) $(OFLAG)TypeConversionAmbiguity.exe TypeConversionAmbiguity.obj 

TypeConversionFanout.exe: TypeConversionFanout.obj 
	$(CPP) $(OFLAG)TypeConversionFanout.exe TypeConversionFanout.obj 

CopyingVsInitialization2.exe: CopyingVsInitialization2.obj 
	$(CPP) $(OFLAG)CopyingVsInitialization2.exe CopyingVsInitialization2.obj 


OperatorOverloadingSyntax.obj: OperatorOverloadingSyntax.cpp 
OverloadingUnaryOperators.obj: OverloadingUnaryOperators.cpp 
Integer.obj: Integer.cpp Integer.h ..\require.h 
IntegerTest.obj: IntegerTest.cpp Integer.h 
ByteTest.obj: ByteTest.cpp Byte.h 
OverloadingOperatorComma.obj: OverloadingOperatorComma.cpp 
SmartPointer.obj: SmartPointer.cpp ..\require.h 
NestedSmartPointer.obj: NestedSmartPointer.cpp ..\require.h 
PointerToMemberOperator.obj: PointerToMemberOperator.cpp 
IostreamOperatorOverloading.obj: IostreamOperatorOverloading.cpp ..\require.h 
CopyingVsInitialization.obj: CopyingVsInitialization.cpp 
SimpleAssignment.obj: SimpleAssignment.cpp 
CopyingWithPointers.obj: CopyingWithPointers.cpp ..\require.h 
ReferenceCounting.obj: ReferenceCounting.cpp ..\require.h 
AutomaticOperatorEquals.obj: AutomaticOperatorEquals.cpp 
AutomaticTypeConversion.obj: AutomaticTypeConversion.cpp 
ExplicitKeyword.obj: ExplicitKeyword.cpp 
OperatorOverloadingConversion.obj: OperatorOverloadingConversion.cpp 
ReflexivityInOverloading.obj: ReflexivityInOverloading.cpp 
Strings1.obj: Strings1.cpp ..\require.h 
Strings2.obj: Strings2.cpp ..\require.h 
TypeConversionAmbiguity.obj: TypeConversionAmbiguity.cpp 
TypeConversionFanout.obj: TypeConversionFanout.cpp 
CopyingVsInitialization2.obj: CopyingVsInitialization2.cpp 

