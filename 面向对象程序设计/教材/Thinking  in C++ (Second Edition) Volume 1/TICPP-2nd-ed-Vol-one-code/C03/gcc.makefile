# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C03
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
	Return \
	Ifthen \
	Guess \
	Guess2 \
	Charlist \
	Menu \
	Menu2 \
	gotoKeyword \
	CatsInHats \
	AutoIncrement \
	Basic \
	Specify \
	YourPets1 \
	YourPets2 \
	PassByValue \
	PassAddress \
	PassReference \
	AllDefinitions \
	VoidPointer \
	CastFromVoidPointer \
	Scope \
	OnTheFly \
	Global \
	Static \
	FileStatic \
	Forward \
	Mathops \
	Boolean \
	Bitwise \
	CommaOperator \
	Pitfall \
	SimpleCast \
	FunctionCallCast \
	static_cast \
	const_cast \
	reinterpret_cast \
	sizeof \
	sizeofOperator \
	SimpleStruct \
	SimpleStruct2 \
	SelfReferential \
	SimpleStruct3 \
	Enum \
	Union \
	Arrays \
	StructArray \
	ArrayAddresses \
	ArrayIdentifier \
	PointersAndBrackets \
	ArrayArguments \
	CommandLineArgs \
	ArgsToInts \
	FloatingAsBinary \
	PointerIncrement \
	PointerIncrement2 \
	PointerArithmetic \
	DynamicDebugFlags \
	StringizingExpressions \
	Assert \
	ComplicatedDefinitions \
	PointerToFunction \
	FunctionTable 

test: all 
	Return  
	Ifthen  
	Guess  
	Guess2  
	Charlist  
	Menu  
	Menu2  
	gotoKeyword  
	CatsInHats  
	AutoIncrement  
	Basic  
	Specify  
	YourPets1  
	YourPets2  
	PassByValue  
	PassAddress  
	PassReference  
	AllDefinitions  
	VoidPointer  
	CastFromVoidPointer  
	Scope  
	OnTheFly  
	Global  
	Static  
	FileStatic  
	Forward  
	Mathops  
	Boolean  
	Bitwise  
	CommaOperator  
	Pitfall  
	SimpleCast  
	FunctionCallCast  
	static_cast  
	const_cast  
	reinterpret_cast  
	sizeof  
	sizeofOperator  
	SimpleStruct  
	SimpleStruct2  
	SelfReferential  
	SimpleStruct3  
	Enum  
	Union  
	Arrays  
	StructArray  
	ArrayAddresses  
	ArrayIdentifier  
	PointersAndBrackets  
	ArrayArguments  
	CommandLineArgs  
	ArgsToInts  
	FloatingAsBinary 3.14159 
	PointerIncrement  
	PointerIncrement2  
	PointerArithmetic  
	DynamicDebugFlags  
	StringizingExpressions  
	Assert  
	ComplicatedDefinitions  
	PointerToFunction  
	FunctionTable  

bugs: 
	@echo No compiler bugs in this directory!

Return: Return.o 
	$(CPP) $(OFLAG)Return Return.o 

Ifthen: Ifthen.o 
	$(CPP) $(OFLAG)Ifthen Ifthen.o 

Guess: Guess.o 
	$(CPP) $(OFLAG)Guess Guess.o 

Guess2: Guess2.o 
	$(CPP) $(OFLAG)Guess2 Guess2.o 

Charlist: Charlist.o 
	$(CPP) $(OFLAG)Charlist Charlist.o 

Menu: Menu.o 
	$(CPP) $(OFLAG)Menu Menu.o 

Menu2: Menu2.o 
	$(CPP) $(OFLAG)Menu2 Menu2.o 

gotoKeyword: gotoKeyword.o 
	$(CPP) $(OFLAG)gotoKeyword gotoKeyword.o 

CatsInHats: CatsInHats.o 
	$(CPP) $(OFLAG)CatsInHats CatsInHats.o 

AutoIncrement: AutoIncrement.o 
	$(CPP) $(OFLAG)AutoIncrement AutoIncrement.o 

Basic: Basic.o 
	$(CPP) $(OFLAG)Basic Basic.o 

Specify: Specify.o 
	$(CPP) $(OFLAG)Specify Specify.o 

YourPets1: YourPets1.o 
	$(CPP) $(OFLAG)YourPets1 YourPets1.o 

YourPets2: YourPets2.o 
	$(CPP) $(OFLAG)YourPets2 YourPets2.o 

PassByValue: PassByValue.o 
	$(CPP) $(OFLAG)PassByValue PassByValue.o 

