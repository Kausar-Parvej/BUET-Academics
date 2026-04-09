#include<stdio.h>

int main()
{
    int n,i,f,f0=0,f1=1;

    printf("Enter n:\n");
    scanf("%d",&n);

    for(i=3;i<=n;i++){
        f=f0+f1;
        f0=f1;
        f1=f;
    }

     printf("\nThe %dth fibonacci number is %d\n",n,f);

    return 0;
}
