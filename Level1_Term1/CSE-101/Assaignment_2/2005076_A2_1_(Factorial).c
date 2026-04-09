#include<stdio.h>

int main()
{
    int n,i,fact=1;

    printf("Enter n:\n");
    scanf("%d",&n);

    for(i=1; i<=n; i++)
    {
        fact=fact*i;
    }

    printf("\n%d!=%d\n",n,fact);

    return 0;

}
