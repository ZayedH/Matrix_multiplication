/*******************************************************************************

*******************************************************************************/

#include "mult_pointers.h"
// #include <malloc.h>
# include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv)
{
   /* Intializes random number generator */
   time_t t;
   srand((unsigned) time(&t));


   int n_rows_cols = 200;
   int** A = (int**)malloc(n_rows_cols*sizeof(int*));
   int** B = (int**)malloc(n_rows_cols*sizeof(int*));
   int** C = (int**)malloc(n_rows_cols*sizeof(int*));
   for (int i =0; i< n_rows_cols; i++){
       A[i] = (int*)malloc(n_rows_cols*sizeof(int));
       B[i] = (int*)malloc(n_rows_cols*sizeof(int));
       C[i] = (int*)malloc(n_rows_cols*sizeof(int));
   }
   for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
            A[i][j] = rand()% 5;
            B[i][j] = rand()% 5;
      }
   }

   mult( A,  B, C, n_rows_cols);

      for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {

            printf("%d ",C[i][j]);
      }
      printf("\n") ;
      }
   }



