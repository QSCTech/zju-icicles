# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C03
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
	Return.exe \
	Ifthen.exe \
	Guess.exe \
	Guess2.exe \
	Charlist.exe \
	Menu.exe \
	Menu2.exe \
	gotoKeyword.exe \
	CatsInHats.exe \
	AutoIncrement.exe \
	Basic.exe \
	Specify.exe \
	YourPets1.exe \
	YourPets2.exe \
	PassByValue.exe \
	PassAddress.exe \
	PassReference.exe \
	AllDefinitions.exe \
	VoidPointer.exe \
	CastFromVoidPointer.exe \
	Scope.exe \
	OnTheFly.exe \
	Global.exe \
	Static.exe \
	FileStatic.exe \
	Forward.exe \
	Mathops.exe \
	Boolean.exe \
	Bitwise.exe \
	CommaOperator.exe \
	Pitfall.exe \
	SimpleCast.exe \
	FunctionCallCast.exe \
	static_cast.exe \
	const_cast.exe \
	reinterpret_cast.exe \
	sizeof.exe \
	sizeofOperator.exe \
	SimpleStruct.exe \
	SimpleStruct2.exe \
	SelfReferential.exe \
	SimpleStruct3.exe \
	Enum.exe \
	Union.exe \
	Arrays.exe \
	StructArray.exe \
	ArrayAddresses.exe \
	ArrayIdentifier.exe \
	PointersAndBrackets.exe \
	ArrayArguments.exe \
	CommandLineArgs.exe \
	ArgsToInts.exe \
	FloatingAsBinary.exe \
	PointerIncrement.exe \
	PointerIncrement2.exe \
	PointerArithmetic.exe \
	DynamicDebugFlags.exe \
	StringizingExpressions.exe \
	Assert.exe \
	ComplicatedDefinitions.exe \
	PointerToFunction.exe \
	FunctionTable.exe 

test: all 
	Return.exe  
	Ifthen.exe  
	Guess.exe  
	Guess2.exe  
	Charlist.exe  
	Menu.exe  
	Menu2.exe  
	gotoKeyword.exe  
	CatsInHats.exe  
	AutoIncrement.exe  
	Basic.exe  
	Specify.exe  
	YourPets1.exe  
	YourPets2.exe  
	PassByValue.exe  
	PassAddress.exe  
	PassReference.exe  
	AllDefinitions.exe  
	VoidPointer.exe  
	CastFromVoidPointer.exe  
	Scope.exe  
	OnTheFly.exe  
	Global.exe  
	Static.exe  
	FileStatic.exe  
	Forward.exe  
	Mathops.exe  
	Boolean.exe  
	Bitwise.exe  
	CommaOperator.exe  
	Pitfall.exe  
	SimpleCast.exe  
	FunctionCallCast.exe  
	static_cast.exe  
	const_cast.exe  
	reinterpret_cast.exe  
	sizeof.exe  
	sizeofOperator.exe  
	SimpleStruct.exe  
	SimpleStruct2.exe  
	SelfReferential.exe  
	SimpleStruct3.exe  
	Enum.exe  
	Union.exe  
	Arrays.exe  
	StructArray.exe  
	ArrayAddresses.exe  
	ArrayIdentifier.exe  
	PointersAndBrackets.exe  
	ArrayArguments.exe  
	CommandLineArgs.exe  
	ArgsToInts.exe  
	FloatingAsBinary.exe 3.14159 
	PointerIncrement.exe  
	PointerIncrement2.exe  
	PointerArithmetic.exe  
	DynamicDebugFlags.exe  
	StringizingExpressions.exe  
	Assert.exe  
	ComplicatedDefinitions.exe  
	PointerToFunction.exe  
	FunctionTable.exe  

bugs: 
	@echo No compiler bugs in this directory!

Return.exe: Return.obj 
	$(CPP) $(OFLAG)Return.exe Return.obj 

Ifthen.exe: Ifthen.obj 
	$(CPP) $(OFLAG)Ifthen.exe Ifthen.obj 

