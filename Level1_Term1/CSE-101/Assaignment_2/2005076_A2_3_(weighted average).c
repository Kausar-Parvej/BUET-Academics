#include<stdio.h>

int main()
{
    float num,weight,sum1=0.0,sum2=0.0,avg;
    int n,i;

    printf("How many number you want to input:\n");
    scanf("%d",&n);

    for(i=1; i<=n; i++)
    {
        printf("Enter number%d and it's weighted value:\n",i);
        scanf("%f %f",&num,&weight);
        sum1+=num*weight;
        sum2+=weight;
    }

    avg=sum1/sum2;
    printf("\nWeighted average of the numbers is=%g\n",avg);

    return 0;

}
