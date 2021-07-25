CC=gcc
MPICC=mpicc
CILKCC=/usr/local/OpenCilk-9.0.1-Linux/bin/clang
CFLAGS=-O3
PTHREADSFLAGS = -O3 -pthread -std=c99
# /mnt/apps/prebuilt/OpenCilk/9.0.1/build/bin/clang

default: all

main: mmio.o coo2csc.o main.o
	$(CC) $(CFLAGS) -o ../out/main mmio.c coo2csc.c main.c

test: mmio.o coo2csc.o test.c
	$(CC) $(PTHREADSFLAGS) -o test mmio.c coo2csc.c test.c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: main 

.PHONY: clean
	
clean:
	rm -f main.o 