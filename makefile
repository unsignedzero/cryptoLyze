CCC=g++
CCFLAGS=-O3 -Wall -Wextra

.SUFFIXES: .cpp

LIBDIR= ./lib/

default: sboxMain.x

sboxMain.x: dep
	$(CCC) $(CCFLAGS) -o $@ sboxMain.cpp -I./lib -L. -lsbox

blah:
	$(CCC) $(CCFLAGS) -o $@ sboxMain.cpp -I./lib -L. *.o

dep: libsbox.a

libsbox.a:
	$(CCC) $(CCFLAGS) -c ./lib/sboxWrapperLib.cpp
	ar rcs libsbox.a sboxWrapperLib.o

clean:
	rm -rvf *.a *.o *.out *.x
