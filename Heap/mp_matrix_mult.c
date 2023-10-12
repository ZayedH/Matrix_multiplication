#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include "mult_matrix.h"
// #include <stdbool.h>


int main(int argc, char **argv)
{
    double begin = omp_get_wtime();
    time_t t;
        // srand((unsigned) time(&t));
    srand(0);
    int* A;
    int* B;
    int* C;
    int i, j, k;
    int n_rows_cols = 1024;
    A = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    B = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    C = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    for(int i = 0; i <  n_rows_cols; i++) {
            for(int j = 0; j <  n_rows_cols; j++) {
                *(A+i*n_rows_cols + j)=  rand()% 5;
                *(B+i*n_rows_cols + j) = rand()% 5;
      }
   }
    #pragma omp parallel
    
        #pragma omp single
        {
            printf("\nMultiplying two %dx%d matrices using %d thread(s).\n\n", n_rows_cols, n_rows_cols, omp_get_num_threads());
        }
        #pragma omp parallel for private(i,j,k)
        for(i = 0; i <  n_rows_cols; i++) {
            for(j = 0; j <  n_rows_cols; j++) {
         *(C+i*n_rows_cols + j)= 0;
         for(k = 0; k < n_rows_cols; k++) {
             *(C+i*n_rows_cols + j)+= *(A+i*n_rows_cols+k) * *(B+k*n_rows_cols+j);
         }
      } 
        }

    double end = omp_get_wtime();
    printf("Matrix A:\n");
    print_matrix(A, n_rows_cols);
    printf("Matrix B:\n");
    print_matrix(B, n_rows_cols);
    printf("Product Matrix C = AB:\n");
    print_matrix(C, n_rows_cols);
    // Determine and print the total run time
    double runTime = (end - begin);
    printf("Runtime: %f seconds\n", runTime);

 
}
