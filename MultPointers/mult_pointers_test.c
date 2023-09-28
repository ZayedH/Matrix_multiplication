/*******************************************************************************

*******************************************************************************/

#include "mult_pointers.h"
// #include <malloc.h>
# include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
   int n_rows_cols = 5;
   int** A = (int**)malloc(n_rows_cols*sizeof(int*));
   int** B = (int**)malloc(n_rows_cols*sizeof(int*));
   for (int i =0; i< n_rows_cols; i++){
       A[i] = (int*)malloc(n_rows_cols*sizeof(int));
       B[i] = (int*)malloc(n_rows_cols*sizeof(int));
   }
   for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
            A[i][j] = rand()% 100;
            B[i][j] = rand()% 100;
      }
   }

   int** C = mult( A,  B, n_rows_cols);

      for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {

            printf("%d ",C[i][j]);
      }
      printf("\n") ;
      }
   }



