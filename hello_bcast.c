#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define MASTER  0
#define TAG     0
#define MSGSIZE 4000000
#define MAX 25

int main(int argc, char** argv) {
        int my_rank, source, num_nodes;
    	char my_host[MAX];
    	char message[MSGSIZE];
		

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_nodes);


    printf("[%d]: Before Bcast, buf is %s\n", my_rank, message);

       	
    if(my_rank==0){
    gethostname (my_host, MAX);
    sprintf(message, "Hello from process %d on host %s!", my_rank, my_host);
     }
     

	double total_time=0.0;
	


	MPI_Barrier(MPI_COMM_WORLD);
	total_time-=MPI_Wtime();
        /* everyone calls bcast, data is taken from root and ends up in everyone's buf */
    MPI_Bcast(message,MSGSIZE, MPI_CHAR, MASTER, MPI_COMM_WORLD);

	MPI_Barrier(MPI_COMM_WORLD);
	total_time+=MPI_Wtime();	
	
	
	
	
 	printf("%lf \n",total_time);
	


	MPI_Finalize();
        return 0;


}