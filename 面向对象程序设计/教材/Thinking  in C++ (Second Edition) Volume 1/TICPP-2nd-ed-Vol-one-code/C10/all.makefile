# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C10
# using the all compiler
# Note: does not make files that will 
# not compile with this compiler
# Invoke with: make -f all.makefile

.SUFFIXES : .obj .cpp .c
.cpp.obj :
	$(CPP) $(CPPFLAGS) -c $<
.c.obj :
	$(CPP) $(CPPFLAGS) -c $<

all: \
	StaticVariablesInfunctions.exe \
	StaticObjectsInFunctions.exe \
	StaticDestructors.exe \
	LocalExtern.exe \
	MyLib.exe \
	Continuation.exe \
	BobsSuperDuperLibrary.exe \
	UnnamedNamespaces.exe \
	FriendInjection.exe \
	ScopeResolution.exe \
	Arithmetic.exe \
	NamespaceOverriding1.exe \
	OverridingAmbiguity.exe \
	UsingDeclaration1.exe \
	UsingDeclaration2.exe \
	Statinit.exe \
	StaticArray.exe \
	StaticObjectArrays.exe \
	Local.exe \
	SimpleStaticMemberFunction.exe \
	StaticMemberFunctions.exe \
	Singleton.exe \
	Oof.exe \
	Initializer2.exe \
	Technique2.exe \
	Technique2b.exe 

test: all 
	StaticVariablesInfunctions.exe  
	StaticObjectsInFunctions.exe  
	StaticDestructors.exe  
	LocalExtern.exe  
	MyLib.exe  
	Continuation.exe  
	BobsSuperDuperLibrary.exe  
	UnnamedNamespaces.exe  
	FriendInjection.exe  
	ScopeResolution.exe  
	Arithmetic.exe  
	NamespaceOverriding1.exe  
	OverridingAmbiguity.exe  
	UsingDeclaration1.exe  
	UsingDeclaration2.exe  
	Statinit.exe  
	StaticArray.exe  
	StaticObjectArrays.exe  
	Local.exe  
	SimpleStaticMemberFunction.exe  
	StaticMemberFunctions.exe  
	Singleton.exe  
	Oof.exe  
	Initializer2.exe  
	Technique2.exe  
	Technique2b.exe  

bugs: 
	@echo No compiler bugs in this directory!

StaticVariablesInfunctions.exe: StaticVariablesInfunctions.obj 
	$(CPP) $(OFLAG)StaticVariablesInfunctions.exe StaticVariablesInfunctions.obj 

StaticObjectsInFunctions.exe: StaticObjectsInFunctions.obj 
	$(CPP) $(OFLAG)StaticObjectsInFunctions.exe StaticObjectsInFunctions.obj 

StaticDestructors.exe: StaticDestructors.obj 
	$(CPP) $(OFLAG)StaticDestructors.exe StaticDestructors.obj 

LocalExtern.exe: LocalExtern.obj LocalExtern2.obj 
	$(CPP) $(OFLAG)LocalExtern.exe LocalExtern.obj LocalExtern2.obj 

MyLib.exe: MyLib.obj 
	$(CPP) $(OFLAG)MyLib.exe MyLib.obj 

Continuation.exe: Continuation.obj 
	$(CPP) $(OFLAG)Continuation.exe Continuation.obj 

BobsSuperDuperLibrary.exe: BobsSuperDuperLibrary.obj 
	$(CPP) $(OFLAG)BobsSuperDuperLibrary.exe BobsSuperDuperLibrary.obj 

UnnamedNamespaces.exe: UnnamedNamespaces.obj 
	$(CPP) $(OFLAG)UnnamedNamespaces.exe UnnamedNamespaces.obj 

FriendInjection.exe: FriendInjection.obj 
	$(CPP) $(OFLAG)FriendInjection.exe FriendInjection.obj 

ScopeResolution.exe: ScopeResolution.obj 
	$(CPP) $(OFLAG)ScopeResolution.exe ScopeResolution.obj 

Arithmetic.exe: Arithmetic.obj 
	$(CPP) $(OFLAG)Arithmetic.exe Arithmetic.obj 

NamespaceOverriding1.exe: NamespaceOverriding1.obj 
	$(CPP) $(OFLAG)NamespaceOverriding1.exe NamespaceOverriding1.obj 

OverridingAmbiguity.exe: OverridingAmbiguity.obj 
	$(CPP) $(OFLAG)OverridingAmbiguity.exe OverridingAmbiguity.obj 

