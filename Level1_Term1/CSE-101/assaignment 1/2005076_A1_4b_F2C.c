#include<stdio.h>

int main()                          //converting fahrenheit to celsius:
{
    float fahrenheit,celsius;

    printf("Enter the temperature in Fahrenheit:\n");
    scanf("%f",&fahrenheit);

    celsius=5.0/9*(fahrenheit-32);

    printf("\nTemperature in  Celsius is %.2f\n",celsius);

    return 0;
}

