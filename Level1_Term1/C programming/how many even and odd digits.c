#include<stdio.h>

int main()
{
    int n,a,count1=0,count2=0;

    printf("Enter a number:\n");
    scanf("%d",&n);

    while(n>1){
        a=n%10;
        if(a%2==0){
            count2++;}
        else{
            count1++;}

        n=n/10;
    }

    printf("\nThe number of even digit is:%d\n",count2);
    printf("\nThe number of odd digit is:%d\n",count1);

    return 0;

}
