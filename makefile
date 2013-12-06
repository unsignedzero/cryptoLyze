# Used to generate the libs and the executable.
# Created by David Tran (unsignedzero)

CCC=g++
CCFLAGS=-O3 -Wall -Wextra -g

LIBDIR= ./lib/

default: sboxMain.x

clean:
	rm -rvf *.a *.o *.out *.x

depend: dep

dep: libsbox.a

libsbox.a:
	$(CCC) $(CCFLAGS) -c $(LIBDIR)*.cpp
	ar rcs libsbox.a *.o

sboxMain.x: dep
	$(CCC) $(CCFLAGS) -o $@ sboxMain.cpp -I$(LIBDIR) -L. -lsbox

test: sboxMain.x
