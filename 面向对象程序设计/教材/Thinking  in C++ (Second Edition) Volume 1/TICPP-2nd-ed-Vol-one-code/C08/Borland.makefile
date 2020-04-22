# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C08
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
	Safecons.exe \
	Constag.exe \
	ConstPointers.exe \
	PointerAssignment.exe \
	Constval.exe \
	ConstReturnValues.exe \
	ConstPointer.exe \
	ConstTemporary.exe \
	ConstInitialization.exe \
	BuiltInTypeConstructors.exe \
	EncapsulatingTypes.exe \
	StringStack.exe \
	EnumHack.exe \
	ConstMember.exe \
	Quoter.exe \
	Castaway.exe \
	Mutable.exe \
	Volatile.exe 

test: all 
	Safecons.exe  
	Constag.exe  
	ConstPointers.exe  
	PointerAssignment.exe  
	Constval.exe  
	ConstReturnValues.exe  
	ConstPointer.exe  
	ConstTemporary.exe  
	ConstInitialization.exe  
	BuiltInTypeConstructors.exe  
	EncapsulatingTypes.exe  
	StringStack.exe  
	EnumHack.exe  
	ConstMember.exe  
	Quoter.exe  
	Castaway.exe  
	Mutable.exe  
	Volatile.exe  

bugs: 
	@echo No compiler bugs in this directory!

Safecons.exe: Safecons.obj 
	$(CPP) $(OFLAG)Safecons.exe Safecons.obj 

Constag.exe: Constag.obj 
	$(CPP) $(OFLAG)Constag.exe Constag.obj 

ConstPointers.exe: ConstPointers.obj 
	$(CPP) $(OFLAG)ConstPointers.exe ConstPointers.obj 

PointerAssignment.exe: PointerAssignment.obj 
	$(CPP) $(OFLAG)PointerAssignment.exe PointerAssignment.obj 

Constval.exe: Constval.obj 
	$(CPP) $(OFLAG)Constval.exe Constval.obj 

ConstReturnValues.exe: ConstReturnValues.obj 
	$(CPP) $(OFLAG)ConstReturnValues.exe ConstReturnValues.obj 

ConstPointer.exe: ConstPointer.obj 
	$(CPP) $(OFLAG)ConstPointer.exe ConstPointer.obj 

ConstTemporary.exe: ConstTemporary.obj 
	$(CPP) $(OFLAG)ConstTemporary.exe ConstTemporary.obj 

ConstInitialization.exe: ConstInitialization.obj 
	$(CPP) $(OFLAG)ConstInitialization.exe ConstInitialization.obj 

BuiltInTypeConstructors.exe: BuiltInTypeConstructors.obj 
	$(CPP) $(OFLAG)BuiltInTypeConstructors.exe BuiltInTypeConstructors.obj 

EncapsulatingTypes.exe: EncapsulatingTypes.obj 
	$(CPP) $(OFLAG)EncapsulatingTypes.exe EncapsulatingTypes.obj 

StringStack.exe: StringStack.obj 
	$(CPP) $(OFLAG)StringStack.exe StringStack.obj 

EnumHack.exe: EnumHack.obj 
	$(CPP) $(OFLAG)EnumHack.exe EnumHack.obj 

ConstMember.exe: ConstMember.obj 
	$(CPP) $(OFLAG)ConstMember.exe ConstMember.obj 

Quoter.exe: Quoter.obj 
	$(CPP) $(OFLAG)Quoter.exe Quoter.obj 

Castaway.exe: Castaway.obj 
	$(CPP) $(OFLAG)Castaway.exe Castaway.obj 

Mutable.exe: Mutable.obj 
	$(CPP) $(OFLAG)Mutable.exe Mutable.obj 

Volatile.exe: Volatile.obj 
	$(CPP) $(OFLAG)Volatile.exe Volatile.obj 


Safecons.obj: Safecons.cpp 
Constag.obj: Constag.cpp 
ConstPointers.obj: ConstPointers.cpp 
PointerAssignment.obj: PointerAssignment.cpp 
Constval.obj: Constval.cpp 
ConstReturnValues.obj: ConstReturnValues.cpp 
ConstPointer.obj: ConstPointer.cpp 
ConstTemporary.obj: ConstTemporary.cpp 
ConstInitialization.obj: ConstInitialization.cpp 
BuiltInTypeConstructors.obj: BuiltInTypeConstructors.cpp 
EncapsulatingTypes.obj: EncapsulatingTypes.cpp 
StringStack.obj: StringStack.cpp 
EnumHack.obj: EnumHack.cpp 
ConstMember.obj: ConstMember.cpp 
Quoter.obj: Quoter.cpp 
Castaway.obj: Castaway.cpp 
Mutable.obj: Mutable.cpp 
Volatile.obj: Volatile.cpp 

