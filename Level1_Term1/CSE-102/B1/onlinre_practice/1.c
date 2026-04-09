#include<stdio.h>

void swap(int*,int*);

int main()
{
    int a=30,b=44;

    swap(&a,&b);

    printf("a=%d b=%d\n",a,b);

    return 0;
}
void swap(int*x,int*y)
{
    int temp;
    temp=*x;
    *x=*y;
    *y=temp;


    return;
}
