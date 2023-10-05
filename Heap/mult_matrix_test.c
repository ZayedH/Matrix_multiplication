/*******************************************************************************

*******************************************************************************/

#include "mult_matrix.h"
// #include <malloc.h>
# include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv)
{
   clock_t begin = clock();
   time_t t;
   /* Intializes random number generator */
   // srand((unsigned) time(&t));
   srand(0);

   int n_rows_cols = 1458;
   int n_size = n_rows_cols*n_rows_cols;
   int* A = malloc(n_size*sizeof(int));
   int* B = malloc(n_size*sizeof(int));
   int* C = malloc(n_size*sizeof(int));
   for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
            *(A+i*n_rows_cols + j)=  rand()% 5;
            *(B+i*n_rows_cols + j) = rand()% 5;
      }
   }

   mult( A,  B, C, n_rows_cols);
   clock_t end = clock();

            printf("A:\n");
            print_matrix(A, n_rows_cols);
            printf("B:\n");
            print_matrix(B, n_rows_cols);
            printf("Product Matrix:\n");
            print_matrix(C, n_rows_cols);

                    // Determine and print the total run time
        double runTime = (double)(end - begin) / CLOCKS_PER_SEC;
        printf("Runtime: %f seconds\n", runTime);
   }



