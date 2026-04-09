#include<stdio.h>

int main()
{
    int n=5,i,m=1,k=0;

    for(i=n;i>1;i=i-1){
        m=m*i;
        k=k+m;

        printf("factorial is %d\n",m);
    }

    printf("sum is %d\n",k);

    return 0;
}
