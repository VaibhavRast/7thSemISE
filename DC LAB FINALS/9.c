#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>

#define SEED 12345678
#define N 100000

void main(int argc,char *argv[])
{
    int rank,size;
    double x,y,z;
    double count=0,final_value=0;

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);
    MPI_Comm_size( MPI_COMM_WORLD , &size);

    srand(SEED+rank);
   
    for (int i = 0; i < N; i++)
        {
            x=(double)rand()/RAND_MAX;
            y=(double)rand()/RAND_MAX;
            z=x*x+y*y;

            if(z<=1)
                count+=1;
        }
  

    MPI_Reduce( &count , &final_value , 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD);

    if(rank==0)
    {
        printf("Value of pi is %lf",(final_value/N)*4/size);
    }
    

    MPI_Finalize();

}