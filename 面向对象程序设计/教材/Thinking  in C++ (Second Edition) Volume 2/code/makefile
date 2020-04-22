# Master makefile for "Thinking in C++, 2nd Edition, Volume 2"
# by Bruce Eckel & Chuck Allison
# Available at http://www.BruceEckel.com
# (c)2001 MindView Inc. Copyright notice in Copyright.txt
# Compiles all the code in the book

help: 
	@echo To compile all programs from 
	@echo "Thinking in C++, 2nd Edition, Volume 2"
	@echo type one of the following commands, according to your platform:
	@echo make Borland
	@echo make g++295 \(g++ 2.95, used with Cygwin\)
	@echo make g++3
	@echo make edg
	@echo make Microsoft
	@echo make clean


$(MAKECMDGOALS): 
	$(MAKE) $(MAKECMDGOALS) -C TestSuite
	$(MAKE) $(MAKECMDGOALS) -C C01
	$(MAKE) $(MAKECMDGOALS) -C C02
	$(MAKE) $(MAKECMDGOALS) -C C03
	$(MAKE) $(MAKECMDGOALS) -C C04
	$(MAKE) $(MAKECMDGOALS) -C C05
	$(MAKE) $(MAKECMDGOALS) -C C06
	$(MAKE) $(MAKECMDGOALS) -C C07
	$(MAKE) $(MAKECMDGOALS) -C C08
	$(MAKE) $(MAKECMDGOALS) -C C09
	$(MAKE) $(MAKECMDGOALS) -C C10
	$(MAKE) $(MAKECMDGOALS) -C C11
	$(MAKE) $(MAKECMDGOALS) -C C0B
