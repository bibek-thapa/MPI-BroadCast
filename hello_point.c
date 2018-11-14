#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <mpi.h>

#define MASTER  0
#define TAG     0
#define MSGSIZE 4000000



#define MAX 25

int main(int argc, char* argv[])
{
    int my_rank, source, num_nodes;
    char my_host[MAX];
    char message[MSGSIZE];
    double t1, t2;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);
    MPI_Barrier(MPI_COMM_WORLD);
    t1=MPI_Wtime();

    if (my_rank != MASTER) {
        gethostname (my_host, MAX);
        sprintf(message, "Hello All, I am broadcasting to %s",my_host);
        MPI_Send(message, strlen(message) + 1, MPI_CHAR, MASTER, TAG, MPI_COMM_WORLD);
    }
    else {
        gethostname (my_host, MAX);
        // printf ("Num_nodes: %d\n", num_nodes);
        // printf ("Hello from Master (process %d) on host %s!\n", my_rank, my_host);
        for (source = 1; source < num_nodes; source++) {
            MPI_Recv(message, MSGSIZE, MPI_CHAR, source, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            // printf("%s\n", message);
        }
    }
    MPI_Barrier(MPI_COMM_WORLD);
    t2=MPI_Wtime();
     printf("%lf\n",t2-t1);


 
    MPI_Finalize();
   
   
    return 0;
}
