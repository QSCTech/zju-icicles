# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C12
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
	OperatorOverloadingSyntax \
	OverloadingUnaryOperators \
	IntegerTest \
	ByteTest \
	OverloadingOperatorComma \
	SmartPointer \
	NestedSmartPointer \
	PointerToMemberOperator \
	CopyingVsInitialization \
	SimpleAssignment \
	CopyingWithPointers \
	ReferenceCounting \
	AutomaticOperatorEquals \
	AutomaticTypeConversion \
	ExplicitKeyword \
	OperatorOverloadingConversion \
	ReflexivityInOverloading \
	Strings1 \
	Strings2 \
	TypeConversionAmbiguity \
	TypeConversionFanout \
	CopyingVsInitialization2 

test: all 
	OperatorOverloadingSyntax  
	OverloadingUnaryOperators  
	IntegerTest  
	ByteTest  
	OverloadingOperatorComma  
	SmartPointer  
	NestedSmartPointer  
	PointerToMemberOperator  
	CopyingVsInitialization  
	SimpleAssignment  
	CopyingWithPointers  
	ReferenceCounting  
	AutomaticOperatorEquals  
	AutomaticTypeConversion  
	ExplicitKeyword  
	OperatorOverloadingConversion  
	ReflexivityInOverloading  
	Strings1  
	Strings2  
	TypeConversionAmbiguity  
	TypeConversionFanout  
	CopyingVsInitialization2  

bugs: \
	IostreamOperatorOverloading 

OperatorOverloadingSyntax: OperatorOverloadingSyntax.o 
	$(CPP) $(OFLAG)OperatorOverloadingSyntax OperatorOverloadingSyntax.o 

OverloadingUnaryOperators: OverloadingUnaryOperators.o 
	$(CPP) $(OFLAG)OverloadingUnaryOperators OverloadingUnaryOperators.o 

IntegerTest: IntegerTest.o Integer.o 
	$(CPP) $(OFLAG)IntegerTest IntegerTest.o Integer.o 

ByteTest: ByteTest.o 
	$(CPP) $(OFLAG)ByteTest ByteTest.o 

OverloadingOperatorComma: OverloadingOperatorComma.o 
	$(CPP) $(OFLAG)OverloadingOperatorComma OverloadingOperatorComma.o 

SmartPointer: SmartPointer.o 
	$(CPP) $(OFLAG)SmartPointer SmartPointer.o 

NestedSmartPointer: NestedSmartPointer.o 
	$(CPP) $(OFLAG)NestedSmartPointer NestedSmartPointer.o 

PointerToMemberOperator: PointerToMemberOperator.o 
	$(CPP) $(OFLAG)PointerToMemberOperator PointerToMemberOperator.o 

IostreamOperatorOverloading: IostreamOperatorOverloading.o 
	$(CPP) $(OFLAG)IostreamOperatorOverloading IostreamOperatorOverloading.o 

CopyingVsInitialization: CopyingVsInitialization.o 
	$(CPP) $(OFLAG)CopyingVsInitialization CopyingVsInitialization.o 

SimpleAssignment: SimpleAssignment.o 
	$(CPP) $(OFLAG)SimpleAssignment SimpleAssignment.o 

CopyingWithPointers: CopyingWithPointers.o 
	$(CPP) $(OFLAG)CopyingWithPointers CopyingWithPointers.o 

ReferenceCounting: ReferenceCounting.o 
	$(CPP) $(OFLAG)ReferenceCounting ReferenceCounting.o 

AutomaticOperatorEquals: AutomaticOperatorEquals.o 
	$(CPP) $(OFLAG)AutomaticOperatorEquals AutomaticOperatorEquals.o 

AutomaticTypeConversion: AutomaticTypeConversion.o 
	$(CPP) $(OFLAG)AutomaticTypeConversion AutomaticTypeConversion.o 

ExplicitKeyword: ExplicitKeyword.o 
	$(CPP) $(OFLAG)ExplicitKeyword ExplicitKeyword.o 

OperatorOverloadingConversion: OperatorOverloadingConversion.o 
	$(CPP) $(OFLAG)OperatorOverloadingConversion OperatorOverloadingConversion.o 

ReflexivityInOverloading: ReflexivityInOverloading.o 
	$(CPP) $(OFLAG)ReflexivityInOverloading ReflexivityInOverloading.o 

Strings1: Strings1.o 
	$(CPP) $(OFLAG)Strings1 Strings1.o 

Strings2: Strings2.o 
	$(CPP) $(OFLAG)Strings2 Strings2.o 

TypeConversionAmbiguity: TypeConversionAmbiguity.o 
	$(CPP) $(OFLAG)TypeConversionAmbiguity TypeConversionAmbiguity.o 

TypeConversionFanout: TypeConversionFanout.o 
	$(CPP) $(OFLAG)TypeConversionFanout TypeConversionFanout.o 

CopyingVsInitialization2: CopyingVsInitialization2.o 
	$(CPP) $(OFLAG)CopyingVsInitialization2 CopyingVsInitialization2.o 


OperatorOverloadingSyntax.o: OperatorOverloadingSyntax.cpp 
OverloadingUnaryOperators.o: OverloadingUnaryOperators.cpp 
Integer.o: Integer.cpp Integer.h ../require.h 
IntegerTest.o: IntegerTest.cpp Integer.h 
ByteTest.o: ByteTest.cpp Byte.h 
OverloadingOperatorComma.o: OverloadingOperatorComma.cpp 
SmartPointer.o: SmartPointer.cpp ../require.h 
NestedSmartPointer.o: NestedSmartPointer.cpp ../require.h 
PointerToMemberOperator.o: PointerToMemberOperator.cpp 
IostreamOperatorOverloading.o: IostreamOperatorOverloading.cpp ../require.h 
CopyingVsInitialization.o: CopyingVsInitialization.cpp 
SimpleAssignment.o: SimpleAssignment.cpp 
CopyingWithPointers.o: CopyingWithPointers.cpp ../require.h 
ReferenceCounting.o: ReferenceCounting.cpp ../require.h 
AutomaticOperatorEquals.o: AutomaticOperatorEquals.cpp 
AutomaticTypeConversion.o: AutomaticTypeConversion.cpp 
ExplicitKeyword.o: ExplicitKeyword.cpp 
OperatorOverloadingConversion.o: OperatorOverloadingConversion.cpp 
ReflexivityInOverloading.o: ReflexivityInOverloading.cpp 
Strings1.o: Strings1.cpp ../require.h 
Strings2.o: Strings2.cpp ../require.h 
TypeConversionAmbiguity.o: TypeConversionAmbiguity.cpp 
TypeConversionFanout.o: TypeConversionFanout.cpp 
CopyingVsInitialization2.o: CopyingVsInitialization2.cpp 

