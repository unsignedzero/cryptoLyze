CC=g++
CFLAGS=-O3 -Wall -Wextra

default: sboxMain.x

sboxMain.x:
	$(CC) $(CFLAGS) -o $@ sboxMain.cpp

clean:
	rm -rvf *.x *.o *.out
