#include<stdio.h>

int square_add(int n,int a);

int main()
{
    int n,h;

    printf("Enter the number:\n");
    scanf("%d",&n);

    h=square_add(n,0);

    if(h==1)
        printf("\nYES\n");
    else
        printf("\nNO\n");

    return 0;

}
int square_add(int n, int sum)
{
    if(n==0)
    {
        if(sum>9) return square_add(sum,0);
        else if(sum==1)return 1;
        else return 0;
    }

    return square_add(n/10,n%10*n%10+sum);


}
