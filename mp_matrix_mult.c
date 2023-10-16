#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>
#include "mult_matrix.h"
// #include <stdbool.h>


int main(int argc, char **argv)
{
    double begin;
    double end;
    double runTime;
    time_t t;
        // srand((unsigned) time(&t));
    srand(0);
    int* A;
    int* B;
    int* C;
    int i, j, k, p;
    int n_rows_cols = 4;
    FILE * fptr;
    fptr = fopen("gcc_mult_omp_cache.txt","w");
    for(p= 3; p<=12; p++){

            begin = omp_get_wtime();
            n_rows_cols = n_rows_cols*2;
            A = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
            B = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
            C = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
            for(i = 0; i <  n_rows_cols; i++) {
                    for(j = 0; j <  n_rows_cols; j++) {
                        *(A+i*n_rows_cols + j)=  rand()% 5;
                        *(B+i*n_rows_cols + j) = rand()% 5;
                        *(C+i*n_rows_cols + j)= 0;
            }
        }
            #pragma omp parallel
            
                #pragma omp single
                {
                    printf("\nMultiplying two %dx%d matrices using %d thread(s).\n\n", n_rows_cols, n_rows_cols, omp_get_num_threads());
                }
                #pragma omp parallel for private(i,j,k)
            //     for(i = 0; i <  n_rows_cols; i++) {
            //         for(j = 0; j <  n_rows_cols; j++) {
            //     for(k = 0; k < n_rows_cols; k++) {
            //         *(C+i*n_rows_cols + j)+= *(A+i*n_rows_cols+k) * *(B+k*n_rows_cols+j);
            //     }
            // } 
            //     }
                for(i = 0; i <  n_rows_cols; i++) {
                    for(k = 0; k <  n_rows_cols; k++) {
                for(j = 0; j < n_rows_cols; j++) {
                    *(C+i*n_rows_cols + j)+= *(A+i*n_rows_cols+k) * *(B+k*n_rows_cols+j);
                }
            } 
                }

            end = omp_get_wtime();
            runTime = (end - begin);
            fprintf(fptr,"%d",n_rows_cols);
            fprintf(fptr,":%f\n",runTime);
            free(A);
            free(B);
            free(C);
    }
    fclose(fptr);
    // printf("Matrix A:\n");
    // print_matrix(A, n_rows_cols);
    // printf("Matrix B:\n");
    // print_matrix(B, n_rows_cols);
    // printf("Product Matrix C = AB:\n");
    // print_matrix(C, n_rows_cols);
    // // Determine and print the total run time
    // printf("Runtime: %f seconds\n", runTime);

 
}
