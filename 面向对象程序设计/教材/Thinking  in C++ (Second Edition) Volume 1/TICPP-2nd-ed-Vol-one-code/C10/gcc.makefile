# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C10
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
	StaticVariablesInfunctions \
	StaticObjectsInFunctions \
	StaticDestructors \
	LocalExtern \
	MyLib \
	Continuation \
	BobsSuperDuperLibrary \
	UnnamedNamespaces \
	FriendInjection \
	ScopeResolution \
	Arithmetic \
	NamespaceOverriding1 \
	OverridingAmbiguity \
	UsingDeclaration1 \
	UsingDeclaration2 \
	Statinit \
	StaticArray \
	StaticObjectArrays \
	Local \
	SimpleStaticMemberFunction \
	StaticMemberFunctions \
	Singleton \
	Oof \
	Initializer2 \
	Technique2 \
	Technique2b 

test: all 
	StaticVariablesInfunctions  
	StaticObjectsInFunctions  
	StaticDestructors  
	LocalExtern  
	MyLib  
	Continuation  
	BobsSuperDuperLibrary  
	UnnamedNamespaces  
	FriendInjection  
	ScopeResolution  
	Arithmetic  
	NamespaceOverriding1  
	OverridingAmbiguity  
	UsingDeclaration1  
	UsingDeclaration2  
	Statinit  
	StaticArray  
	StaticObjectArrays  
	Local  
	SimpleStaticMemberFunction  
	StaticMemberFunctions  
	Singleton  
	Oof  
	Initializer2  
	Technique2  
	Technique2b  

bugs: 
	@echo No compiler bugs in this directory!

StaticVariablesInfunctions: StaticVariablesInfunctions.o 
	$(CPP) $(OFLAG)StaticVariablesInfunctions StaticVariablesInfunctions.o 

StaticObjectsInFunctions: StaticObjectsInFunctions.o 
	$(CPP) $(OFLAG)StaticObjectsInFunctions StaticObjectsInFunctions.o 

StaticDestructors: StaticDestructors.o 
	$(CPP) $(OFLAG)StaticDestructors StaticDestructors.o 

LocalExtern: LocalExtern.o LocalExtern2.o 
	$(CPP) $(OFLAG)LocalExtern LocalExtern.o LocalExtern2.o 

MyLib: MyLib.o 
	$(CPP) $(OFLAG)MyLib MyLib.o 

Continuation: Continuation.o 
	$(CPP) $(OFLAG)Continuation Continuation.o 

BobsSuperDuperLibrary: BobsSuperDuperLibrary.o 
	$(CPP) $(OFLAG)BobsSuperDuperLibrary BobsSuperDuperLibrary.o 

UnnamedNamespaces: UnnamedNamespaces.o 
	$(CPP) $(OFLAG)UnnamedNamespaces UnnamedNamespaces.o 

FriendInjection: FriendInjection.o 
	$(CPP) $(OFLAG)FriendInjection FriendInjection.o 

ScopeResolution: ScopeResolution.o 
	$(CPP) $(OFLAG)ScopeResolution ScopeResolution.o 

Arithmetic: Arithmetic.o 
	$(CPP) $(OFLAG)Arithmetic Arithmetic.o 

NamespaceOverriding1: NamespaceOverriding1.o 
	$(CPP) $(OFLAG)NamespaceOverriding1 NamespaceOverriding1.o 

OverridingAmbiguity: OverridingAmbiguity.o 
	$(CPP) $(OFLAG)OverridingAmbiguity OverridingAmbiguity.o 

UsingDeclaration1: UsingDeclaration1.o 
	$(CPP) $(OFLAG)UsingDeclaration1 UsingDeclaration1.o 

UsingDeclaration2: UsingDeclaration2.o 
	$(CPP) $(OFLAG)UsingDeclaration2 UsingDeclaration2.o 

Statinit: Statinit.o 
	$(CPP) $(OFLAG)Statinit Statinit.o 

StaticArray: StaticArray.o 
	$(CPP) $(OFLAG)StaticArray StaticArray.o 

StaticObjectArrays: StaticObjectArrays.o 
	$(CPP) $(OFLAG)StaticObjectArrays StaticObjectArrays.o 

Local: Local.o 
	$(CPP) $(OFLAG)Local Local.o 

SimpleStaticMemberFunction: SimpleStaticMemberFunction.o 
	$(CPP) $(OFLAG)SimpleStaticMemberFunction SimpleStaticMemberFunction.o 

StaticMemberFunctions: StaticMemberFunctions.o 
	$(CPP) $(OFLAG)StaticMemberFunctions StaticMemberFunctions.o 

Singleton: Singleton.o 
	$(CPP) $(OFLAG)Singleton Singleton.o 

Oof: Oof.o Out.o 
	$(CPP) $(OFLAG)Oof Oof.o Out.o 

Initializer2: Initializer2.o InitializerDefs.o Initializer.o 
	$(CPP) $(OFLAG)Initializer2 Initializer2.o InitializerDefs.o Initializer.o 

Technique2: Technique2.o 
	$(CPP) $(OFLAG)Technique2 Technique2.o 

Technique2b: Technique2b.o Dependency1StatFun.o Dependency2StatFun.o 
	$(CPP) $(OFLAG)Technique2b Technique2b.o Dependency1StatFun.o Dependency2StatFun.o 


StaticVariablesInfunctions.o: StaticVariablesInfunctions.cpp ../require.h 
StaticObjectsInFunctions.o: StaticObjectsInFunctions.cpp 
StaticDestructors.o: StaticDestructors.cpp 
LocalExtern.o: LocalExtern.cpp 
LocalExtern2.o: LocalExtern2.cpp 
MyLib.o: MyLib.cpp 
Continuation.o: Continuation.cpp Header2.h 
BobsSuperDuperLibrary.o: BobsSuperDuperLibrary.cpp 
UnnamedNamespaces.o: UnnamedNamespaces.cpp 
FriendInjection.o: FriendInjection.cpp 
ScopeResolution.o: ScopeResolution.cpp 
Arithmetic.o: Arithmetic.cpp NamespaceInt.h 
NamespaceOverriding1.o: NamespaceOverriding1.cpp NamespaceMath.h 
OverridingAmbiguity.o: OverridingAmbiguity.cpp NamespaceMath.h NamespaceOverriding2.h 
UsingDeclaration1.o: UsingDeclaration1.cpp UsingDeclaration.h 
UsingDeclaration2.o: UsingDeclaration2.cpp UsingDeclaration.h 
Statinit.o: Statinit.cpp 
StaticArray.o: StaticArray.cpp 
StaticObjectArrays.o: StaticObjectArrays.cpp 
Local.o: Local.cpp 
SimpleStaticMemberFunction.o: SimpleStaticMemberFunction.cpp 
StaticMemberFunctions.o: StaticMemberFunctions.cpp 
Singleton.o: Singleton.cpp 
Out.o: Out.cpp 
Oof.o: Oof.cpp 
InitializerDefs.o: InitializerDefs.cpp Initializer.h 
Initializer.o: Initializer.cpp Initializer.h 
Initializer2.o: Initializer2.cpp Initializer.h 
Technique2.o: Technique2.cpp Dependency2.h 
Dependency1StatFun.o: Dependency1StatFun.cpp Dependency1StatFun.h 
Dependency2StatFun.o: Dependency2StatFun.cpp Dependency1StatFun.h Dependency2StatFun.h 
Technique2b.o: Technique2b.cpp Dependency2StatFun.h 

