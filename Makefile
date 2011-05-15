# Generic Makefile - usable on either Windows or Linux/Unix
# WRITTEN BY: Michael Main (main@colorado.edu), Sep 17, 2000
#
# This makefile is used as follows to regenerate files for the demo2 program:
#   make throttle.o   --  Regenerates throttle.o by compiling
#   make demo2.o      --  Regenerates demo2.o by compiling
#   make demo2.exe    --  Regenerates the executable demo2 file by compiling
#   make              --  Same as "make demo2.exe"
#
# Two special targets may also be used with this makefile:
#   make all          --  Regenerates all files listed above
#   make clean        --  Erases all files listed above
#
# All compilations occur with -Wall and -gstabs.
# The clean command uses rm to remove all expendable files (rm is part of
# the cs1300 compiler tools from www.cs.colorado.edu/~main/cs1300/README.html).

# This section sets the $(SUFFIX) and $RM) variables depending on whether
# the operating system is Windows or Unix.

MACHINE=$(shell uname -s)

#ifdef COMSPEC
#  SUFFIX = .exe
#  RM = del
#else
#  SUFFIX =
#  RM = rm -f
#endif

APP_NAME = mines
DEFINES = -D__$(MACHINE)__
STATE = unstable
CFLAGS = -Wall -g -c
OFLAGS = -Wall -g -o

ifeq ($(MACHINE),Darwin)
   IFLAGS =
   LFLAGS =
else ifeq ($(MACHINE),FreeBSD)
   IFLAGS =
   LFLAGS =
else
   IFLAGS =
   LFLAGS =
endif

$(APP_NAME)$(SUFFIX): dice.o main.o
	g++ $(OFLAGS) $(APP_NAME) dice.o main.o $(LFLAGS)

dice.o: src/dice.cxx
	g++ $(CFLAGS) $(DEFINES) $(IFLAGS) src/dice.cxx

main.o: src/main.cxx
	g++ $(CFLAGS) $(DEFINES) $(IFLAGS) src/main.cxx

clean:
	rm -rf $(APP_NAME)$(SUFFIX)
	rm -rf *.o

all:
	@make $(APP_NAME)