PassAddress: PassAddress.o 
	$(CPP) $(OFLAG)PassAddress PassAddress.o 

PassReference: PassReference.o 
	$(CPP) $(OFLAG)PassReference PassReference.o 

AllDefinitions: AllDefinitions.o 
	$(CPP) $(OFLAG)AllDefinitions AllDefinitions.o 

VoidPointer: VoidPointer.o 
	$(CPP) $(OFLAG)VoidPointer VoidPointer.o 

CastFromVoidPointer: CastFromVoidPointer.o 
	$(CPP) $(OFLAG)CastFromVoidPointer CastFromVoidPointer.o 

Scope: Scope.o 
	$(CPP) $(OFLAG)Scope Scope.o 

OnTheFly: OnTheFly.o 
	$(CPP) $(OFLAG)OnTheFly OnTheFly.o 

Global: Global.o Global2.o 
	$(CPP) $(OFLAG)Global Global.o Global2.o 

Static: Static.o 
	$(CPP) $(OFLAG)Static Static.o 

FileStatic: FileStatic.o 
	$(CPP) $(OFLAG)FileStatic FileStatic.o 

Forward: Forward.o 
	$(CPP) $(OFLAG)Forward Forward.o 

Mathops: Mathops.o 
	$(CPP) $(OFLAG)Mathops Mathops.o 

Boolean: Boolean.o 
	$(CPP) $(OFLAG)Boolean Boolean.o 

Bitwise: Bitwise.o printBinary.o 
	$(CPP) $(OFLAG)Bitwise Bitwise.o printBinary.o 

CommaOperator: CommaOperator.o 
	$(CPP) $(OFLAG)CommaOperator CommaOperator.o 

Pitfall: Pitfall.o 
	$(CPP) $(OFLAG)Pitfall Pitfall.o 

SimpleCast: SimpleCast.o 
	$(CPP) $(OFLAG)SimpleCast SimpleCast.o 

FunctionCallCast: FunctionCallCast.o 
	$(CPP) $(OFLAG)FunctionCallCast FunctionCallCast.o 

static_cast: static_cast.o 
	$(CPP) $(OFLAG)static_cast static_cast.o 

const_cast: const_cast.o 
	$(CPP) $(OFLAG)const_cast const_cast.o 

reinterpret_cast: reinterpret_cast.o 
	$(CPP) $(OFLAG)reinterpret_cast reinterpret_cast.o 

sizeof: sizeof.o 
	$(CPP) $(OFLAG)sizeof sizeof.o 

sizeofOperator: sizeofOperator.o 
	$(CPP) $(OFLAG)sizeofOperator sizeofOperator.o 

SimpleStruct: SimpleStruct.o 
	$(CPP) $(OFLAG)SimpleStruct SimpleStruct.o 

SimpleStruct2: SimpleStruct2.o 
	$(CPP) $(OFLAG)SimpleStruct2 SimpleStruct2.o 

SelfReferential: SelfReferential.o 
	$(CPP) $(OFLAG)SelfReferential SelfReferential.o 

SimpleStruct3: SimpleStruct3.o 
	$(CPP) $(OFLAG)SimpleStruct3 SimpleStruct3.o 

Enum: Enum.o 
	$(CPP) $(OFLAG)Enum Enum.o 

Union: Union.o 
	$(CPP) $(OFLAG)Union Union.o 

Arrays: Arrays.o 
	$(CPP) $(OFLAG)Arrays Arrays.o 

StructArray: StructArray.o 
	$(CPP) $(OFLAG)StructArray StructArray.o 

ArrayAddresses: ArrayAddresses.o 
	$(CPP) $(OFLAG)ArrayAddresses ArrayAddresses.o 

ArrayIdentifier: ArrayIdentifier.o 
	$(CPP) $(OFLAG)ArrayIdentifier ArrayIdentifier.o 

PointersAndBrackets: PointersAndBrackets.o 
	$(CPP) $(OFLAG)PointersAndBrackets PointersAndBrackets.o 

ArrayArguments: ArrayArguments.o 
	$(CPP) $(OFLAG)ArrayArguments ArrayArguments.o 

CommandLineArgs: CommandLineArgs.o 
	$(CPP) $(OFLAG)CommandLineArgs CommandLineArgs.o 

ArgsToInts: ArgsToInts.o 
	$(CPP) $(OFLAG)ArgsToInts ArgsToInts.o 

FloatingAsBinary: FloatingAsBinary.o printBinary.o 
	$(CPP) $(OFLAG)FloatingAsBinary FloatingAsBinary.o printBinary.o 

