# include <stdio.h>
/* MPI function signature */

# include <mpi.h>

int tab[12] = {1, 2, 3, 5, 8, 9, 7, 8, 2, 1, 4, 0};

int main(int argc, char  **argv)
{
    
    int sum = 0, s;
    int i, r;
    MPI_Status status;


    MPI_Init(&argc, &argv);  /* initialisation of MPI Library */

    MPI_Comm_rank(MPI_COMM_WORLD, &r); /* Get the rank of current task*/

    for (i = 3*r; i < 3*(r+1); i++){
        sum  = sum + tab[i];
    } 
    
    int tag = 10*r; /* Message tag */

    if(r==0){

/* Process 0 receive 3 messages in any order*/
for (int p = 0; p<3; p++)
{
    MPI_Recv(&s, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status );
    printf("From = %d \n", status.MPI_SOURCE);
    sum = sum + s;
}


printf(" Total Sum = %d \n", sum);
        
    }else{
         MPI_Send(&sum, 1, MPI_INT,0, tag, MPI_COMM_WORLD);
    }
      
        
    

    /* Finalisation of MPI */

    MPI_Finalize();
    return 0;
}
