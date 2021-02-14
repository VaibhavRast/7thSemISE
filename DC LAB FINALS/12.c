#include<mpi.h>
#include<stdlib.h>
#include<stdio.h>

//F(J)=C Find J given C and range A-B
int f(int n)//Function definition
{
    return n*n;
}

int search(int a,int b, int c, int rank, int size)
{
    int j=-1;
    for(int i=a+rank;0<=i&&i<=b;i+=size)
    {
        int fn_returnval=f(i);
        if(fn_returnval==c){
            j=i;
            break;
        }
    }
    return j;
}

void main(int argc,char *argv[])
{
    int a=1,b=100000000,c=49,j;
    int rank,size;
    double wtime;

    MPI_Init( &argc , &argv);
    MPI_Comm_rank( MPI_COMM_WORLD , &rank);
    MPI_Comm_size( MPI_COMM_WORLD , &size);

    if(rank==0)
        printf("A,B AND C %d %d %d \n",a,b,c);
    wtime=MPI_Wtime();
    j=search(a,b,c,rank,size);
    wtime=MPI_Wtime()-wtime;

    if(j!=-1)
        printf("Process %d found J with value %d and Time Taken:%f \n",rank,j,wtime);
    
    MPI_Finalize();    
}
