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

../out/main ../matrices/test.mtx 

mpirun -np 4 ../out/main_mpi ../matrices/belgium_osm.mtx ../matrices/belgium_osm.mtx ../matrices/belgium_osm.mtx

mpirun -np 1 ../out/main_mpi ../matrices/test.mtx

../out/main ../matrices/belgium_osm.mtx
../out/main ../matrices/com-Youtube.mtx
../out/main ../matrices/dblp-2010.mtx
../out/main ../matrices/mycielskian13.mtx
../out/main ../matrices/NACA0015.mtx
../out/main ../matrices/Oregon-1.mtx

../out/main_cilk ../matrices/belgium_osm.mtx
../out/main_cilk ../matrices/com-Youtube.mtx
../out/main_cilk ../matrices/dblp-2010.mtx
../out/main_cilk ../matrices/mycielskian13.mtx
../out/main_cilk ../matrices/NACA0015.mtx
../out/main_cilk ../matrices/Oregon-1.mtx

mpirun -np 2 ../out/main_mpi ../matrices/belgium_osm.mtx
mpirun -np 1 ../out/main_mpi ../matrices/com-Youtube.mtx
mpirun -np 1 ../out/main_mpi ../matrices/dblp-2010.mtx
mpirun -np 1 ../out/main_mpi ../matrices/mycielskian13.mtx
mpirun -np 1 ../out/main_mpi ../matrices/NACA0015.mtx
mpirun -np 1 ../out/main_mpi ../matrices/Oregon-1.mtx

mpirun -np 2 ../out/main_mpi_cilk ../matrices/belgium_osm.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/belgium_osm.mtx
mpirun -np 8 ../out/main_mpi_cilk ../matrices/belgium_osm.mtx
mpirun -np 16 ../out/main_mpi_cilk ../matrices/belgium_osm.mtx

mpirun -np 2 ../out/main_mpi_cilk ../matrices/com-Youtube.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/com-Youtube.mtx
mpirun -np 8 ../out/main_mpi_cilk ../matrices/com-Youtube.mtx
mpirun -np 16 ../out/main_mpi_cilk ../matrices/com-Youtube.mtx

mpirun -np 2 ../out/main_mpi_cilk ../matrices/dblp-2010.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/dblp-2010.mtx
mpirun -np 8 ../out/main_mpi_cilk ../matrices/dblp-2010.mtx
mpirun -np 16 ../out/main_mpi_cilk ../matrices/dblp-2010.mtx

mpirun -np 2 ../out/main_mpi_cilk ../matrices/mycielskian13.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/mycielskian13.mtx
mpirun -np 8 ../out/main_mpi_cilk ../matrices/mycielskian13.mtx
mpirun -np 16 ../out/main_mpi_cilk ../matrices/mycielskian13.mtx

mpirun -np 2 ../out/main_mpi_cilk ../matrices/NACA0015.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/NACA0015.mtx
mpirun -np 8 ../out/main_mpi_cilk ../matrices/NACA0015.mtx
mpirun -np 16 ../out/main_mpi_cilk ../matrices/NACA0015.mtx

mpirun -np 2 ../out/main_mpi_cilk ../matrices/Oregon-1.mtx
mpirun -np 4 ../out/main_mpi_cilk ../matrices/Oregon-1.mtx
mpirun -np 8 ../out/main_mpi_cilk ../matrices/Oregon-1.mtx
mpirun -np 16 ../out/main_mpi_cilk ../matrices/Oregon-1.mtx

| | belgium | youtube | dble  | cielskian | NACA |
|:---:|:---:|:---:|:---:|:---:|:---:|
| serial | 0.087932 | 1.763913 | 0.063627 | 0.539022 | 0.320220 |
|---|---|---|---|---|---|
|OpenCilk (2)| 0.278805  | 5.074418 | 0.192323 | 1.406947 | 0.799982 |
|OpenCilk (4)| 0.321334 | 3.352160 | 0.195200 | 0.761468 | 0.914551 |
|OpenCilk (8)| 0.352363 | 3.126018 | 0.212793 | 0.422077 | 0.908831 |
|OpenCilk (16)| 0.393207 | 2.811118 | 0.251401 | 0.245278 | 0.883939 |
|---|---|---|---|---|---|
|MPI (2)| 0.098410  | 8.536654 | 0.120479 | 2.421233 | 0.345864 |
|MPI (4)| 0.096419 | 8.422834 | 0.095763 | 2.001625 | 0.205676 |
|MPI (8)| 0.054796 | 9.406903 | 0.041331 | 1.838767 | 0.160665 |
|MPI (16)| 0.018225 | 9.525907 | 0.022670 | 1.505502 | 0.081438 |
|---|---|---|---|---|---|
|MPI-OpenCilk (2)| 0.024839  | 0.535940 | 0.030184 | 0.136520 | 0.077520 |
|MPI-OpenCilk (4)| 0.059776 | 0.793653 | 0.029060 | 0.133236 | 0.148808 |
|MPI-OpenCilk (8)| 0.073357 | 0.815906 | 0.048248 | 0.144958 | 0.110132 |
|MPI-OpenCilk (16)| 0.157198 | 1.074799 | 0.160304 | 0.262570 | 0.445075 |
