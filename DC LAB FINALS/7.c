#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>
#define buffersize 32 
// Communication between process.

void main(int argc, char *argv[])
{
    int rank;// Stores process id
    int size;// No of processes in commuincator
    char msg[buffersize]="Hello";

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank); 
    MPI_Comm_size( MPI_COMM_WORLD , &size);
    MPI_Status status;

    if(rank==3)// Process 3 (root) will send a message to all the other process in the communicator
    {
        for(int pid=0;pid<size;pid++)
        {
            if(pid!=3)
            MPI_Send( msg , buffersize , MPI_CHAR , pid , 0 , MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv( msg , buffersize , MPI_CHAR , 3 , 0 , MPI_COMM_WORLD , &status);
        printf("Message: %s from process %d to process %d \n",msg,3,rank);
    }
    MPI_Finalize();    

}