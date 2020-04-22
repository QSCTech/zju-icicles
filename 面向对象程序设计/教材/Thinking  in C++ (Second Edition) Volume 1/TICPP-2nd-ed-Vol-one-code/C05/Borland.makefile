# From Thinking in C++, 2nd Edition
# At http://www.BruceEckel.com
# (c) Bruce Eckel 1999
# Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory C05
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
	Public.exe \
	Private.exe \
	Friend.exe \
	NestFriend.exe \
	Class.exe \
	UseHandle.exe 

test: all 
	Public.exe  
	Private.exe  
	Friend.exe  
	NestFriend.exe  
	Class.exe  
	UseHandle.exe  

bugs: 
	@echo No compiler bugs in this directory!

Public.exe: Public.obj 
	$(CPP) $(OFLAG)Public.exe Public.obj 

Private.exe: Private.obj 
	$(CPP) $(OFLAG)Private.exe Private.obj 

Friend.exe: Friend.obj 
	$(CPP) $(OFLAG)Friend.exe Friend.obj 

NestFriend.exe: NestFriend.obj 
	$(CPP) $(OFLAG)NestFriend.exe NestFriend.obj 

Class.exe: Class.obj 
	$(CPP) $(OFLAG)Class.exe Class.obj 

UseHandle.exe: UseHandle.obj Handle.obj 
	$(CPP) $(OFLAG)UseHandle.exe UseHandle.obj Handle.obj 


Public.obj: Public.cpp 
Private.obj: Private.cpp 
Friend.obj: Friend.cpp 
NestFriend.obj: NestFriend.cpp 
Class.obj: Class.cpp 
Handle.obj: Handle.cpp Handle.h ..\require.h 
UseHandle.obj: UseHandle.cpp Handle.h 