UsingDeclaration1.exe: UsingDeclaration1.obj 
	$(CPP) $(OFLAG)UsingDeclaration1.exe UsingDeclaration1.obj 

UsingDeclaration2.exe: UsingDeclaration2.obj 
	$(CPP) $(OFLAG)UsingDeclaration2.exe UsingDeclaration2.obj 

Statinit.exe: Statinit.obj 
	$(CPP) $(OFLAG)Statinit.exe Statinit.obj 

StaticArray.exe: StaticArray.obj 
	$(CPP) $(OFLAG)StaticArray.exe StaticArray.obj 

StaticObjectArrays.exe: StaticObjectArrays.obj 
	$(CPP) $(OFLAG)StaticObjectArrays.exe StaticObjectArrays.obj 

Local.exe: Local.obj 
	$(CPP) $(OFLAG)Local.exe Local.obj 

SimpleStaticMemberFunction.exe: SimpleStaticMemberFunction.obj 
	$(CPP) $(OFLAG)SimpleStaticMemberFunction.exe SimpleStaticMemberFunction.obj 

StaticMemberFunctions.exe: StaticMemberFunctions.obj 
	$(CPP) $(OFLAG)StaticMemberFunctions.exe StaticMemberFunctions.obj 

Singleton.exe: Singleton.obj 
	$(CPP) $(OFLAG)Singleton.exe Singleton.obj 

Oof.exe: Oof.obj Out.obj 
	$(CPP) $(OFLAG)Oof.exe Oof.obj Out.obj 

Initializer2.exe: Initializer2.obj InitializerDefs.obj Initializer.obj 
	$(CPP) $(OFLAG)Initializer2.exe Initializer2.obj InitializerDefs.obj Initializer.obj 

Technique2.exe: Technique2.obj 
	$(CPP) $(OFLAG)Technique2.exe Technique2.obj 

Technique2b.exe: Technique2b.obj Dependency1StatFun.obj Dependency2StatFun.obj 
	$(CPP) $(OFLAG)Technique2b.exe Technique2b.obj Dependency1StatFun.obj Dependency2StatFun.obj 


StaticVariablesInfunctions.obj: StaticVariablesInfunctions.cpp ..\require.h 
StaticObjectsInFunctions.obj: StaticObjectsInFunctions.cpp 
StaticDestructors.obj: StaticDestructors.cpp 
LocalExtern.obj: LocalExtern.cpp 
LocalExtern2.obj: LocalExtern2.cpp 
MyLib.obj: MyLib.cpp 
Continuation.obj: Continuation.cpp Header2.h 
BobsSuperDuperLibrary.obj: BobsSuperDuperLibrary.cpp 
UnnamedNamespaces.obj: UnnamedNamespaces.cpp 
FriendInjection.obj: FriendInjection.cpp 
ScopeResolution.obj: ScopeResolution.cpp 
Arithmetic.obj: Arithmetic.cpp NamespaceInt.h 
NamespaceOverriding1.obj: NamespaceOverriding1.cpp NamespaceMath.h 
OverridingAmbiguity.obj: OverridingAmbiguity.cpp NamespaceMath.h NamespaceOverriding2.h 
UsingDeclaration1.obj: UsingDeclaration1.cpp UsingDeclaration.h 
UsingDeclaration2.obj: UsingDeclaration2.cpp UsingDeclaration.h 
Statinit.obj: Statinit.cpp 
StaticArray.obj: StaticArray.cpp 
StaticObjectArrays.obj: StaticObjectArrays.cpp 
Local.obj: Local.cpp 
SimpleStaticMemberFunction.obj: SimpleStaticMemberFunction.cpp 
StaticMemberFunctions.obj: StaticMemberFunctions.cpp 
Singleton.obj: Singleton.cpp 
Out.obj: Out.cpp 
Oof.obj: Oof.cpp 
InitializerDefs.obj: InitializerDefs.cpp Initializer.h 
Initializer.obj: Initializer.cpp Initializer.h 
Initializer2.obj: Initializer2.cpp Initializer.h 
Technique2.obj: Technique2.cpp Dependency2.h 
Dependency1StatFun.obj: Dependency1StatFun.cpp Dependency1StatFun.h 
Dependency2StatFun.obj: Dependency2StatFun.cpp Dependency1StatFun.h Dependency2StatFun.h 
Technique2b.obj: Technique2b.cpp Dependency2StatFun.h 

