# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C13
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
	MallocClass \
	NewAndDelete \
	BadVoidPointerDeletion \
	PStashTest \
	GlobalOperatorNew \
	Framis \
	ArrayOperatorNew \
	NoMemory \
	PlacementOperatorNew 

test: all 
	MallocClass  
	NewAndDelete  
	BadVoidPointerDeletion  
	PStashTest  
	GlobalOperatorNew  
	Framis  
	ArrayOperatorNew  
	NoMemory  
	PlacementOperatorNew  

bugs: \
	NewHandler 

MallocClass: MallocClass.o 
	$(CPP) $(OFLAG)MallocClass MallocClass.o 

NewAndDelete: NewAndDelete.o 
	$(CPP) $(OFLAG)NewAndDelete NewAndDelete.o 

BadVoidPointerDeletion: BadVoidPointerDeletion.o 
	$(CPP) $(OFLAG)BadVoidPointerDeletion BadVoidPointerDeletion.o 

PStashTest: PStashTest.o PStash.o 
	$(CPP) $(OFLAG)PStashTest PStashTest.o PStash.o 

NewHandler: NewHandler.o 
	$(CPP) $(OFLAG)NewHandler NewHandler.o 

GlobalOperatorNew: GlobalOperatorNew.o 
	$(CPP) $(OFLAG)GlobalOperatorNew GlobalOperatorNew.o 

Framis: Framis.o 
	$(CPP) $(OFLAG)Framis Framis.o 

ArrayOperatorNew: ArrayOperatorNew.o 
	$(CPP) $(OFLAG)ArrayOperatorNew ArrayOperatorNew.o 

NoMemory: NoMemory.o 
	$(CPP) $(OFLAG)NoMemory NoMemory.o 

PlacementOperatorNew: PlacementOperatorNew.o 
	$(CPP) $(OFLAG)PlacementOperatorNew PlacementOperatorNew.o 


MallocClass.o: MallocClass.cpp ../require.h 
NewAndDelete.o: NewAndDelete.cpp Tree.h 
BadVoidPointerDeletion.o: BadVoidPointerDeletion.cpp 
PStash.o: PStash.cpp PStash.h ../require.h 
PStashTest.o: PStashTest.cpp PStash.h ../require.h 
NewHandler.o: NewHandler.cpp 
GlobalOperatorNew.o: GlobalOperatorNew.cpp 
Framis.o: Framis.cpp 
ArrayOperatorNew.o: ArrayOperatorNew.cpp 
NoMemory.o: NoMemory.cpp 
PlacementOperatorNew.o: PlacementOperatorNew.cpp 

