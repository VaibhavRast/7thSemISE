#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define N 4

int a[N][N]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
int b[N][N]={{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
int c[N][N];

void main(int argc, char *argv[])
{
    int rank,size,i,j,k;
    
    MPI_Status status;
    MPI_Init( &argc , &argv);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);
    MPI_Comm_size( MPI_COMM_WORLD , &size);

    int nworkers;// Slave processes to 0 the master processs which divides work row wise to each process
    int rows,offset,src,dest;
    int avgrows,extra;

    if(rank==0)
    {
        //Divide Work 4 send to each slave and 3 receive statements from slave
        nworkers=size-1;
        rows=N/nworkers;
        extra=N%nworkers;
        offset=0;

        for(dest=1;dest<=nworkers;dest++)//Division of work
        {
            rows=(dest<=extra)?avgrows+1:avgrows;
            MPI_Send( &offset , 1 , MPI_INT , dest , 1 , MPI_COMM_WORLD);
            MPI_Send( &rows , 1 , MPI_INT , dest , 1 , MPI_COMM_WORLD);
            MPI_Send( &a[offset][0] , rows*N , MPI_INT , dest , 1 , MPI_COMM_WORLD);
            MPI_Send( &b , N*N , MPI_INT , dest , 1 , MPI_COMM_WORLD);
            offset+=rows;
        }

        for ( src = 1; src <=nworkers; src++)//Receiving results
        {
            MPI_Recv( &offset , 1 , MPI_INT , src , 2 , MPI_COMM_WORLD , &status);
            MPI_Recv( &rows , 1 , MPI_INT , src , 2 , MPI_COMM_WORLD , &status);
            MPI_Recv( &c[offset][0] , N*rows , MPI_INT , src , 2 , MPI_COMM_WORLD , &status);
        }

        //Print Result
        for ( i = 0; i < N; i++)
        {
            for ( j = 0; j < N; j++)
            {
                printf("%d",c[i][j]);
            }
            printf("\n");
        }

    }

    if(rank>0)
    {
        MPI_Recv( &offset , 1 , MPI_INT , 0 , 1 , MPI_COMM_WORLD,&status);
        MPI_Recv( &rows , 1 , MPI_INT , 0 , 1 , MPI_COMM_WORLD,&status);
        MPI_Recv( &a , rows*N , MPI_INT , 0 , 1 , MPI_COMM_WORLD,&status);
        MPI_Recv( &b , N*N , MPI_INT , 0 , 1 , MPI_COMM_WORLD,&status);

        //Matrix Multiplication Logic
        for ( j = 0; j < N; j++)
        {
            for ( i = 0; i < N; i++)// i<rows important
            {
                c[i][j]=0;
                for ( k = 0; k < N; k++)
                    c[i][j]+=a[i][k]*b[k][j];    
            }  
        }
        MPI_Send( &offset , 1 , MPI_INT , 0 , 2 , MPI_COMM_WORLD);
        MPI_Send( &rows , 1 , MPI_INT , 0 , 2 , MPI_COMM_WORLD);
        MPI_Send( &c[offset][0] , N*rows , MPI_INT , 0 , 2 , MPI_COMM_WORLD);

    }
    MPI_Finalize();
}
