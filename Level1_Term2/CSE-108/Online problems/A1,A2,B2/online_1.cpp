#include<iostream>
#include<cstring>
#include<cmath>>

using namespace std;
class car;

class truck
{
    int weight;
    int speed;

public:
    truck(int w, int v)
    {
        weight=w;
        speed=v;
    }

    //friend int car::spGreater(truck &ob);
    friend class car;
};

class car
{
    int passengers;
    int speed;
    int regNo;
    char *owner;

public:
    car()
    {
        //initialization
    }
    car(int n)
    {
        passengers=n;
    }

    car(int n, int v)
    {
        passengers=n;
        speed=v;
    }
    car(int n, int v, int no, char *s);

    void enterDetail(int n, int v)
    {
        passengers=n;
        speed=v;
    }
    ~car()
    {
        delete[] owner;
    }

    void enterDetail(int n, int v, int no, char *s);

    void Reg(int no, char*s);

    void show()
    {
        cout<<"Passengers: "<<passengers<<"         "<<"Speed: "<<speed<<endl;
        cout<<"Registration# "<<regNo<<"     "<<"Owner Name: "<<owner<<endl<<endl<<endl;

    }

    int spGreater(truck &ob)
    {
        return abs(speed-ob.speed);
    }

};

car::car(int n, int v, int no, char *s)
{
    passengers=n;
    speed=v;
    regNo=no;
    owner=new char[strlen(s)+1];
    strcpy(owner,s);
}

void car::enterDetail(int n, int v, int no, char *s)
{
    passengers=n;
    speed=v;
    regNo=no;
    owner=new char[strlen(s)+1];
    strcpy(owner,s);
}

void car::Reg(int no, char*s)
{
    regNo=no;
    owner=new char[strlen(s)+1];
    strcpy(owner,s);
}


int main()
{
    car car1, car2(8), car3(6, 100), car4(10, 120, 1001, "Karim"), car5;
    truck truck1(2000, 70);
    int d;

    car4.show();
    car3.enterDetail(8, 20);
    car2.enterDetail(5,80);
    car2.Reg(1005, "Hena");
    car2.show();
    car5.enterDetail(7, 80, 1002, "John");
    car5.show();
    car1.Reg(1010, "Rita");

    cout<<"Speed Difference: "<<car3.spGreater(truck1) << "kms" <<"\n\n\n";

    return 0;
}

