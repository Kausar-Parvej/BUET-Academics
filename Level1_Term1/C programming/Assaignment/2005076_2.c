#include<stdio.h>

int day_count(int y,int m,int q);

int main()
{
    int year,month,day,n;

    printf("Enter year:");
    scanf("%d",&year);
    printf("Enter month(1-12):");
    scanf("%d",&month);
    printf("\n");

    printf("\nCalender for:\n\n");

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

    printf(",%d\n",year);
    printf("\n");

    printf("SUN  MON  TUE  WED  THU  FRI  SAT\n");

    if(month==3||month==5||month==7||month==8||month==10||month==12||month==1) n=31;
    else if(month==4||month==6||month==9||month==11) n=30;
    else if(month==2)
    {
        if((year%4==0&&year%100!=0)||(year%100==0&&year%400==0)) n=29;
        else n=28;
    }

    if(month==1||month==2)
    {
        month+=12;
        year=year-1;
    }

    if(day_count(year,month,1)==2) printf("     ");
    else if(day_count(year,month,1)==3) printf("          ");
    else if(day_count(year,month,1)==4) printf("               ");
    else if(day_count(year,month,1)==5) printf("                    ");
    else if(day_count(year,month,1)==6) printf("                         ");
    else if(day_count(year,month,1)==0) printf("                              ");


    for(day=1; day<=n; day++)
    {
        if(day_count(year,month,day)==1) printf("%-5d",day);
        else if(day_count(year,month,day)==2) printf("%-5d",day);
        else if(day_count(year,month,day)==3) printf("%-5d",day);
        else if(day_count(year,month,day)==4) printf("%-5d",day);
        else if(day_count(year,month,day)==5) printf("%-5d",day);
        else if(day_count(year,month,day)==6) printf("%-5d",day);
        else if(day_count(year,month,day)==0) printf("%-5d\n",day);


    }
    printf("\n");

    return 0 ;


}
int day_count(int y,int m,int q)
{
    int h=(q+(26*(m+1)/10)+y+(y/4)+6*(y/100)+(y/400))%7;
    return h;
}

