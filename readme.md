../out/main ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
../out/main_cilk ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
mpirun -np 1 ../out/main_mpi ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
mpirun -np 1 ../out/main_mpi_cilk ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx