#include<stdio.h>

int main()
{
    int arr[10][10];
    int i,j,n,m;

    printf("row and column\n");
    scanf("%d %d",&n,&m);
    for(i=0; i<n; i++)
        for(j=0; j<m; j++)
            scanf("%d", &arr[i][j]);
    int **parr=arr;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("%d ", *(*(parr + i) + j));
        }

        printf("\n");
    }
    return 0;

}
