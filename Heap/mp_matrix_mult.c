#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include "mult_matrix.h"
// #include <stdbool.h>


int main(int argc, char **argv)
{
    clock_t begin = clock();
    time_t t;
        // srand((unsigned) time(&t));
    srand(0);
    int* A;
    int* B;
    int* C;
    int i, j, k;
    int n_rows_cols = 1458;
    A = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    B = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    C = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    for(int i = 0; i <  n_rows_cols; i++) {
            for(int j = 0; j <  n_rows_cols; j++) {
                *(A+i*n_rows_cols + j)=  rand()% 5;
                *(B+i*n_rows_cols + j) = rand()% 5;
      }
   }
    #pragma omp parallel for private(i,j,k)
    
        // int number_of_threads = omp_get_num_threads();
        // int rows = n_rows_cols/number_of_threads;
        // int rank_of_thread = omp_get_thread_num();
        // if ( rank_of_thread != number_of_threads-1){

        // for (int i = rows*rank_of_thread; i < n_rows_cols ; i++)
        //  {
        //  for (int j = 0; j < n_rows_cols; j++)
        //      {
        //         *(C+i*n_rows_cols+j) = 0;
        //      for (int k = 0; k < n_rows_cols; k++)
        //       {
        //           *(C+i*n_rows_cols+j) +=  *(A+i*n_rows_cols+k) * *(B+k*n_rows_cols+j);
        //         }
        //     }
        //  }

        // }else{
        // for (int i = rows*rank_of_thread; i < (rank_of_thread+1)*rows ; i++)
        //  {
        //  for (int j = 0; j < n_rows_cols; j++)
        //      {
        //         *(C+i*n_rows_cols+j) = 0;
        //      for (int k = 0; k < n_rows_cols; k++)
        //       {
        //           *(C+i*n_rows_cols+j) +=  *(A+i*n_rows_cols+k) * *(B+k*n_rows_cols+j);
        //         }
        //     }
        //  }
        // }
        for(i = 0; i <  n_rows_cols; i++) {
            for(j = 0; j <  n_rows_cols; j++) {
         *(C+i*n_rows_cols + j)= 0;
         for(k = 0; k < n_rows_cols; k++) {
             *(C+i*n_rows_cols + j)+= *(A+i*n_rows_cols+k) * *(B+k*n_rows_cols+j);
         }
      } 
        
    }
    clock_t end = clock();
    printf("Matrix A:\n");
    print_matrix(A, n_rows_cols);
    printf("Matrix B:\n");
    print_matrix(B, n_rows_cols);
    printf("Product Matrix C = AB:\n");
    print_matrix(C, n_rows_cols);
    // Determine and print the total run time
    double runTime = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Runtime: %f seconds\n", runTime);

 
}
