#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void merge(int a[],int s,int e){
    int temp[100];
    int mid=(s+e)/2;
    int i=s,j=mid+1,k=s;

    while(i<=mid && j<=e){
        if(a[i]<=a[j])
        {
            temp[k++]=a[i++];
        }
        else
        {
          temp[k++]=a[j++];  
        }
    }
    while(i<=mid){
        temp[k++]=a[i++];
    }
    while(j<=e){
        temp[k++]=a[j++];
    }

    for(i=s;i<=e;i++){
        a[i]=temp[i];
    }
}

void mergesort(int a[],int s,int e) // s-Start index e- ending index
{
    omp_set_num_threads(8);
int mid=0;
if(s<e){
    int mid=(s+e)/2;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            mergesort(a,s,mid);
            printf("Process handling left recursion is %d \n",omp_get_thread_num());
        }
        #pragma omp section
        {
            mergesort(a,mid+1,e);
            printf("Process handling right recursion is %d \n",omp_get_thread_num());
        }
    }
    merge(a,s,e);
}
}

void main(){
    int n,i=0;
    printf("Enter num of elemets");
    scanf("%d",&n);
    int a[n];
    for(i=0;i<n;i++){
        a[i]=rand()%100;
    }
    printf("Array before sorting");
    for ( i = 0; i < n; i++)
    {
        printf("%d \n",a[i]);
    }
    mergesort(a,0,n-1);
    //Calc time taken
    printf("Array after sorting");
    for ( i = 0; i < n; i++)
    {
        printf("%d \n",a[i]);
    }
}
