#include<stdio.h>
#define pi 3.141592654              //area of the surface-area of a cylinder:

int main(){
    float radius,height,area;

    printf("Enter the radius of the cylinder's cross-section:\n");
    scanf("%f",&radius);

    printf("Now enter the height of the cylinder:\n");
    scanf("%f",&height);

    area=2*pi*radius*(radius+height);

    printf("\nsurface area of the cylinder is %.4f\n",area);

    return 0;
}
