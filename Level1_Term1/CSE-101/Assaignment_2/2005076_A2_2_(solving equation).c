#include<stdio.h>
#include<math.h>

int main()
{
    float x1=1.2,x2,d;

    while(1)
    {
        x2=sqrt((10-x1*x1*x1*x1*x1)/3);
        d=fabs(x2-x1);
        x1=(x1+x2)/2;

        if(d<=0.000001)
            break;
    }

    printf("\nThe value of x is approximately=%f\n",x2);

    return 0;
}
