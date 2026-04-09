#include<stdio.h>

int main()
{
    int n,x,i,m=1;

    printf("Enter two number as in pow(N,x):\n");
    scanf("%d %d",&n,&x);

    for(i=1;i<=x;i++)
    {
        m=m*n;
    }
    printf("%d^%d=%d\n",n,x,m);

    return 0;
}
