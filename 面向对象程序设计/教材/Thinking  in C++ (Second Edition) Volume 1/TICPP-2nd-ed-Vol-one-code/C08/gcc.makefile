# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C08
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
	Safecons \
	Constag \
	ConstPointers \
	PointerAssignment \
	Constval \
	ConstReturnValues \
	ConstPointer \
	ConstTemporary \
	ConstInitialization \
	BuiltInTypeConstructors \
	EncapsulatingTypes \
	StringStack \
	EnumHack \
	ConstMember \
	Quoter \
	Castaway \
	Mutable \
	Volatile 

test: all 
	Safecons  
	Constag  
	ConstPointers  
	PointerAssignment  
	Constval  
	ConstReturnValues  
	ConstPointer  
	ConstTemporary  
	ConstInitialization  
	BuiltInTypeConstructors  
	EncapsulatingTypes  
	StringStack  
	EnumHack  
	ConstMember  
	Quoter  
	Castaway  
	Mutable  
	Volatile  

bugs: 
	@echo No compiler bugs in this directory!

Safecons: Safecons.o 
	$(CPP) $(OFLAG)Safecons Safecons.o 

Constag: Constag.o 
	$(CPP) $(OFLAG)Constag Constag.o 

ConstPointers: ConstPointers.o 
	$(CPP) $(OFLAG)ConstPointers ConstPointers.o 

PointerAssignment: PointerAssignment.o 
	$(CPP) $(OFLAG)PointerAssignment PointerAssignment.o 

Constval: Constval.o 
	$(CPP) $(OFLAG)Constval Constval.o 

ConstReturnValues: ConstReturnValues.o 
	$(CPP) $(OFLAG)ConstReturnValues ConstReturnValues.o 

ConstPointer: ConstPointer.o 
	$(CPP) $(OFLAG)ConstPointer ConstPointer.o 

ConstTemporary: ConstTemporary.o 
	$(CPP) $(OFLAG)ConstTemporary ConstTemporary.o 

ConstInitialization: ConstInitialization.o 
	$(CPP) $(OFLAG)ConstInitialization ConstInitialization.o 

BuiltInTypeConstructors: BuiltInTypeConstructors.o 
	$(CPP) $(OFLAG)BuiltInTypeConstructors BuiltInTypeConstructors.o 

EncapsulatingTypes: EncapsulatingTypes.o 
	$(CPP) $(OFLAG)EncapsulatingTypes EncapsulatingTypes.o 

StringStack: StringStack.o 
	$(CPP) $(OFLAG)StringStack StringStack.o 

EnumHack: EnumHack.o 
	$(CPP) $(OFLAG)EnumHack EnumHack.o 

ConstMember: ConstMember.o 
	$(CPP) $(OFLAG)ConstMember ConstMember.o 

Quoter: Quoter.o 
	$(CPP) $(OFLAG)Quoter Quoter.o 

Castaway: Castaway.o 
	$(CPP) $(OFLAG)Castaway Castaway.o 

Mutable: Mutable.o 
	$(CPP) $(OFLAG)Mutable Mutable.o 

Volatile: Volatile.o 
	$(CPP) $(OFLAG)Volatile Volatile.o 


Safecons.o: Safecons.cpp 
Constag.o: Constag.cpp 
ConstPointers.o: ConstPointers.cpp 
PointerAssignment.o: PointerAssignment.cpp 
Constval.o: Constval.cpp 
ConstReturnValues.o: ConstReturnValues.cpp 
ConstPointer.o: ConstPointer.cpp 
ConstTemporary.o: ConstTemporary.cpp 
ConstInitialization.o: ConstInitialization.cpp 
BuiltInTypeConstructors.o: BuiltInTypeConstructors.cpp 
EncapsulatingTypes.o: EncapsulatingTypes.cpp 
StringStack.o: StringStack.cpp 
EnumHack.o: EnumHack.cpp 
ConstMember.o: ConstMember.cpp 
Quoter.o: Quoter.cpp 
Castaway.o: Castaway.cpp 
Mutable.o: Mutable.cpp 
Volatile.o: Volatile.cpp 

