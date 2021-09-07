CC=gcc
MPICC=mpicc
CILKCC=/usr/local/OpenCilk-9.0.1-Linux/bin/clang
CFLAGS=-O3
PTHREADSFLAGS = -O3 -pthread -std=c99
# /mnt/apps/prebuilt/OpenCilk/9.0.1/build/bin/clang

default: all

main: mmio.o coo2csc.o main.c
	$(CC) $(CFLAGS) -o ../out/main mmio.c coo2csc.c main.c

main3: mmio.o coo2csc.o main3.c
	$(CC) $(CFLAGS) -o ../out/main3 mmio.c coo2csc.c main3.c

main_cilk: mmio.o coo2csc.o main_cilk.c
	$(CILKCC) -o ../out/main_cilk mmio.c coo2csc.c main_cilk.c -fcilkplus

main_mpi: mmio.o coo2csc.o main_mpi.c
	$(MPICC) -o ../out/main_mpi mmio.c coo2csc.c main_mpi.c -fcilkplus

main_mpi_cilk: mmio.o coo2csc.o main_mpi_cilk.c
	$(MPICC) -o ../out/main_mpi_cilk mmio.c coo2csc.c main_mpi_cilk.c -fcilkplus

test: mmio.o coo2csc.o test.c
	$(CC) $(PTHREADSFLAGS) -o test mmio.c coo2csc.c test.c

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: main main_cilk main_mpi_cilk main_mpi main3

.PHONY: clean
	
clean:
	rm -f main.o 