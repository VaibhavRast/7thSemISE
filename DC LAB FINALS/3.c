#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>

int prime_table[100];
double sine_table[100];

void prime_gen(int n)//n - no of primes required
{
    int count=0,flag,i=2,j;
    while (count<n)
    {
        int flag=1;//Prime
        for ( j = 2; j <i; j++)
        {
            if((i%j)==0){
                flag=0;//Non prime
                break;
            }
        }

        if(flag){
            prime_table[count]=i;
            count++;
        }
        i++;
    }
    
}

void sine_gen(int n)
{
    for(int i=0;i<n;i++)
    {
        sine_table[i]=sin(i*M_PI/180);
    }
}

void main(){
    int n,i,j;
    printf("Enter size of table");
    scanf("%d",&n);

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            prime_gen(n);
            printf("Primes");
            for(i=0;i<n;i++)
            printf("%d \n",prime_table[i]);
        }

        #pragma omp section
        {
            printf("Sines");
            sine_gen(n);
            for(j=0;j<n;j++)
            printf("%f \n",sine_table[j]);
        }
    }

}