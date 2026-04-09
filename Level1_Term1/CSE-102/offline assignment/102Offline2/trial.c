#include<stdio.h>

int main()
{
    int **p=0;
    int r=2,c=3;

    p=(int**) malloc(sizeof(int*)*r);
    for(size_t i =0; i<r; i++)
        *(p+i)=(int*) malloc(sizeof(int)*c);

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            scanf("%d", *(p+i)+j);
        }
    }

    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            printf("%d ",p[i][j]);//p[i][j]=*(*(p+i)+j)
        }
        printf("\n");
    }

    for(int i=0; i<r; i++)
    {
        free(p[i]);
    }
    free(p);

    return 0;

}
