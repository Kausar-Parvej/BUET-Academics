#include<stdio.h>
#include<windows.h>
#include<conio.h>

int n,a[1000];

int main()
{
    int i,t;

    for(i=0; i<1000; i++)
        a[i]=-1;

    printf("\n  First enter some values to create the tree (press 0 and enter to complete the process):");
    while(1)
    {
        scanf("%d",&t);
        input(t,1);
        if(t==0) break;
    }
    printf("\n  tree has been created. press any key to continue...");
    getch();
    system("cls");

    int k=0,x;
    while(k!=6)
    {
        system("cls");
        printf(" Choose-");
        printf("\n\t1. Insert a new value");
        printf("\n\t2. Display the height of a node");
        printf("\n\t3. Display the listing of the values");
        printf("\n\t4. Delete an element");
        printf("\n\t5. Display the maximum height of the tree");
        printf("\n\t6. Exit");

        printf("\n\n Enter your choice:");
        scanf("%d",&k);

        if(k==1)insert();
        else if(k==2)
        {
            system("cls");
            printf("\n  Enter a node to get it's height:");
            scanf("%d",&x);
            node_height(x,1);
        }
        else if(k==3)display();
    }
    return 0;

}
void input(int x, int i)
{
    if(a[i]==-1) a[i]=x;
    else
    {
        if(x<a[i]) input(x,2*i);
        else if(x>=a[i]) input(x,2*i+1);
    }
}
void insert()
{
    int x;
    system("cls");
    printf("\n  Enter a number to insert:");
    scanf("%d",&x);
    input(x,1);
    printf("\n  %d has been inserted. press any key to continue...",x);
    getch();
}
void node_height(int x, int i)
{
    int count=0;
    if(a[1]==-1) {printf("\n  First create a tree. press any key to continue...");getch();}
    else
    {
        if(x<a[i])
        {
            count++;
            node_height(x,2*i);
        }
        else if(x>a[i])
        {
            count++;
            node_height(x,2*i+1);
        }
    }
    if (x==a[i])  {printf("\n  The height of the node is%d. press any key to continue...",count); getch();}
}
void display()
{
    int k;
    system("cls");
    printf("\n  choose-");
    printf("\n\t1. In-order traversals:");
    printf("\n\t2. pre-order traversals:");
    printf("\n\t3. post-order traversals:");
    printf("\n  enter your choice..");
    scanf("%d",&k);
    if(k==1)
    {
        system("cls");
        printf("\n  Listing of the values(in-order traversals):");
        inorder(a[1],1);
    }
    if(k==2)
    {
        system("cls");
        printf("\n  Listing of the values(pre-order traversals):");
        preorder(a[1],1);
    }
    if(k==3)
    {
        system("cls");
        printf("\n  Listing of the values(post-order traversals):");
        postorder(a[1],1);
    }
    printf("\n  press any key to continue...");
    getch();
}
void inorder(int i)
{
    if(a[2*i]==-1)
    {
        printf("  %d",a[i]);
        if(a[2*i+1]!=-1) inorder(2*i+1);
        else
    }
    else inorder(2*i);
}
void preorder(int x, int i)
{
    if(a[i]==-1) return;
    printf("  %d",a[i]);
    if(a[2*i]==-1) preorder(x,2*i+1);
    else preorder(x,2*i);
}
void postorder(int x, int i)
{
    if(a[i]==-1) return;
    if(a[2*i]==-1) preorder(x,2*i+1);
    if(a[2*i]!=-1) preorder(x,2*i);
}

