/*******************************************************************************

*******************************************************************************/
#include "mult_matrix.h"
// #include <malloc.h>
# include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char **argv)
{ 
   clock_t end;
   clock_t begin;
   int n_rows_cols = 4;
   int n_size;
   double runTime;
   int* A;
   int* B;
   int* C;
   FILE *fptr;
   time_t t;
   // srand((unsigned) time(&t));
   srand(0);
   fptr = fopen("gcc_mult_cache.txt","w");
   for(int p = 3; p<=12; p++){

      begin = clock();
      /* Intializes random number generator */
      // srand((unsigned) time(&t));
      n_rows_cols = n_rows_cols*2;
      printf("\nMultiplying two %dx%d matrices. \n\n ", n_rows_cols, n_rows_cols);
      n_size = n_rows_cols*n_rows_cols;
      A = malloc(n_size*sizeof(int));
      B = malloc(n_size*sizeof(int));
      C = malloc(n_size*sizeof(int));
      for(int i = 0; i <  n_rows_cols; i++) {
         for(int j = 0; j <  n_rows_cols; j++) {
               *(A+i*n_rows_cols + j)=  rand()% 5;
               *(B+i*n_rows_cols + j) = rand()% 5;
               *(C+i*n_rows_cols + j)= 0;
         }
      }

      mult_cache_friendly( A,  B, C, n_rows_cols);
      end = clock();
      runTime = (double)(end - begin) / CLOCKS_PER_SEC;
      fprintf(fptr,"%d",n_rows_cols);
      fprintf(fptr,":%f\n",runTime);
      free(A);
      free(B);
      free(C);
   }
   fclose(fptr);

            // printf("A:\n");
            // print_matrix(A, n_rows_cols);
            // printf("B:\n");
            // print_matrix(B, n_rows_cols);
            // printf("Product Matrix:\n");
            // print_matrix(C, n_rows_cols);
            // free(A);
            // free(B);
            // free(C);

                    // Determine and print the total run time
      //   double runTime = (double)(end - begin) / CLOCKS_PER_SEC;
      //   printf("Runtime: %f seconds\n", runTime);
   }



