# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C15
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
	Instrument2.exe \
	Instrument3.exe \
	Instrument4.exe \
	Sizes.exe \
	Early.exe \
	Instrument5.exe \
	PureVirtualDefinitions.exe \
	AddingVirtuals.exe \
	ObjectSlicing.exe \
	NameHiding2.exe \
	VariantReturn.exe \
	VirtualDestructors.exe \
	UnAbstract.exe \
	PureVirtualDestructors.exe \
	VirtualsInDestructors.exe \
	OStackTest.exe \
	OperatorPolymorphism.exe \
	DynamicCast.exe \
	StaticHierarchyNavigation.exe 

test: all 
	Instrument2.exe  
	Instrument3.exe  
	Instrument4.exe  
	Sizes.exe  
	Early.exe  
	Instrument5.exe  
	PureVirtualDefinitions.exe  
	AddingVirtuals.exe  
	ObjectSlicing.exe  
	NameHiding2.exe  
	VariantReturn.exe  
	VirtualDestructors.exe  
	UnAbstract.exe  
	PureVirtualDestructors.exe  
	VirtualsInDestructors.exe  
	OStackTest.exe OStackTest.cpp 
	OperatorPolymorphism.exe  
	DynamicCast.exe  
	StaticHierarchyNavigation.exe  

bugs: 
	@echo No compiler bugs in this directory!

Instrument2.exe: Instrument2.obj 
	$(CPP) $(OFLAG)Instrument2.exe Instrument2.obj 

Instrument3.exe: Instrument3.obj 
	$(CPP) $(OFLAG)Instrument3.exe Instrument3.obj 

Instrument4.exe: Instrument4.obj 
	$(CPP) $(OFLAG)Instrument4.exe Instrument4.obj 

Sizes.exe: Sizes.obj 
	$(CPP) $(OFLAG)Sizes.exe Sizes.obj 

Early.exe: Early.obj 
	$(CPP) $(OFLAG)Early.exe Early.obj 

Instrument5.exe: Instrument5.obj 
	$(CPP) $(OFLAG)Instrument5.exe Instrument5.obj 

PureVirtualDefinitions.exe: PureVirtualDefinitions.obj 
	$(CPP) $(OFLAG)PureVirtualDefinitions.exe PureVirtualDefinitions.obj 

AddingVirtuals.exe: AddingVirtuals.obj 
	$(CPP) $(OFLAG)AddingVirtuals.exe AddingVirtuals.obj 

ObjectSlicing.exe: ObjectSlicing.obj 
	$(CPP) $(OFLAG)ObjectSlicing.exe ObjectSlicing.obj 

NameHiding2.exe: NameHiding2.obj 
	$(CPP) $(OFLAG)NameHiding2.exe NameHiding2.obj 

VariantReturn.exe: VariantReturn.obj 
	$(CPP) $(OFLAG)VariantReturn.exe VariantReturn.obj 

VirtualDestructors.exe: VirtualDestructors.obj 
	$(CPP) $(OFLAG)VirtualDestructors.exe VirtualDestructors.obj 

UnAbstract.exe: UnAbstract.obj 
	$(CPP) $(OFLAG)UnAbstract.exe UnAbstract.obj 

PureVirtualDestructors.exe: PureVirtualDestructors.obj 
	$(CPP) $(OFLAG)PureVirtualDestructors.exe PureVirtualDestructors.obj 

VirtualsInDestructors.exe: VirtualsInDestructors.obj 
	$(CPP) $(OFLAG)VirtualsInDestructors.exe VirtualsInDestructors.obj 

OStackTest.exe: OStackTest.obj 
	$(CPP) $(OFLAG)OStackTest.exe OStackTest.obj 

OperatorPolymorphism.exe: OperatorPolymorphism.obj 
	$(CPP) $(OFLAG)OperatorPolymorphism.exe OperatorPolymorphism.obj 

DynamicCast.exe: DynamicCast.obj 
	$(CPP) $(OFLAG)DynamicCast.exe DynamicCast.obj 

StaticHierarchyNavigation.exe: StaticHierarchyNavigation.obj 
	$(CPP) $(OFLAG)StaticHierarchyNavigation.exe StaticHierarchyNavigation.obj 


Instrument2.obj: Instrument2.cpp 
Instrument3.obj: Instrument3.cpp 
Instrument4.obj: Instrument4.cpp 
Sizes.obj: Sizes.cpp 
Early.obj: Early.cpp 
Instrument5.obj: Instrument5.cpp 
PureVirtualDefinitions.obj: PureVirtualDefinitions.cpp 
AddingVirtuals.obj: AddingVirtuals.cpp 
ObjectSlicing.obj: ObjectSlicing.cpp 
NameHiding2.obj: NameHiding2.cpp 
VariantReturn.obj: VariantReturn.cpp 
VirtualDestructors.obj: VirtualDestructors.cpp 
UnAbstract.obj: UnAbstract.cpp 
PureVirtualDestructors.obj: PureVirtualDestructors.cpp 
VirtualsInDestructors.obj: VirtualsInDestructors.cpp 
OStackTest.obj: OStackTest.cpp OStack.h ..\require.h 
OperatorPolymorphism.obj: OperatorPolymorphism.cpp 
DynamicCast.obj: DynamicCast.cpp 
StaticHierarchyNavigation.obj: StaticHierarchyNavigation.cpp 

