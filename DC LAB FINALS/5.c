#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<omp.h>
#include<float.h>

#define K 4

int cluster[K][2]={{75,25},{25,25},{25,75},{75,75}};//Cluster centre
int cluster_count[K]={0,0,0,0};//No of points in each cluster
int num_points;//Number of datapoints in datapoints[100][2]
long datapoints[100][2];


double get_dist(int x1,int y1,int x2,int y2){
    double dx,dy;
    dx=x2-x1;
    dy=y2-y1;
    return (double)(sqrt(dx*dx+dy*dy));
}

void populate_points(){
    int i;
    #pragma omp parallel for private(i)
    for ( i = 0; i < num_points; i++)
    {
        datapoints[i][0]=rand()%100;
        datapoints[i][1]=rand()%100;
        printf("Data point {%ld,%ld} \n",datapoints[i][0],datapoints[i][1]);
    }
    
}

void classify()
{
    int i,j,cluster_index;
    double curr_dist=0,min_dist=999;

    #pragma omp parallel for private(i,j,cluster_index,curr_dist,min_dist)
    for ( i = 0; i < num_points; i++)
    {
        curr_dist=0;
        min_dist=999;
        cluster_index=-1;

        for( j=0;j<K;j++)
        {
            curr_dist=get_dist(datapoints[i][0],datapoints[i][1],cluster[j][0],cluster[j][1]);
            if(curr_dist<min_dist)
            {
                min_dist=curr_dist;
                cluster_index=j;//The cluster to which point was assigned
            }
        }//end of inner for
        printf("Datapoint {%ld,%ld} assigned to cluster %d \n",datapoints[i][0],datapoints[i][1],cluster_index);
        cluster_count[cluster_index]++;
    }
    
}

void main()
{
    omp_set_num_threads(8);

    printf("Enter Number of points");
    scanf("%d",&num_points);

    double t1,t2;

    populate_points();

    t1=omp_get_wtime();
    classify();
    t2=omp_get_wtime();

    printf("Time taken: %lf \n",(t2-t1));

    //No of points in each cluster
    for(int i=0;i<4;i++){
        printf("Cluster%d->%d \t",i,cluster_count[i]);
    }

}