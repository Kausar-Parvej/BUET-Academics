#include<stdio.h>

int main()
{
    int n,i,m;

    printf("Enter a number to check whether it is prime or not:\n");
    scanf("%d",&n);

    for(i=2; i<=n/2; i++)
    {
        m=n%i;
        if(m==0)
            break;
    }

    if(m==0)
        printf("\n%d is not a prime number\n",n);
    else
        printf("\n%d is a prime number!\n",n);

    return 0;

}
