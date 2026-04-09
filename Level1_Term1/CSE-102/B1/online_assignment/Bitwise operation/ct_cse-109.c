#include<stdio.h>
#include<string.h>

int main()
{
   char s[50],s2[50];
   scanf("%[^\n]",s);
   printf("%s\n",s);

   //reverse
   int len=strlen(s);

   for(int i=0;i<=len;i++)
   {
       s2[i]=s[len-i];
   }
   s2[i+1]='\0';
   printf("%s",s2);

    return 0;
}
