#include <stdio.h>

int main()
{
    int arr1[20];
    int i,n;

    int *parr1=arr1;

    scanf("%d",&n);

    for(i=0;i<n;i++){
        scanf("%d",(parr1+i));
    }

    printf("array 1:");
    for(i=0;i<n;i++){
        printf("%4d",*(parr1+i));
    }
    printf("\n\n");

    printf("array 1:");
    for(i=n-1;i>=0;i--){
        printf("%4d",*(parr1+i));
    }
    return 0;
}
