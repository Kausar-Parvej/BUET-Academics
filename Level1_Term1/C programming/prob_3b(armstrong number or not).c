#include<stdio.h>

int main()
{
    int n,a,b,c,m;
    int i=1;

    printf("Enter a three digit number:\n");
    scanf("%d",&n);

    a=n/100;
    b=(n-a*100)/10;
    c=n-a*100-b*10;

    m=a*a*a+b*b*b+c*c*c;

    if(m==n){
        printf("\n%d is a armstrong number\n",n);
    }
    else{
        printf("\n%d is NOT a armstrong number\n",n);
    }

    return 0;
}
