/*******************************************************************************

*******************************************************************************/
#include "mult_matrix.h"
# include <stdio.h>

void mult( int* A, int* B, int* C, int n_rows_cols){

   for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
         *(C+i*n_rows_cols + j)= 0;
         Product: for(int k = 0; k < n_rows_cols; k++) {
             *(C+i*n_rows_cols + j)+= (*(A+i*n_rows_cols + k)) * (*(B+i*n_rows_cols + j));
         }
      }
   }

}
void print_matrix(int* matrix, int n_rows_cols)
{
    for (int i = 0; i < n_rows_cols; i++)
    {
        for (int j = 0; j < n_rows_cols; j++)
        {
            printf("%d\t", *(matrix+i*n_rows_cols + j));
        }
        printf("\n");
    }
    printf("\n");
}

