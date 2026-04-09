#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "utils.h"

int row,col;
int max_color;
char name[3];
Color **image;


void read_PPM()
{
    FILE *fp1;
    fp1=fopen("DennisRitchie.ppm","r");

    fscanf(fp1,"%s %d %d %d",name, &col, &row, &max_color) ;

    image=(Color**) malloc(row*sizeof(Color*));
    for(size_t i=0; i<row; i++)
    {
        image[i]=(Color*) malloc(col*sizeof(Color));
    }

    if(!feof(fp1))
    {
        for(int i=0; i<row; i++)
        {
            for(int j=0; j<col; j++)
            {
                fscanf(fp1,"%d %d %d", &image[i][j].R, &image[i][j].G, &image[i][j].B );
            }
        }

    }
    fclose(fp1);

}

void write_PPM()
{
    FILE *fp2;
    fp2=fopen("hidden_msg.ppm","w");

    fprintf(fp2,"%s \n%d %d \n%d\n",name, col, row, max_color);

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            fprintf(fp2,"%4d%4d%4d  ", image[i][j].R, image[i][j].G, image[i][j].B );
        }
        fprintf(fp2,"\n");
    }

    fclose(fp2);

}

void free_image()
{
    for(size_t i=0; i<row; i++)
    {
        free(image[i]);
    }
    free(image);
}


void evaluate_one_pixel()
{
    int mask=1;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(((image[i][j].B) & mask)==1)
            {
                image[i][j].R=255;
                image[i][j].G=255;
                image[i][j].B=255;
            }
            if(((image[i][j].B) & mask)==0)
            {
                image[i][j].R=0;
                image[i][j].G=0;
                image[i][j].B=0;
            }

        }

    }
}

int main()
{
    read_PPM();
    evaluate_one_pixel();
    write_PPM();
    free_image();

    printf("\n\tSuccessfully deciphered the image...\n\t  OPEN 'hidden_msg.ppm' FILE TO GET THE MESSAGE.\n\n ");

    return 0;
}


