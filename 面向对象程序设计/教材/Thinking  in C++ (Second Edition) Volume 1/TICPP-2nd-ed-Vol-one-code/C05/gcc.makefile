# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C05
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
	Public \
	Private \
	Friend \
	NestFriend \
	Class \
	UseHandle 

test: all 
	Public  
	Private  
	Friend  
	NestFriend  
	Class  
	UseHandle  

bugs: 
	@echo No compiler bugs in this directory!

Public: Public.o 
	$(CPP) $(OFLAG)Public Public.o 

Private: Private.o 
	$(CPP) $(OFLAG)Private Private.o 

Friend: Friend.o 
	$(CPP) $(OFLAG)Friend Friend.o 

NestFriend: NestFriend.o 
	$(CPP) $(OFLAG)NestFriend NestFriend.o 

Class: Class.o 
	$(CPP) $(OFLAG)Class Class.o 

UseHandle: UseHandle.o Handle.o 
	$(CPP) $(OFLAG)UseHandle UseHandle.o Handle.o 


Public.o: Public.cpp 
Private.o: Private.cpp 
Friend.o: Friend.cpp 
NestFriend.o: NestFriend.cpp 
Class.o: Class.cpp 
Handle.o: Handle.cpp Handle.h ../require.h 
UseHandle.o: UseHandle.cpp Handle.h 

