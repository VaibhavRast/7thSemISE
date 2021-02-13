#include <stdio.h>
#include <omp.h>
#include <math.h>

void main(){
    omp_set_num_threads(8);
    int n;
    printf("Enter num");
    scanf("%d",&n);
    long fact=1,fact1=1;
    int i=1;
    #pragma omp parallel for reduction(*:fact)
    for (i = 1; i <=n; i++)
    {
        fact=fact*i;
    }
    printf("Factorial of %d: %ld \n",n,fact);

    #pragma omp parallel for firstprivate(fact1) 
    for (i = 1; i <=n; i++)
    {
        printf("Fact1 address and value for thread when assigned copy of shared variable is %d: %p, %ld \n",omp_get_thread_num(),&fact1,fact1);
        fact1=fact1*i;
        
        
    }
    printf("Factorial of %d: %ld \n",n,fact1);
}