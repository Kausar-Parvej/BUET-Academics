#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "utils.h"

int row,col;
int max_color;
char name[3];
Color **image;

int main()
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

    FILE *fp2;
    fp2=fopen("secret_msg2.ppm","w");

    fprintf(fp2,"%s \n%d %d \n%d\n",name, col, row, max_color);

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            if(((image[i][j].B) & 1)==1)
            {
                image[i][j].R=255;
                image[i][j].G=0;
                image[i][j].B=0;
            }
            else
            {
                int random=rand();

                image[i][j].R=random%255;
                image[i][j].G=random%255;
                image[i][j].B=random%255;
            }

            fprintf(fp2,"%4d%4d%4d  ", image[i][j].R, image[i][j].G, image[i][j].B );

        }
        fprintf(fp2,"\n");
    }

    fclose(fp2);

    for(size_t i=0; i<row; i++)
    {
        free(image[i]);
    }
    free(image);

    printf("\n\tCheck 'secret_msg2.ppm'\n\n ");

    return 0;

}
