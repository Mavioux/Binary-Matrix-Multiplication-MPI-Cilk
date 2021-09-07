../out/main ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
../out/main_cilk ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
mpirun -np 4 ../out/main_mpi ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/test1.mtx ../matrices/test2.mtx ../matrices/test3.mtx
belgium_osm.mtx
com-Youtube.mtx
dblp-2010.mtx
mycielskian13.mtx
NACA0015.mtx
Oregon-1.mtx

../out/main3 ../matrices/belgium_osm.mtx ../matrices/belgium_osm.mtx ../matrices/belgium_osm.mtx
../out/main ../matrices/Oregon-1.mtx ../matrices/Oregon-1.mtx ../matrices/Oregon-1.mtx
../out/main ../matrices/com-Youtube.mtx ../matrices/com-Youtube.mtx ../matrices/com-Youtube.mtx

mpirun -np 4 ../out/main_mpi ../matrices/belgium_osm.mtx ../matrices/belgium_osm.mtx ../matrices/belgium_osm.mtx