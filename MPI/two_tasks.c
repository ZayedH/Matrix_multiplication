# include <stdio.h>
/* MPI function signature */

# include <mpi.h>

char tab[4] = {1, 2, 3, 5};

int main(int argc, char const *argv[])
{
    
    char sum = 0, s;
    int i, r;
    MPI_Status status;


    MPI_Init(&argc, &argv);  /* initialisation of MPI Library */

    MPI_Comm_rank(MPI_COMM_WORLD, &r); /* Get the rank of current task*/
    // printf("0 = %d \n", tab[0]);
    // printf("1 = %d \n", tab[1]); 
    // printf("2 = %d \n", tab[2]);
    // printf("3 = %d \n", tab[3]);

    

    int tag = 1000; /* Message tag */

    if(r==0){
        for (i = 0; i < 2; i++){
        sum  = sum + tab[i];
    }
        MPI_Send(&sum, 1, MPI_CHAR,1, tag, MPI_COMM_WORLD);
    }else{
        for (i = 2; i < 4; i++){
        sum  = sum + tab[i];
    }
        MPI_Recv(&s, 1, MPI_CHAR, 0,tag, MPI_COMM_WORLD, &status );
        printf("Sum = %d \n", s+sum);
    }

    /* Finalisation of MPI */

    MPI_Finalize();
    return 0;
}
