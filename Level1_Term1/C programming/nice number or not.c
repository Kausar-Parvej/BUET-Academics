#include<stdio.h>

int main()                          //6,18...is nice number
{
    int n,i,count=0,sum=0;

    printf("Enter a number:\n");
    scanf("%d",&n);

    for(i=n/2;i>0;i--){
        if(n%i==0){
            sum=sum+i;
            count++;
        }
        if(count==3){
            break;
        }
    }

    if(sum==n){
        printf("\n%d is a nice number\n",n);
    }
    else{
        printf("\n%d is NOT a nice number\n",n);
    }

    return 0;
}