PointerIncrement: PointerIncrement.o 
	$(CPP) $(OFLAG)PointerIncrement PointerIncrement.o 

PointerIncrement2: PointerIncrement2.o 
	$(CPP) $(OFLAG)PointerIncrement2 PointerIncrement2.o 

PointerArithmetic: PointerArithmetic.o 
	$(CPP) $(OFLAG)PointerArithmetic PointerArithmetic.o 

DynamicDebugFlags: DynamicDebugFlags.o 
	$(CPP) $(OFLAG)DynamicDebugFlags DynamicDebugFlags.o 

StringizingExpressions: StringizingExpressions.o 
	$(CPP) $(OFLAG)StringizingExpressions StringizingExpressions.o 

Assert: Assert.o 
	$(CPP) $(OFLAG)Assert Assert.o 

ComplicatedDefinitions: ComplicatedDefinitions.o 
	$(CPP) $(OFLAG)ComplicatedDefinitions ComplicatedDefinitions.o 

PointerToFunction: PointerToFunction.o 
	$(CPP) $(OFLAG)PointerToFunction PointerToFunction.o 

FunctionTable: FunctionTable.o 
	$(CPP) $(OFLAG)FunctionTable FunctionTable.o 


Return.o: Return.cpp 
Ifthen.o: Ifthen.cpp 
Guess.o: Guess.cpp 
Guess2.o: Guess2.cpp 
Charlist.o: Charlist.cpp 
Menu.o: Menu.cpp 
Menu2.o: Menu2.cpp 
gotoKeyword.o: gotoKeyword.cpp 
CatsInHats.o: CatsInHats.cpp 
AutoIncrement.o: AutoIncrement.cpp 
Basic.o: Basic.cpp 
Specify.o: Specify.cpp 
YourPets1.o: YourPets1.cpp 
YourPets2.o: YourPets2.cpp 
PassByValue.o: PassByValue.cpp 
PassAddress.o: PassAddress.cpp 
PassReference.o: PassReference.cpp 
AllDefinitions.o: AllDefinitions.cpp 
VoidPointer.o: VoidPointer.cpp 
CastFromVoidPointer.o: CastFromVoidPointer.cpp 
Scope.o: Scope.cpp 
OnTheFly.o: OnTheFly.cpp 
Global.o: Global.cpp 
Global2.o: Global2.cpp 
Static.o: Static.cpp 
FileStatic.o: FileStatic.cpp 
FileStatic2.o: FileStatic2.cpp 
Forward.o: Forward.cpp 
Mathops.o: Mathops.cpp 
Boolean.o: Boolean.cpp 
printBinary.o: printBinary.cpp 
Bitwise.o: Bitwise.cpp printBinary.h 
Rotation.o: Rotation.cpp 
CommaOperator.o: CommaOperator.cpp 
Pitfall.o: Pitfall.cpp 
SimpleCast.o: SimpleCast.cpp 
FunctionCallCast.o: FunctionCallCast.cpp 
static_cast.o: static_cast.cpp 
const_cast.o: const_cast.cpp 
reinterpret_cast.o: reinterpret_cast.cpp 
sizeof.o: sizeof.cpp 
sizeofOperator.o: sizeofOperator.cpp 
SimpleStruct.o: SimpleStruct.cpp 
SimpleStruct2.o: SimpleStruct2.cpp 
SelfReferential.o: SelfReferential.cpp 
SimpleStruct3.o: SimpleStruct3.cpp 
Enum.o: Enum.cpp 
Union.o: Union.cpp 
Arrays.o: Arrays.cpp 
StructArray.o: StructArray.cpp 
ArrayAddresses.o: ArrayAddresses.cpp 
ArrayIdentifier.o: ArrayIdentifier.cpp 
PointersAndBrackets.o: PointersAndBrackets.cpp 
ArrayArguments.o: ArrayArguments.cpp 
CommandLineArgs.o: CommandLineArgs.cpp 
ArgsToInts.o: ArgsToInts.cpp 
FloatingAsBinary.o: FloatingAsBinary.cpp printBinary.h 
PointerIncrement.o: PointerIncrement.cpp 
PointerIncrement2.o: PointerIncrement2.cpp 
PointerArithmetic.o: PointerArithmetic.cpp 
DynamicDebugFlags.o: DynamicDebugFlags.cpp 
StringizingExpressions.o: StringizingExpressions.cpp 
Assert.o: Assert.cpp 
ComplicatedDefinitions.o: ComplicatedDefinitions.cpp 
PointerToFunction.o: PointerToFunction.cpp 
FunctionTable.o: FunctionTable.cpp 

