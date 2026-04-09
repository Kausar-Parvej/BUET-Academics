#include<stdio.h>

int main()
{
    char st[50];
    scanf("%s",st);
    int a=strln(st);
    printf("%d",a);

}
int strln(char* ch)
{
   int ctr = 0;
   while (*ch != '\0')
   {
      ctr++;
      ch++;
   }
   return ctr;
}