Guess.exe: Guess.obj 
	$(CPP) $(OFLAG)Guess.exe Guess.obj 

Guess2.exe: Guess2.obj 
	$(CPP) $(OFLAG)Guess2.exe Guess2.obj 

Charlist.exe: Charlist.obj 
	$(CPP) $(OFLAG)Charlist.exe Charlist.obj 

Menu.exe: Menu.obj 
	$(CPP) $(OFLAG)Menu.exe Menu.obj 

Menu2.exe: Menu2.obj 
	$(CPP) $(OFLAG)Menu2.exe Menu2.obj 

gotoKeyword.exe: gotoKeyword.obj 
	$(CPP) $(OFLAG)gotoKeyword.exe gotoKeyword.obj 

CatsInHats.exe: CatsInHats.obj 
	$(CPP) $(OFLAG)CatsInHats.exe CatsInHats.obj 

AutoIncrement.exe: AutoIncrement.obj 
	$(CPP) $(OFLAG)AutoIncrement.exe AutoIncrement.obj 

Basic.exe: Basic.obj 
	$(CPP) $(OFLAG)Basic.exe Basic.obj 

Specify.exe: Specify.obj 
	$(CPP) $(OFLAG)Specify.exe Specify.obj 

YourPets1.exe: YourPets1.obj 
	$(CPP) $(OFLAG)YourPets1.exe YourPets1.obj 

YourPets2.exe: YourPets2.obj 
	$(CPP) $(OFLAG)YourPets2.exe YourPets2.obj 

PassByValue.exe: PassByValue.obj 
	$(CPP) $(OFLAG)PassByValue.exe PassByValue.obj 

PassAddress.exe: PassAddress.obj 
	$(CPP) $(OFLAG)PassAddress.exe PassAddress.obj 

PassReference.exe: PassReference.obj 
	$(CPP) $(OFLAG)PassReference.exe PassReference.obj 

AllDefinitions.exe: AllDefinitions.obj 
	$(CPP) $(OFLAG)AllDefinitions.exe AllDefinitions.obj 

VoidPointer.exe: VoidPointer.obj 
	$(CPP) $(OFLAG)VoidPointer.exe VoidPointer.obj 

CastFromVoidPointer.exe: CastFromVoidPointer.obj 
	$(CPP) $(OFLAG)CastFromVoidPointer.exe CastFromVoidPointer.obj 

Scope.exe: Scope.obj 
	$(CPP) $(OFLAG)Scope.exe Scope.obj 

OnTheFly.exe: OnTheFly.obj 
	$(CPP) $(OFLAG)OnTheFly.exe OnTheFly.obj 

Global.exe: Global.obj Global2.obj 
	$(CPP) $(OFLAG)Global.exe Global.obj Global2.obj 

Static.exe: Static.obj 
	$(CPP) $(OFLAG)Static.exe Static.obj 

FileStatic.exe: FileStatic.obj 
	$(CPP) $(OFLAG)FileStatic.exe FileStatic.obj 

Forward.exe: Forward.obj 
	$(CPP) $(OFLAG)Forward.exe Forward.obj 

Mathops.exe: Mathops.obj 
	$(CPP) $(OFLAG)Mathops.exe Mathops.obj 

Boolean.exe: Boolean.obj 
	$(CPP) $(OFLAG)Boolean.exe Boolean.obj 

Bitwise.exe: Bitwise.obj printBinary.obj 
	$(CPP) $(OFLAG)Bitwise.exe Bitwise.obj printBinary.obj 

CommaOperator.exe: CommaOperator.obj 
	$(CPP) $(OFLAG)CommaOperator.exe CommaOperator.obj 

Pitfall.exe: Pitfall.obj 
	$(CPP) $(OFLAG)Pitfall.exe Pitfall.obj 

SimpleCast.exe: SimpleCast.obj 
	$(CPP) $(OFLAG)SimpleCast.exe SimpleCast.obj 

