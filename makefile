# Used to generate the libs and the executable.
# Created by David Tran (unsignedzero)
# Last Modified: 01-17-2014

CXX=g++
CCSPEEDFLAGS=-O3
CCDEBUGFLAGS=-Wall -Wextra
CCTESTFLAGS=-coverage -O0 -g

LIBDIR= ./lib/

default: sboxMain.x

depend: dep

dep: libsbox.a

libsbox.a:
	$(CXX) $(CCDEBUGFLAGS) $(CCSPEEDFLAGS) -c $(LIBDIR)*.cpp
	ar rcs libsbox.a *.o

sboxMain.x: dep
	$(CXX) $(CCSPEEDFLAGS) $(CCDEBUGFLAGS) -o $@ sboxMain.cpp -I$(LIBDIR) -I./data/ -L. -lsbox

test: clean
	$(CXX) $(CCDEBUGFLAGS) $(CCTESTFLAGS) -c $(LIBDIR)*.cpp
	ar rcs libsbox.a *.o
	$(CXX) $(CCDEBUGFLAGS) $(CCTESTFLAGS) -o sboxMain.x sboxMain.cpp -I$(LIBDIR) -I./data/ -L. -lsbox
	./sboxMain.x test

profile: test
	gcov */*.cpp */*.tpp */*.hpp *.cpp
	coveralls --exclude lib --exclude tests --verbose | grep 'coverage' | grep '1'

clean:
	rm -rvf *.x *.a *.o *.out *.gcda *.gcov *.gcno
	rm -rvf output*
