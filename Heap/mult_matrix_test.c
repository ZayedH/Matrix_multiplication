/*******************************************************************************

*******************************************************************************/

#include "mult_matrix.h"
// #include <malloc.h>
# include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv)
{
   /* Intializes random number generator */
   time_t t;
   srand((unsigned) time(&t));

   int n_rows_cols = 5;
   int n_size = n_rows_cols*n_rows_cols;
   int* A = malloc(n_size*sizeof(int));
   int* B = malloc(n_size*sizeof(int));
   int* C = malloc(n_size*sizeof(int));
   for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
            *(A+i*n_rows_cols + j)=  0;
            *(B+i*n_rows_cols + j) = rand()% 5;
      }
   }


   printf("%d\n", &A[0]);
   printf("%d\n",&A[1]);
    printf("%d\n",&A[2]);

   mult( A,  B, C, n_rows_cols);

            printf("A:\n");
            print_matrix(A, n_rows_cols);
            printf("B:\n");
            print_matrix(B, n_rows_cols);
            printf("Product Matrix:\n");
            print_matrix(C, n_rows_cols);
   }



