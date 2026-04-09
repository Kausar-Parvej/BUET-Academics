#include<stdio.h>

int pow(int f,int g);

int main()
{
    int n,x,ans;
    printf("Enter two number as in pow(N,x):\n");
    scanf("%d %d",&n,&x);

    ans=pow(n,x);
    printf("%d^%d=%d\n",n,x,ans);

    return 0;
}

int pow(int a,int b)
{
    int i,m=1;
    for(i=1; i<=b; i++)
    {
        a=m*a;
        m=a;
    }
    return a;
}
