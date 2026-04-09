#include<stdio.h>

int main()
{
     float x,y,m;
     int i;

    printf("Enter two integers:\n");
    scanf("%f %f",&x,&y);

    m=x;

    for(i=1;i<15;i++){
        m=m/y;
        if(m==1){
            break;
        }
    }
    if(m==1){
        printf("\n%d=%d^%d\n",(int)x,(int)y,i);
    }
    else{
        printf("\n1could find natural exponent\n");

    }

    return 0;
}
