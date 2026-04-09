#include<stdio.h>

int main()
{
    int n,m;
    int i=1;

    printf("Enter a positive number:\n");
    scanf("%d",&n);

    m=n;

    for(;;i++){
        m=m/10;
        if(m<1){
            break;
        }
    }
    printf("\n%d is consists of:%d digits\n",n,i);

    return 0;
}
