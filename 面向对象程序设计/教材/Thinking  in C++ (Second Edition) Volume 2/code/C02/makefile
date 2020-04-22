# From "Thinking in C++, 2nd Edition, Volume 2" 
# by Bruce Eckel & Chuck Allison
# Available at http://www.BruceEckel.com
# (c)2001 MindView Inc. Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory .\C02
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
	Date.$(OBJEXT) \
	SimpleDateTest.exe \
	DateTest.exe \
	StackTest.exe \
	SuiteExample.exe

Microsoft:  \
	Date.$(OBJEXT) \
	SimpleDateTest.exe \
	DateTest.exe \
	StackTest.exe \
	SuiteExample.exe

g++295:  \
	Date.$(OBJEXT) \
	SimpleDateTest.exe \
	DateTest.exe \
	StackTest.exe \
	SuiteExample.exe

g++3:  \
	Date.$(OBJEXT) \
	SimpleDateTest.exe \
	DateTest.exe \
	StackTest.exe \
	SuiteExample.exe

edg:  \
	Date.$(OBJEXT) \
	SimpleDateTest.exe \
	DateTest.exe \
	StackTest.exe \
	SuiteExample.exe

clean:
ifeq ($(notdir $(SHELL)),COMMAND.COM)
	del *.obj
	del *.exe
	del *.tds
	del *.o
else
	rm -f *.o *.obj *.exe *.tds
endif


Date.$(OBJEXT): Date.cpp

SimpleDateTest.exe: Date.$(OBJEXT) SimpleDateTest.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)SimpleDateTest.exe SimpleDateTest.$(OBJEXT) Date.$(OBJEXT)

SimpleDateTest.$(OBJEXT): SimpleDateTest.cpp
DateTest.exe: Date.$(OBJEXT) ../TestSuite/Test.$(OBJEXT) DateTest.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)DateTest.exe DateTest.$(OBJEXT) Date.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	DateTest.exe
endif

DateTest.$(OBJEXT): DateTest.cpp
StackTest.exe: ../TestSuite/Test.$(OBJEXT) StackTest.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)StackTest.exe StackTest.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	StackTest.exe
endif

StackTest.$(OBJEXT): StackTest.cpp
SuiteExample.exe: ../TestSuite/Test.$(OBJEXT) ../TestSuite/Suite.$(OBJEXT) Date.$(OBJEXT) SuiteExample.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)SuiteExample.exe SuiteExample.$(OBJEXT) ../TestSuite/Test.$(OBJEXT) ../TestSuite/Suite.$(OBJEXT) Date.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	SuiteExample.exe
endif

SuiteExample.$(OBJEXT): SuiteExample.cpp
