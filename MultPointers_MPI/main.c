#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mpi.h"

// Size of the matrix (NxN)
#define n_rows_cols 8

MPI_Status status;

// Print matrix function declaration
// void printMatrix(int (*)[n_rows_cols]);


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

    MPI_Init(&argc, &argv);  /* initialisation of MPI Library */
        
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_processors); // Determine number of processors available
    
    MPI_Comm_rank(MPI_COMM_WORLD, &processor_rank); // Determine rank of process

    number_of_workers = number_of_processors - 1; // The number of workers on multiplication

    /* ---------- Manager Processor Code ---------- */
    if (processor_rank == 0)
    {
        A = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
        B = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
        C = malloc(sizeof(int) * n_rows_cols*n_rows_cols);
        printf("\nMultiplying a %dx%d matrix using %d processor(s).\n\n", n_rows_cols, n_rows_cols, number_of_processors);
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
            MPI_Send(&A, rows * n_rows_cols, MPI_INT, destination_processor, 1, MPI_COMM_WORLD);

            // Send entire matrix 2 to destination worker processor
            MPI_Send(&B, n_rows_cols * n_rows_cols, MPI_INT, destination_processor, 1, MPI_COMM_WORLD);

            // Determine the next chunk of data to send to the next processor
            matrix_subset = matrix_subset + rows;
        }
        // Retrieve results from all workers processors
        for (int i = 1; i <= number_of_workers; i++)
        {
            source_processor = i;
            MPI_Recv(&matrix_subset, 1, MPI_INT, source_processor, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source_processor, 2, MPI_COMM_WORLD, &status);
            MPI_Recv(&C, rows * n_rows_cols, MPI_INT, source_processor, 2, MPI_COMM_WORLD, &status);
        }

        // print  matrix results
        // if (false)
        // {
        //     printf("Matrix 1 A:\n");
        //     printMatrix(A);
        //     printf("Matrix 2 B:\n");
        //     printMatrix(B);
        //     printf("Product Matrix C = AB:\n");
        //     printMatrix(C);
        // }


    }

    /* ---------- Worker Processor Code ---------- */
    else
    {
        // A = (int**)malloc(n_rows_cols*sizeof(int*));
        // B = (int**)malloc(n_rows_cols*sizeof(int*));
        // C = (int**)malloc(n_rows_cols*sizeof(int*));
        // for (int i =0; i< n_rows_cols; i++){
        //     A[i] = (int*)malloc(n_rows_cols*sizeof(int));
        //     B[i] = (int*)malloc(n_rows_cols*sizeof(int));
        //     C[i] = (int*)malloc(n_rows_cols*sizeof(int));
        // }
        source_processor = 0;
        MPI_Recv(&matrix_subset, 1, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&A, rows * n_rows_cols, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(&B, n_rows_cols * n_rows_cols, MPI_INT, source_processor, 1, MPI_COMM_WORLD, &status);

        /* Perform matrix multiplication */
        // for (int i = 0; i < rows ; i++)
        // {
        //     for (int j = 0; j < n_rows_cols; j++)
        //     {
        //         C[i][j] = 0;
        //         for (int k = 0; k < n_rows_cols; k++)
        //         {
        //             C[i][j] = C[i][j] + A[i][k] * B[k][j];
        //         }
        //     }
        // }

        MPI_Send(&matrix_subset, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        MPI_Send(&C, rows * n_rows_cols, MPI_INT, 0, 2, MPI_COMM_WORLD);
    }
    MPI_Finalize();


}

// /**
//  * @brief Prints the contents of an NxN matrix
//  * 
//  * @param matrix An NxN matrix of integers
//  */
// void printMatrix(int (*matrix)[n_rows_cols])
// {
//     for ( int i = 0; i < n_rows_cols; i++)
//     {
//         for (int j = 0; j < n_rows_cols; j++)
//         {
//             printf("%d\t", matrix[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }
