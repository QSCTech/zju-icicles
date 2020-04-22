# From "Thinking in C++, 2nd Edition, Volume 2" 
# by Bruce Eckel & Chuck Allison
# Available at http://www.BruceEckel.com
# (c)2001 MindView Inc. Copyright notice in Copyright.txt
# Automatically-generated MAKEFILE 
# For examples in directory .\C10
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
	MultipleInheritance1.exe \
	MultipleInheritance2.exe \
	MultipleInheritance3.exe \
	MultipleInheritance4.exe \
	Overhead.exe \
	Mithis.exe \
	Persist1.exe \
	Persist2.exe \
	Vendor.$(OBJEXT) \
	Paste.exe

Microsoft:  \
	MultipleInheritance1.exe \
	MultipleInheritance2.exe \
	MultipleInheritance3.exe \
	MultipleInheritance4.exe \
	Overhead.exe \
	Mithis.exe \
	Persist1.exe \
	Persist2.exe \
	Vendor.$(OBJEXT) \
	Paste.exe

g++295:  \
	MultipleInheritance1.exe \
	MultipleInheritance2.exe \
	MultipleInheritance3.exe \
	MultipleInheritance4.exe \
	Overhead.exe \
	Mithis.exe \
	Persist1.exe \
	Persist2.exe \
	Vendor.$(OBJEXT) \
	Paste.exe

g++3:  \
	MultipleInheritance1.exe \
	MultipleInheritance2.exe \
	MultipleInheritance3.exe \
	MultipleInheritance4.exe \
	Overhead.exe \
	Mithis.exe \
	Persist2.exe \
	Vendor.$(OBJEXT) \
	Paste.exe

edg:  \
	MultipleInheritance1.exe \
	MultipleInheritance2.exe \
	MultipleInheritance3.exe \
	MultipleInheritance4.exe \
	Overhead.exe \
	Mithis.exe \
	Persist1.exe \
	Persist2.exe \
	Vendor.$(OBJEXT) \
	Paste.exe

clean:
ifeq ($(notdir $(SHELL)),COMMAND.COM)
	del *.obj
	del *.exe
	del *.tds
	del *.o
else
	rm -f *.o *.obj *.exe *.tds
endif


MultipleInheritance1.exe: ../TestSuite/Test.$(OBJEXT) MultipleInheritance1.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)MultipleInheritance1.exe MultipleInheritance1.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	MultipleInheritance1.exe
endif

MultipleInheritance1.$(OBJEXT): MultipleInheritance1.cpp
MultipleInheritance2.exe: ../TestSuite/Test.$(OBJEXT) MultipleInheritance2.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)MultipleInheritance2.exe MultipleInheritance2.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	MultipleInheritance2.exe
endif

MultipleInheritance2.$(OBJEXT): MultipleInheritance2.cpp
MultipleInheritance3.exe: ../TestSuite/Test.$(OBJEXT) MultipleInheritance3.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)MultipleInheritance3.exe MultipleInheritance3.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	MultipleInheritance3.exe
endif

MultipleInheritance3.$(OBJEXT): MultipleInheritance3.cpp
MultipleInheritance4.exe: ../TestSuite/Test.$(OBJEXT) MultipleInheritance4.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)MultipleInheritance4.exe MultipleInheritance4.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	MultipleInheritance4.exe
endif

MultipleInheritance4.$(OBJEXT): MultipleInheritance4.cpp
Overhead.exe: ../TestSuite/Test.$(OBJEXT) Overhead.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)Overhead.exe Overhead.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	Overhead.exe
endif

Overhead.$(OBJEXT): Overhead.cpp
Mithis.exe: ../TestSuite/Test.$(OBJEXT) Mithis.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)Mithis.exe Mithis.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	Mithis.exe
endif

Mithis.$(OBJEXT): Mithis.cpp
Persist1.exe: ../TestSuite/Test.$(OBJEXT) Persist1.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)Persist1.exe Persist1.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	Persist1.exe
endif

Persist1.$(OBJEXT): Persist1.cpp
Persist2.exe: ../TestSuite/Test.$(OBJEXT) Persist2.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)Persist2.exe Persist2.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	Persist2.exe
endif

Persist2.$(OBJEXT): Persist2.cpp
Vendor.$(OBJEXT): Vendor.cpp

Paste.exe: Vendor.$(OBJEXT) ../TestSuite/Test.$(OBJEXT) Paste.$(OBJEXT)
	$(CPP) $(CPPFLAGS) $(EXEFLAG)Paste.exe Paste.$(OBJEXT) Vendor.$(OBJEXT) ../TestSuite/Test.$(OBJEXT)
ifneq ($(MAKECMDGOALS),Microsoft)
	Paste.exe
endif

Paste.$(OBJEXT): Paste.cpp
