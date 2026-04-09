#include<stdio.h>
#include<math.h>

int main()
{
    unsigned int n, n1=0, n2=0,i,a,b;
    scanf("%d",&n);

    unsigned int mask1=1, mask2=2;
    printf("\n");

    for(i=0;i<16;i++)
    {
        a=n&mask1;
        a=(a!=0)?1:0;
        n1=n1+a*pow(2,i);
        mask1=mask1<<2;
        //printf("%d",a);

        b=n&mask2;
        b=(b!=0)?1:0;
        n2=n2+b*pow(2,i);
        mask2=mask2<<2;
        //printf("b=%d",b);

    }
    printf("%d",(n1>n2)?n1:n2);

    //printf("\n%d\n%d", n1,n2);

    return 0;
}
