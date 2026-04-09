#include<stdio.h>

int main()
{
    int row,column,a=1,i,space;

    printf("Enter how many row you want in pascal's triangle:\n");
    scanf("%d",&row);

    for(i=1; i<=row; i++)
    {
        for(space=i; space<=(row-1); space++)
        {
            printf("  ");
        }
        for(column=1; column<=i; column++)
        {
            if(column==1 || column==i)
                a=1;
            else
                a=a*(i-column+1)/(column-1);        //t(r+1)/t(r)=(n-r+1)/r
            printf("%4d",a);
        }
        printf("\n");
    }

    return 0;

}
