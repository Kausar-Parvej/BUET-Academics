#include<iostream>
#include<cstring>
using namespace std;

class Vector
{
    char *name;
    int x,y,z;
public:
    Vector(char *n)
    {
        int l = strlen(n);
        name = new char[l+1];
        strcpy(name,n);
        x=0;
        y=0;
        z=0;
    }
    Vector(char *n, int a, int b, int c)
    {
        int l = strlen(n);
        name = new char[l+1];
        strcpy(name,n);
        x=a;
        y=b;
        z=c;
    }

    Vector(const Vector &ob)
    {
        int l = strlen(ob.name);
        name = new char[l+1];
        strcpy(name,ob.name);
        x=ob.x;
        y=ob.y;
        z=ob.z;
    }

    void setX(int a)
    {
        x=a;
    }

    void setY(int b)
    {
        y=b;
    }
    void setZ(int c)
    {
        z=c;
    }

    void setName(char *n)
    {
        int l = strlen(n);
        name = new char[l+1];
        strcpy(name,n);
    }

    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

    int getZ()
    {
        return z;
    }

    char *getName()
    {
        return name;
    }

    ~Vector()
    {
        delete []name;
    }

    friend ostream &operator <<(ostream &stream, Vector ob);
    Vector operator ^(Vector ob);
    bool operator ==(Vector ob);
    Vector operator *(int n);
    friend Vector operator *(int n, Vector ob);
    Vector operator *(Vector ob);
    Vector operator =(Vector ob);

};

ostream &operator <<(ostream &stream, Vector ob)
{
    //v1: 1x+2y+3z
    cout.unsetf(ios::showpos);
    stream<<ob.name<<": "<<ob.x<<"x";
    cout.setf(ios::showpos);
    stream<<ob.y<<"y"<<ob.z<<"z"<<endl;
    return stream;
}

Vector Vector:: operator ^(Vector ob)
{
    Vector temp("temp");
    temp.x=(y*ob.z)-(z*ob.y);
    temp.y=(z*ob.x)-(x*ob.z);
    temp.z=(x*ob.y)-(y*ob.x);
    return temp;
}

bool Vector:: operator ==(Vector ob)
{
    return (x==ob.x && y==ob.y && z==ob.z);
}

Vector Vector:: operator *(int n)
{
    Vector temp("temp");
    temp.x=x*n;
    temp.y=y*n;
    temp.z=z*n;
    return temp;
}

Vector operator *(int n, Vector ob)
{
   Vector temp("temp");
    temp.x=ob.x*n;
    temp.y=ob.y*n;
    temp.z=ob.z*n;
    return temp;
}

Vector Vector:: operator *(Vector ob)
{
    Vector temp("temp");
    temp.x=x*ob.x;
    temp.y=y*ob.y;
    temp.z=z*ob.z;
    return temp;
}

Vector Vector:: operator =(Vector ob)
{
    x=ob.x;
    y=ob.y;
    z=ob.z;

    return *this;
}

int main()
{
    Vector v1("v1", 1,2,3), v2("v2", 4, 5, -6), v3("Result1"),v4("Result2",-27,18,-3);

    cout << v1;     //Print the components of vector v1
    cout << v2;     //Print the components of vector v2

    v3= v1^v2;       //Calculate the cross product of vector v1 and vector v2 (Consider ^ as cross product for this assignment)
    cout << v3;     //Print the modified components of vector v3 (Name: Result1)

    if(v3==v4)      //Check for equality; if two vectors contain equal component values (x, y, z), then they are equal
        cout<<"Vectors are equal"<<endl;
    else
        cout<<"Vectors are not equal"<<endl;

    v1= v1*2;       //Multiply each component of vector v1 with the given value
    cout << v1;     //Print the modified components of vector v1

    v2= 2*v2;        //Multiply each component of vector v2 with the given value
    cout << v2;     //Print the modified components of vector v2

    v3=v1*v2;       //Multiply each component of vector v1 with the corresponding component of vector v2
    cout << v3;     //Print the modified components of vector v3 (Name: Result1)

    if(v3==v4)      //Check for equality; if two vectors contain equal component values (x, y, z), then they are equal
        cout<<"Vectors are equal"<<endl;
    else
        cout<<"Vectors are not equal"<<endl;

    return 0;
}

/* Output:
v1: 1x+2y+3z
v2: 4x+5y-6z
Result1: -27x+18y-3z
Vectors are equal
v1: 2x+4y+6z
v2: 8x+10y-12z
Result1: 16x+40y-72z
Vectors are not equal
*/