FunctionCallCast.exe: FunctionCallCast.obj 
	$(CPP) $(OFLAG)FunctionCallCast.exe FunctionCallCast.obj 

static_cast.exe: static_cast.obj 
	$(CPP) $(OFLAG)static_cast.exe static_cast.obj 

const_cast.exe: const_cast.obj 
	$(CPP) $(OFLAG)const_cast.exe const_cast.obj 

reinterpret_cast.exe: reinterpret_cast.obj 
	$(CPP) $(OFLAG)reinterpret_cast.exe reinterpret_cast.obj 

sizeof.exe: sizeof.obj 
	$(CPP) $(OFLAG)sizeof.exe sizeof.obj 

sizeofOperator.exe: sizeofOperator.obj 
	$(CPP) $(OFLAG)sizeofOperator.exe sizeofOperator.obj 

SimpleStruct.exe: SimpleStruct.obj 
	$(CPP) $(OFLAG)SimpleStruct.exe SimpleStruct.obj 

SimpleStruct2.exe: SimpleStruct2.obj 
	$(CPP) $(OFLAG)SimpleStruct2.exe SimpleStruct2.obj 

SelfReferential.exe: SelfReferential.obj 
	$(CPP) $(OFLAG)SelfReferential.exe SelfReferential.obj 

SimpleStruct3.exe: SimpleStruct3.obj 
	$(CPP) $(OFLAG)SimpleStruct3.exe SimpleStruct3.obj 

Enum.exe: Enum.obj 
	$(CPP) $(OFLAG)Enum.exe Enum.obj 

Union.exe: Union.obj 
	$(CPP) $(OFLAG)Union.exe Union.obj 

Arrays.exe: Arrays.obj 
	$(CPP) $(OFLAG)Arrays.exe Arrays.obj 

StructArray.exe: StructArray.obj 
	$(CPP) $(OFLAG)StructArray.exe StructArray.obj 

ArrayAddresses.exe: ArrayAddresses.obj 
	$(CPP) $(OFLAG)ArrayAddresses.exe ArrayAddresses.obj 

ArrayIdentifier.exe: ArrayIdentifier.obj 
	$(CPP) $(OFLAG)ArrayIdentifier.exe ArrayIdentifier.obj 

PointersAndBrackets.exe: PointersAndBrackets.obj 
	$(CPP) $(OFLAG)PointersAndBrackets.exe PointersAndBrackets.obj 

ArrayArguments.exe: ArrayArguments.obj 
	$(CPP) $(OFLAG)ArrayArguments.exe ArrayArguments.obj 

CommandLineArgs.exe: CommandLineArgs.obj 
	$(CPP) $(OFLAG)CommandLineArgs.exe CommandLineArgs.obj 

ArgsToInts.exe: ArgsToInts.obj 
	$(CPP) $(OFLAG)ArgsToInts.exe ArgsToInts.obj 

FloatingAsBinary.exe: FloatingAsBinary.obj printBinary.obj 
	$(CPP) $(OFLAG)FloatingAsBinary.exe FloatingAsBinary.obj printBinary.obj 

PointerIncrement.exe: PointerIncrement.obj 
	$(CPP) $(OFLAG)PointerIncrement.exe PointerIncrement.obj 

PointerIncrement2.exe: PointerIncrement2.obj 
	$(CPP) $(OFLAG)PointerIncrement2.exe PointerIncrement2.obj 

PointerArithmetic.exe: PointerArithmetic.obj 
	$(CPP) $(OFLAG)PointerArithmetic.exe PointerArithmetic.obj 

DynamicDebugFlags.exe: DynamicDebugFlags.obj 
	$(CPP) $(OFLAG)DynamicDebugFlags.exe DynamicDebugFlags.obj 

StringizingExpressions.exe: StringizingExpressions.obj 
	$(CPP) $(OFLAG)StringizingExpressions.exe StringizingExpressions.obj 

Assert.exe: Assert.obj 
	$(CPP) $(OFLAG)Assert.exe Assert.obj 

