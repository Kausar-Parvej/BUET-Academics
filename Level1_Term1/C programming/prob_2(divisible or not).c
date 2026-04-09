#include<stdio.h>

int main()
{
    int x,y;

    printf("Enter two integers:\n");
    scanf("%d %d",&x,&y);

    if(x%y==0){
        printf("\n%d is divisible by %d\n",x,y);
    }
    else{
        printf("\n%d is not divisible by %d\n",x,y);
    }

    return 0;
}
