# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C15
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
	Instrument2 \
	Instrument3 \
	Instrument4 \
	Sizes \
	Early \
	Instrument5 \
	PureVirtualDefinitions \
	AddingVirtuals \
	ObjectSlicing \
	NameHiding2 \
	VariantReturn \
	VirtualDestructors \
	UnAbstract \
	PureVirtualDestructors \
	VirtualsInDestructors \
	OStackTest \
	OperatorPolymorphism \
	DynamicCast \
	StaticHierarchyNavigation 

test: all 
	Instrument2  
	Instrument3  
	Instrument4  
	Sizes  
	Early  
	Instrument5  
	PureVirtualDefinitions  
	AddingVirtuals  
	ObjectSlicing  
	NameHiding2  
	VariantReturn  
	VirtualDestructors  
	UnAbstract  
	PureVirtualDestructors  
	VirtualsInDestructors  
	OStackTest OStackTest.cpp 
	OperatorPolymorphism  
	DynamicCast  
	StaticHierarchyNavigation  

bugs: 
	@echo No compiler bugs in this directory!

Instrument2: Instrument2.o 
	$(CPP) $(OFLAG)Instrument2 Instrument2.o 

Instrument3: Instrument3.o 
	$(CPP) $(OFLAG)Instrument3 Instrument3.o 

Instrument4: Instrument4.o 
	$(CPP) $(OFLAG)Instrument4 Instrument4.o 

Sizes: Sizes.o 
	$(CPP) $(OFLAG)Sizes Sizes.o 

Early: Early.o 
	$(CPP) $(OFLAG)Early Early.o 

Instrument5: Instrument5.o 
	$(CPP) $(OFLAG)Instrument5 Instrument5.o 

PureVirtualDefinitions: PureVirtualDefinitions.o 
	$(CPP) $(OFLAG)PureVirtualDefinitions PureVirtualDefinitions.o 

AddingVirtuals: AddingVirtuals.o 
	$(CPP) $(OFLAG)AddingVirtuals AddingVirtuals.o 

ObjectSlicing: ObjectSlicing.o 
	$(CPP) $(OFLAG)ObjectSlicing ObjectSlicing.o 

NameHiding2: NameHiding2.o 
	$(CPP) $(OFLAG)NameHiding2 NameHiding2.o 

VariantReturn: VariantReturn.o 
	$(CPP) $(OFLAG)VariantReturn VariantReturn.o 

VirtualDestructors: VirtualDestructors.o 
	$(CPP) $(OFLAG)VirtualDestructors VirtualDestructors.o 

UnAbstract: UnAbstract.o 
	$(CPP) $(OFLAG)UnAbstract UnAbstract.o 

PureVirtualDestructors: PureVirtualDestructors.o 
	$(CPP) $(OFLAG)PureVirtualDestructors PureVirtualDestructors.o 

VirtualsInDestructors: VirtualsInDestructors.o 
	$(CPP) $(OFLAG)VirtualsInDestructors VirtualsInDestructors.o 

OStackTest: OStackTest.o 
	$(CPP) $(OFLAG)OStackTest OStackTest.o 

OperatorPolymorphism: OperatorPolymorphism.o 
	$(CPP) $(OFLAG)OperatorPolymorphism OperatorPolymorphism.o 

DynamicCast: DynamicCast.o 
	$(CPP) $(OFLAG)DynamicCast DynamicCast.o 

StaticHierarchyNavigation: StaticHierarchyNavigation.o 
	$(CPP) $(OFLAG)StaticHierarchyNavigation StaticHierarchyNavigation.o 


Instrument2.o: Instrument2.cpp 
Instrument3.o: Instrument3.cpp 
Instrument4.o: Instrument4.cpp 
Sizes.o: Sizes.cpp 
Early.o: Early.cpp 
Instrument5.o: Instrument5.cpp 
PureVirtualDefinitions.o: PureVirtualDefinitions.cpp 
AddingVirtuals.o: AddingVirtuals.cpp 
ObjectSlicing.o: ObjectSlicing.cpp 
NameHiding2.o: NameHiding2.cpp 
VariantReturn.o: VariantReturn.cpp 
VirtualDestructors.o: VirtualDestructors.cpp 
UnAbstract.o: UnAbstract.cpp 
PureVirtualDestructors.o: PureVirtualDestructors.cpp 
VirtualsInDestructors.o: VirtualsInDestructors.cpp 
OStackTest.o: OStackTest.cpp OStack.h ../require.h 
OperatorPolymorphism.o: OperatorPolymorphism.cpp 
DynamicCast.o: DynamicCast.cpp 
StaticHierarchyNavigation.o: StaticHierarchyNavigation.cpp 

