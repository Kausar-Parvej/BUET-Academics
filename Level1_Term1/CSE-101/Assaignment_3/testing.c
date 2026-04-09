#include<stdio.h>
#include<windows.h>

void Display();

int n,a[100];

int main()
{
    int i;
    printf(" How many data you wanna input:");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("\n\tenter num%d:",i+1);
        scanf("%d",&a[i]);
    }

    printf(" The numbers are ");
    for(int i=0; i<n; i++) printf("%4d",a[i]);

    printf("enter a key...");
    getch();
    system("cls");

}
