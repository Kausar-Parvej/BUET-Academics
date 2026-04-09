#include<stdio.h>
#define pi 3.141592654                 //volume of a sphere:

int main(){
    float radius,volume;

    printf("Enter the radius:\n");
    scanf("%f",&radius);

    volume=4.0/3*pi*radius*radius*radius;

    printf("volume of the sphere is %.4f\n",volume);

    return 0;

}
