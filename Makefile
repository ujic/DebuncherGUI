
#
# WARNING : g++ and root-system are requiered to compile this example
#


#
# If pkg-config isn't installed on your system, comment the following lines and
# set the fasterac flags as indicated with your own paths:
#
# FASTERAC_CFLAGS = -I/usr/include
# FASTERAC_LIBS   = -L/usr/lib -lfasterac
#
FASTERAC_CFLAGS = $(shell pkg-config  --cflags libfasterac)
FASTERAC_LIBS   = $(shell pkg-config  --libs   libfasterac)
#
# rootcling -f debunchDict.cc -c include/debuncher_GUI2.hh debuncherLinkDef.h - to build a dictionary
ROOT_CFLAGS     = $(shell root-config --cflags)
ROOT_LIBS       = $(shell root-config --libs)

CC        = g++

CXXFLAGS      =  -O -g -Wall -fPIC
CFLAGS    = ${FASTERAC_CFLAGS} ${ROOT_CFLAGS}
LIBS      = ${FASTERAC_LIBS}   ${ROOT_LIBS} -lGui

SRCEXE    = $(shell ls *.cxx)
#EXE       = $(SRCEXE:.C=)
ALL=debuncher_GUI2

all : $(ALL)

debuncher_GUI2 : debuncher_GUI2.cxx debunchDict.cxx
	${CC} -o $@ $@.cxx debunchDict.cxx ${CFLAGS} ${LIBS}

clean :
	rm -f *.o
	rm -f $(ALL)


