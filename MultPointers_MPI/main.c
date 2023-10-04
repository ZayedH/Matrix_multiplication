#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

// Size of the matrix (NxN)
#define n_rows_cols 8

MPI_Status status;

// Print matrix function declaration
void printMatrix(int*);


int* A;
int* B;
int* C;

int main(int argc, char **argv)
{

    int number_of_processors; // number of processors
    int processor_rank;
    int number_of_workers;

    
    int source_processor; // Processor sending data

    int destination_processor;  // Processor to receive data

    int rows; // The number of rows for a worker processor to process

    int matrix_subset;  // The subset of a matrix to be processed by workers
    A = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    B = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
    C = malloc(sizeof(int) * n_rows_cols*n_rows_cols);

    MPI_Init(&argc, &argv);  /* initialisation of MPI Library */
        
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processors); // Determine number of processors available
    
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank); // Determine rank of process

    number_of_workers = number_of_processors - 1; // The number of workers on multiplication

    /* ---------- Manager Processor Code ---------- */
    if (processor_rank == 0)
    {
        printf("\nMultiplying a %dx%d matrix using %d processor(s).\n\n", n_rows_cols, n_rows_cols, number_of_processors);
           for(int i = 0; i <  n_rows_cols; i++) {
      for(int j = 0; j <  n_rows_cols; j++) {
            *(A+i*n_rows_cols + j)=  1;
            *(B+i*n_rows_cols + j) = 1;
      }
   }
        /* Send the matrix to the worker processes */
        rows = n_rows_cols / number_of_workers;
        matrix_subset = 0;
        for (destination_processor = 1; destination_processor <= number_of_workers; destination_processor++)
        {
            // Determine the subset of the matrix to send to the destination processor
            MPI_Send(&matrix_subset, 1, MPI_INT, destination_processor, 1, MPI_COMM_WORLD);

            // Send the number of rows to process to the destination worker processor
            MPI_Send(&rows, 1, MPI_INT, destination_processor, 1, MPI_COMM_WORLD);

            // Send rows from matrix 1 to destination worker processor
            MPI_Send(&A[matrix_subset], rows * n_rows_cols, MPI_INT, destination_processor, 1, MPI_COMM_WORLD);

            // Send entire matrix 2 to destination worker processor
            MPI_Send(&B[0], n_rows_cols * n_rows_cols, MPI_INT, destination_processor, 1, MPI_COMM_WORLD);

            // Determine the next chunk of data to send to the next processor
            matrix_subset = matrix_subset + rows;
        }
        // Retrieve results from all workers processors
        for (int i = 1; i <= number_of_workers; i++)
        {
            source_processor = i;
            MPI_Recv(&matrix_subset, 1, MPI_INT, source_processor, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source_processor, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&C[matrix_subset], rows * n_rows_cols, MPI_INT, source_processor, 2, MPI_COMM_WORLD, &status);
        }

        if (true)
        {
            printf("Matrix 1 A:\n");
            printMatrix(A);
            printf("Matrix 2 B:\n");
            printMatrix(B);
            printf("Product Matrix C = AB:\n");
            printMatrix(C);
        }


    }

    /* ---------- Worker Processor Code ---------- */
    else
    {
        source_processor = 0;
        MPI_Recv(&matrix_subset, 1, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&A[0], rows * n_rows_cols, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&B[0], n_rows_cols * n_rows_cols, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);

        /* Perform matrix multiplication */
         for (int i = 0; i < rows ; i++)
         {
         for (int j = 0; j < n_rows_cols; j++)
             {
                *(C+i*n_rows_cols+j) = 0;
             for (int k = 0; k < n_rows_cols; k++)
              {
                  *(C+i*n_rows_cols+j) +=  *(A+i*n_rows_cols+j) * *(B+j*n_rows_cols+k);
                }
            }
         }

        MPI_Send(&matrix_subset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&C[0], rows * n_rows_cols, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
    MPI_Finalize();


}

/**
 * @brief Prints the contents of an NxN matrix
 * 
 * @param matrix An NxN matrix of integers
 */
void printMatrix(int* matrix)
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
