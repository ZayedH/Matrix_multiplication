# multiplication of the paralization matrix

In the 'c_code' folder, you will find various methods for computing matrix multiplication, including cache-friendly code, OpenMP, and OpenMPI, all aimed at optimizing execution time.

## mult_matrix.c

Contains both cache-friendly and cache-unfriendly code.

## Getting Started

### mult_matrix_test.c
For testing purposes only, without any parallelization.

### mpi_matrix_mult.c

Contains parallelization using OpenMPI.

```
mpicc -o mpi_matrix_mult  mpi_matrix_mult.c  mult_matrix.o
mpirun -np 4 ./mpi_matrix_mult 
```

### mp_matrix_mult.C
Contains parallelization using OpenMP.

```
 gcc -o  mp_matrix_mult -fopenmp mp_matrix_mult.c mult_matrix.o
```

## Others
There are some text files for collecting data to be plotted for comparison by plots.py.
