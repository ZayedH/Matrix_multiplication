# include <stdio.h>
/* MPI function signature */

# include <mpi.h>

int main(int argc, char const *argv[])
{
    /* initialisation of MPI */
    int N, me;


    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &N);
    MPI_Comm_rank(MPI_COMM_WORLD, &me);

    printf("My rank is %d out of %d \n", me, N);

    /* Finalisation of MPI */

    MPI_Finalize();
    return 0;
}
