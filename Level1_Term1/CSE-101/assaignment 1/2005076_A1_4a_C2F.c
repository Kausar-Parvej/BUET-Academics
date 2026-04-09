#include<stdio.h>

int main()                          //converting celsius to fahrenheit:
{
    float celsius,fahrenheit;

    printf("Enter the temperature in Celsius:\n");
    scanf("%f",&celsius);

    fahrenheit=(9.0/5*celsius)+32;

    printf("\nTemperature in Fahrenheit is %.2f\n",fahrenheit);

    return 0;
}
