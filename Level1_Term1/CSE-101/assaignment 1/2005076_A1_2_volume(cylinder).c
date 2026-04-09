#include<stdio.h>
#define pi 3.141592654                 //volume of a cylinder:

int main(){
    float radius,height,volume;

    printf("Enter the radius of the cylinder's cross-section:\n");
    scanf("%f",&radius);

    printf("Now enter the height of the cylinder:\n");
    scanf("%f",&height);

    volume=pi*radius*radius*height;

    printf("\nVolume of the cylinder is %.4f\n",volume);

    return 0;
}
