#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

void main(int argc , char *argv[])
{
    int rank,size,i,j;
    double a[100],b[100];
    double mysum=0;//Intermediate results
    double globalsum=0;// Final result on reduce

    MPI_Init( &argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0)
        printf("Starting dot product with %d tasks",size);
    
    for(i=0;i<100;i++){
        a[i]=1;
        b[i]=a[i];
    }

    for (j=0;j<100;j++)
    {
        mysum+=a[j]*b[j];
    }

    printf("Task %d partial sum is %lf",rank,mysum);

    MPI_Reduce( &mysum , &globalsum, 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD);

    if(rank==0)
        printf("Completed Process: Global Sum is %lf",globalsum);
    
    MPI_Finalize();
}