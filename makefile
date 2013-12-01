CCC=g++
CCFLAGS=-O3 -Wall -Wextra

DEPFILENAME= sboxLib

.SUFFIXES: .cpp

default: sboxMain.x

sboxMain.x: dep
	$(CCC) $(CCFLAGS) -o $@ sboxMain.cpp

dep: libsbox.a

libsbox.a:
	$(CCC) $(CCFLAGS) -c printStl.cpp sboxSupportLib.cpp sboxWrapperLib.cpp
	ar rcs $@ printStl.o sboxSupportLib.o sboxWrapperLib.o

clean:
	rm -rvf *.a *.o *.out *.x