ComplicatedDefinitions.exe: ComplicatedDefinitions.obj 
	$(CPP) $(OFLAG)ComplicatedDefinitions.exe ComplicatedDefinitions.obj 

PointerToFunction.exe: PointerToFunction.obj 
	$(CPP) $(OFLAG)PointerToFunction.exe PointerToFunction.obj 

FunctionTable.exe: FunctionTable.obj 
	$(CPP) $(OFLAG)FunctionTable.exe FunctionTable.obj 


Return.obj: Return.cpp 
Ifthen.obj: Ifthen.cpp 
Guess.obj: Guess.cpp 
Guess2.obj: Guess2.cpp 
Charlist.obj: Charlist.cpp 
Menu.obj: Menu.cpp 
Menu2.obj: Menu2.cpp 
gotoKeyword.obj: gotoKeyword.cpp 
CatsInHats.obj: CatsInHats.cpp 
AutoIncrement.obj: AutoIncrement.cpp 
Basic.obj: Basic.cpp 
Specify.obj: Specify.cpp 
YourPets1.obj: YourPets1.cpp 
YourPets2.obj: YourPets2.cpp 
PassByValue.obj: PassByValue.cpp 
PassAddress.obj: PassAddress.cpp 
PassReference.obj: PassReference.cpp 
AllDefinitions.obj: AllDefinitions.cpp 
VoidPointer.obj: VoidPointer.cpp 
CastFromVoidPointer.obj: CastFromVoidPointer.cpp 
Scope.obj: Scope.cpp 
OnTheFly.obj: OnTheFly.cpp 
Global.obj: Global.cpp 
Global2.obj: Global2.cpp 
Static.obj: Static.cpp 
FileStatic.obj: FileStatic.cpp 
FileStatic2.obj: FileStatic2.cpp 
Forward.obj: Forward.cpp 
Mathops.obj: Mathops.cpp 
Boolean.obj: Boolean.cpp 
printBinary.obj: printBinary.cpp 
Bitwise.obj: Bitwise.cpp printBinary.h 
Rotation.obj: Rotation.cpp 
CommaOperator.obj: CommaOperator.cpp 
Pitfall.obj: Pitfall.cpp 
SimpleCast.obj: SimpleCast.cpp 
FunctionCallCast.obj: FunctionCallCast.cpp 
static_cast.obj: static_cast.cpp 
const_cast.obj: const_cast.cpp 
reinterpret_cast.obj: reinterpret_cast.cpp 
sizeof.obj: sizeof.cpp 
sizeofOperator.obj: sizeofOperator.cpp 
SimpleStruct.obj: SimpleStruct.cpp 
SimpleStruct2.obj: SimpleStruct2.cpp 
SelfReferential.obj: SelfReferential.cpp 
SimpleStruct3.obj: SimpleStruct3.cpp 
Enum.obj: Enum.cpp 
Union.obj: Union.cpp 
Arrays.obj: Arrays.cpp 
StructArray.obj: StructArray.cpp 
ArrayAddresses.obj: ArrayAddresses.cpp 
ArrayIdentifier.obj: ArrayIdentifier.cpp 
PointersAndBrackets.obj: PointersAndBrackets.cpp 
ArrayArguments.obj: ArrayArguments.cpp 
CommandLineArgs.obj: CommandLineArgs.cpp 
ArgsToInts.obj: ArgsToInts.cpp 
FloatingAsBinary.obj: FloatingAsBinary.cpp printBinary.h 
PointerIncrement.obj: PointerIncrement.cpp 
PointerIncrement2.obj: PointerIncrement2.cpp 
PointerArithmetic.obj: PointerArithmetic.cpp 
DynamicDebugFlags.obj: DynamicDebugFlags.cpp 
StringizingExpressions.obj: StringizingExpressions.cpp 
Assert.obj: Assert.cpp 
ComplicatedDefinitions.obj: ComplicatedDefinitions.cpp 
PointerToFunction.obj: PointerToFunction.cpp 
FunctionTable.obj: FunctionTable.cpp 

