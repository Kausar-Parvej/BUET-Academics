#include<stdio.h>
#include<windows.h>
#include<conio.h>

void Input();
void displa();
void sort();
void sInsert();
void usInsert();
void Append();
void sDelet();
void usDelet();
void sSearch();
void usSearch();
int sort_or_not();

int n,a[100];

int main()
{

    int k=2;
    while(k!=8)
    {
        system("cls");
        printf(" Choose-");
        printf("\n\t1 for taking input (must for first time)");
        printf("\n\t2 for display");
        printf("\n\t3 for sorting");
        printf("\n\t4 for inserting");
        printf("\n\t5 for appending");
        printf("\n\t6 for deleting");
        printf("\n\t7 for searching");
        printf("\n\t8 for exit");

        printf("\n\n Enter your choice:");
        scanf("%d",&k);

        if(k==1)Input();
        if(k==2)displa();
        else if(k==3)Sort();
        else if(k==4)
        {
            if (sort_or_not()==1) sInsert();
            else if (sort_or_not()==0) usInsert();
        }
        else if(k==5)Append();
        else if(k==6)
        {
            if (sort_or_not()==1) sDelet();
            else if (sort_or_not()==0) usDelet();
        }
        else if(k==7)
        {
            if (sort_or_not()==1) sSearch();
            else if (sort_or_not()==0) usSearch();
        }

    }

    return 0;
}
void Input()
{
    system("cls");
    int i;
    printf(" How many data you wanna input:");
    scanf("%d",&n);
    for(i=0; i<n; i++)
    {
        printf("\n\tenter num%d:",i+1);
        scanf("%d",&a[i]);
    }
    printf("\n  numbers have been inputed. press any key to continue...");
    getch();
}
void displa()
{
    system("cls");
    int i;
    printf(" The numbers are:");
    for(i=0; i<n; i++) printf("%d  ",a[i]);
    printf("\n\n  press any key to continue...");
    getch();
}
void Sort()
{
    system("cls");
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(a[i]>a[j])
            {
                int temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
    printf("\n  numbers have been sorted. press any key to continue...");
    getch();
}
void sInsert()
{
    int x,i=0,j;
    system("cls");
    printf("\nEnter a inserted number:");
    scanf("%d",&x);
    while((x>a[i])&&(i<n)) i++;
    n++;
    for(j=n-1; j>i; j--) a[j]=a[j-1];
    a[i]=x;
    printf("\n  %d has been inserted. press any key to continue...",x);
    getch();
}
void usInsert()
{
    int x;
    system("cls");
    printf("\nEnter a inserted number:");
    scanf("%d",&x);
    n++;
    a[n-1]=x;
    printf("\n  %d has been inserted. press any key to continue...",x);
    getch();
}
void Append()
{
    int x;
    system("cls");
    printf("\nEnter a number to append:");
    scanf("%d",&x);
    n++;
    a[n-1]=x;
    printf("\n  %d has been appended. press any key to continue...",x);
    getch();
}
void sDelet()
{
    int x,i=0;
    system("cls");
    printf("\nInput the deleting number:");
    scanf("%d",&x);
    while((x>a[i])&&(i<n)) i++;
    if(x==a[i])
    {
        for(; i<n-1; i++)
            a[i]=a[i+1];
        n--;
        printf("\n  %d has been deleted. press any key to continue...",x);
        getch();
    }
    else
    {
        printf("\n  %d not found. press any key to continue...",x);
        getch();
    }
}
void usDelet()
{
    int x,i=0;
    system("cls");
    printf("\nInput the deleting number:");
    scanf("%d",&x);
    while((x!=a[i])&&(i<n)) i++;
    if(x==a[i])
    {
        for(; i<n-1; i++)
            a[i]=a[i+1];
        n--;
        printf("\n  %d has been deleted. press any key to continue...",x);
        getch();
    }
    else
    {
        printf("\n  %d not found. press any key to continue...",x);
        getch();
    }
}
void sSearch()
{
    int x,i=0;
    system("cls");
    printf("\nsearch a number:");
    scanf("%d",&x);
    while((x>a[i])&&(i<n)) i++;
    if(x==a[i])
    {
        printf("\n  search found. %d is in no:%d position in the sorted list. press any key to continue...",x,i+1);
        getch();
    }
    else
    {
        printf("\n  %d not found. press any key to continue...",x);
        getch();
    }

}
void usSearch()
{
    int x,i=0;
    system("cls");
    printf("\nsearch a number:");
    scanf("%d",&x);
    while((x!=a[i])&&(i<n)) i++;
    if(x==a[i])
    {
        printf("\n  search found. %d is in no:%d position in the unsorted list. press any key to continue...",x,i+1);
        getch();
    }
    else
    {
        printf("\n  %d not found. press any key to continue...",x);
        getch();
    }

}
int sort_or_not()
{
    for(int i=0; i<n-1; i++)
    {
        if(a[i]>a[i+1]) return 0;
    }
    return 1;

}


