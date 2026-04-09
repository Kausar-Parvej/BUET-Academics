#include<stdio.h>

int main()
{
    int n,i,fact=1;       //fact er ekta value age thekei set koire deowa lagbe

    printf("Enter a positive number:\n");
    scanf("%d",&n);

    for(i=1;i<=n;i++){
        fact=fact*i;
    }

    printf("%d!=%d\n",n,fact);

    return 0;
}
