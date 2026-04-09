#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "utils.h"

Image *img;
int row,col;
int max_color;
char name[3];


Image *read_PPM(char *filename)
{
    /* opens a PPM file, constructs an Image object and returns a pointer to it.
    Use fopen(), fscanf(), fprintf(), and fclose().*/

    FILE *fp;
    fp=fopen(filename,"r");

    fscanf(fp,"%s %d %d %d",name, &row, &col, &max_color) ;

    img->image=(Color**) malloc(img->rows*sizeof(Color*));
    for(size_t i=0; i<img->rows; i++)
    {
        img->image[i]=(Color*) malloc(sizeof(Color)*img->cols);
    }

    while(!feof(fp))
    {
        for(int i=0; i<img->rows; i++)
        {
            for(int j=0; j<img->cols; j++)
            {
                fscanf(fp,"%d %d %d", &img->image[i][j].R, &img->image[i][j].G, &img->image[i][j].B );
                printf("%d %d %d",img->image[i][j].R, img->image[i][j].G, img->image[i][j].B);
            }
        }

    }
    fclose(fp);


}

void write_PPM(Image *image, char *filename)
{
    /* takes an Image object and writes to filename in PPM format.*/

}

void free_image(Image *imag)
{
    /* takes an Image object and frees all the memory associated with it.
    This involves not only calling free on image but also on the appropriate
    members of it.
    */
    for(size_t i=0; i<row; i++)
    {
        free(imag->image[i]);
    }
    free(imag->image);
}


Color *evaluate_one_pixel(Image *image, int row, int col)
{
    /* Takes an Image object and returns what color the pixel at the given row/col
    should be in the secret image. This function should not change image*/

}

Image *get_secret_image(Image *image)
{
    /* takes an Image object, and constructs the secret image from it by extracting
    the LSB of the B channel. You should call evaluate_one_pixel() here. */
}

int main()
{
    /* Call read_PPM(), write_PPM(), free_image(), get_secret_image() in some order
    to obtain the hidden message.*/
    //
    read_PPM("toy.ppm");
    //write_PPM();
    free_image(img);
    return 0;
}


