#include<stdio.h>
#include<string.h>

int main()
{
    char s1[100],ch;
    int k,i,count=0;

    scanf("%d",&k);

    scanf("%s",s1);

    for(i = 0; s1[i] != '\0'; ++i)
    {
        ch = s1[i];
        if(ch >= 'A' && ch <= 'Z')
        {
            ch = ch - k;
            if(ch < 'A')
            {
                ch = ch + 'Z' - 'A' + 1;
            }
            s1[i] = ch;
        }
        else if(ch >= 'a' && ch <= 'z')
        {
            s1[i] = ' ';
            count++;
        }
    }

    printf("decrypted message: %s\n", s1);
    return 0;
}




