#include<gd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<omp.h>

void main()
{
    char *input_file="a1.png";
    char *output_file="a2.png";
    int color,r,g,b,combined,x,y;

    FILE *fp;
    if((fp=fopen(input_file,"r"))==NULL){
        printf("Error");
    }

    gdImagePtr img=gdImageCreateFromPng(fp);

    int width=gdImageSX(img);
    int height=gdImageSY(img);
    omp_set_num_threads(8);
    double t1= omp_get_wtime();
    #pragma omp parallel for private(y,color,r,g,b,combined)
    for ( x = 0; x < width; x++)
    {
        #pragma omp critical 
        {
            for ( y = 0; y < height; y++)
            {
                color=gdImageGetPixel(img,x,y);
                r=gdImageRed(img,color);
                g=gdImageGreen(img,color);
                b=gdImageBlue(img,color);
                combined=0.3*r+0.59*g+0.11*b;
                color=gdImageColorAllocate(img,combined,combined,combined);
                gdImageSetPixel(img,x,y,color);
            }
            
        }
    }
    double t2= omp_get_wtime();
    if((fp=fopen(output_file,"w"))==NULL){
        printf("Error");
    }
    gdImagePng(img,fp);
    gdImageDestroy(img);

    fclose(fp);
    printf("Time taken %lf",(t2-t1));
}