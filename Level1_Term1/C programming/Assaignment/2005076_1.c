#include<stdio.h>

int day_count(int y,int m,int q);

int main()
{
    int year,month,day,h;

    printf("Enter year:");
    scanf("%d",&year);
    printf("Enter month(1-12):");
    scanf("%d",&month);
    printf("Enter day:");
    scanf("%d",&day);

    printf("\n");
    if(month==1) printf("JANUARY");
    else if(month==2) printf("FEBRUARY");
    else if(month==3) printf("MARCH");
    else if(month==4) printf("APRIL");
    else if(month==5) printf("MAY");
    else if(month==6) printf("JUNE");
    else if(month==7) printf("JULY");
    else if(month==8) printf("AUGUST");
    else if(month==9) printf("SEPTEMBER");
    else if(month==10) printf("OCTOBER");
    else if(month==11) printf("NOVEMBER");
    else if(month==12) printf("DECEMBER");

    printf(" %d,%d is ",day,year);

    if(month==1||month==2)
    {
        month+=12;
        year=year-1;
    }

    h=day_count(year,month,day);

    if(h==0) printf("SATURDAY");
    else if(h==1) printf("SUNDAY");
    else if(h==2) printf("MONDAY");
    else if(h==3) printf("TUESDAY");
    else if(h==4) printf("WEDNESDAY");
    else if(h==5) printf("THURSDAY");
    else if(h==6) printf("FRIDAY");
    printf("\n");

    return 0;

}
int day_count(int y,int m,int q)
{
    int h=(q+(26*(m+1)/10)+y+(y/4)+6*(y/100)+(y/400))%7;
    return h;
}
