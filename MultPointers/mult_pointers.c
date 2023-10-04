/*******************************************************************************

*******************************************************************************/

#include <malloc.h>
#include "mult_pointers.h"

void mult( int** A, int** B, int** C,int n_rows_cols){
   //  int ** C =  (int**)malloc(n_rows_cols*sizeof(int*));
   for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
         C[i][j] = 0;
         Product: for(int k = 0; k < n_rows_cols; k++) {
            C[i][j] += A[i][k] * B[k][j];
         }
      }
   }

}

