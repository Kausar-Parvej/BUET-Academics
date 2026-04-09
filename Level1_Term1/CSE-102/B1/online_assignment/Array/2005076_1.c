#include<stdio.h>

int main()
{
    int n,m,temp,i,j,k,a[50],b[50],c[50];

    printf("\n\tEnter number of element for arr1:");
    scanf("%d",&n);
    printf("Enter array element:\n" );
    for(i=0; i<n; i++)
        scanf("%d",&a[i]);


    printf("\n\tEnter number of element for arr2:");
    scanf("%d",&m);
    printf("Enter array element:\n" );
    for(i=0; i<m; i++)
        scanf("%d",&b[i]);


    for(i=0; i<n; i++)
    {
        c[i]=a[i];
    }
    for(i=0; i<m; i++)
    {
        c[n+i]=b[i];
    }
    for(int i=0; i<(n+m-1); i++)
    {
        for(int j=i+1; j<(m+n); j++)
        {
            if(c[i]>c[j])
            {
                int temp=c[i];
                c[i]=c[j];
                c[j]=temp;
            }
        }
    }

    k=n+m;

    for(i=0; i<m+n-1; i++)
    {
        if(c[i]=c[i+1])
        {
            for(j=i; j<k-1; j++)
                c[j]=c[j+1];
            k--;
        }
    }


    printf("OUTPUT:\n");
    for(i=0; i<k; i++)
    {
        printf("%4d",c[i]);
    }
    return 0;
}
