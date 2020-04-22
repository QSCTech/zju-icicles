# From "Thinking in C++, 2nd Edition, Volume 2" 
# by Bruce Eckel & Chuck Allison
# Available at http://www.BruceEckel.com
# (c)2001 MindView Inc. Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory .\C03
# Invoke with: make compiler-name
# or: make clean

ifneq ($(MAKECMDGOALS),clean)
include ../$(MAKECMDGOALS).mac
endif

.SUFFIXES : .cpp .$(OBJEXT) .exe
.cpp.$(OBJEXT) :
	$(CPP) $(CPPFLAGS) $(OFLAGS) $<
.cpp.exe :
	$(CPP) $(CPPFLAGS) $< $(EXEFLAG)$@


Borland:  \
	Tracetst.exe \
	MemCheck.$(OBJEXT) \
	MemTest.exe

Microsoft:  \
	Tracetst.exe

g++295:  \
	Tracetst.exe \
	MemCheck.$(OBJEXT) \
	MemTest.exe

g++3:  \
	Tracetst.exe \
	MemCheck.$(OBJEXT) \
	MemTest.exe

edg:  \
	Tracetst.exe \
	MemCheck.$(OBJEXT) \
	MemTest.exe

clean:
ifeq ($(notdir $(SHELL)),COMMAND.COM)
	del *.obj
	del *.exe
	del *.tds
	del *.o
else
	rm -f *.o *.obj *.exe *.tds
endif


Tracetst.exe: Tracetst.cpp

MemCheck.$(OBJEXT): MemCheck.cpp

MemTest.exe: MemCheck.$(OBJEXT) MemTest.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)MemTest.exe MemTest.$(OBJEXT) MemCheck.$(OBJEXT)

MemTest.$(OBJEXT): MemTest.cpp
