#include<stdio.h>

int main()
{
    FILE *fp;
    char ch;
    int n;

    fp=fopen("toy.ppm","r");
    fscanf(fp,"%c",&ch);
    fscanf(fp,"%c",&ch);
    fscanf(fp,"%c",&ch);

    while(!feof(fp))
    {
        fscanf(fp,"%d",&n);
        printf("%d ",n);
    }
    fclose(fp);
    getch();

    return 0;
}
