#include<stdio.h>

int main()
{
    int n,a,b,c,m;

    printf("Enter a number(more than two digit):\n");
    scanf("%d",&n);

    a=n/100;
    b=(n-a*100)/10;
    c=n-a*100-b*10;

    m=a*100+c*10+b;

    printf("\nswapping the last two digit we get:%d\n",m);

    return 0;

}
