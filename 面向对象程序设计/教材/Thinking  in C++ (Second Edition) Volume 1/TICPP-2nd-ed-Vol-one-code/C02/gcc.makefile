# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C02
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
	Declare \
	Hello \
	Stream2 \
	Concat \
	Numconv \
	CallHello \
	HelloStrings \
	Scopy \
	FillString \
	Fillvector \
	GetWords \
	Intvector 

test: all 
	Declare  
	Hello  
	Stream2  
	Concat  
	Numconv  
	CallHello  
	HelloStrings  
	Scopy  
	FillString  
	Fillvector  
	GetWords  
	Intvector  

bugs: 
	@echo No compiler bugs in this directory!

Declare: Declare.o 
	$(CPP) $(OFLAG)Declare Declare.o 

Hello: Hello.o 
	$(CPP) $(OFLAG)Hello Hello.o 

Stream2: Stream2.o 
	$(CPP) $(OFLAG)Stream2 Stream2.o 

Concat: Concat.o 
	$(CPP) $(OFLAG)Concat Concat.o 

Numconv: Numconv.o 
	$(CPP) $(OFLAG)Numconv Numconv.o 

CallHello: CallHello.o 
	$(CPP) $(OFLAG)CallHello CallHello.o 

HelloStrings: HelloStrings.o 
	$(CPP) $(OFLAG)HelloStrings HelloStrings.o 

Scopy: Scopy.o 
	$(CPP) $(OFLAG)Scopy Scopy.o 

FillString: FillString.o 
	$(CPP) $(OFLAG)FillString FillString.o 

Fillvector: Fillvector.o 
	$(CPP) $(OFLAG)Fillvector Fillvector.o 

GetWords: GetWords.o 
	$(CPP) $(OFLAG)GetWords GetWords.o 

Intvector: Intvector.o 
	$(CPP) $(OFLAG)Intvector Intvector.o 


Declare.o: Declare.cpp 
Hello.o: Hello.cpp 
Stream2.o: Stream2.cpp 
Concat.o: Concat.cpp 
Numconv.o: Numconv.cpp 
CallHello.o: CallHello.cpp 
HelloStrings.o: HelloStrings.cpp 
Scopy.o: Scopy.cpp 
FillString.o: FillString.cpp 
Fillvector.o: Fillvector.cpp 
GetWords.o: GetWords.cpp 
Intvector.o: Intvector.cpp 

