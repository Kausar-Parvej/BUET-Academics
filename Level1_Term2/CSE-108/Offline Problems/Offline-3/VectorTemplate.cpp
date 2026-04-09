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

    Vector(const Vector &vobject)
    {
        int l = strlen(vobject.name);
        name = new char[l+1];
        strcpy(name,vobject.name);
        x=vobject.x;
        y=vobject.y;
        z=vobject.z;
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

    friend ostream &operator <<(ostream &stream, Vector vobject);
    Vector operator ^(Vector vobject);
    bool operator ==(Vector vobject);
    Vector operator *(int n);
    friend Vector operator *(int n, Vector vobject);
    Vector operator *(Vector vobject);
    Vector operator =(Vector vobject);

};

ostream &operator <<(ostream &stream, Vector vobject)
{
    //v1: 1x+2y+3z
    cout.unsetf(ios::showpos);
    stream<<vobject.name<<": "<<vobject.x<<"x";
    cout.setf(ios::showpos);
    stream<<vobject.y<<"y"<<vobject.z<<"z"<<endl;
    return stream;
}

Vector Vector:: operator ^(Vector vobject)
{
    Vector temp_obj("temp");
    temp_obj.x=(y*vobject.z)-(z*vobject.y);
    temp_obj.y=(z*vobject.x)-(x*vobject.z);
    temp_obj.z=(x*vobject.y)-(y*vobject.x);
    return temp_obj;
}

bool Vector:: operator ==(Vector vobject)
{
    return (x==vobject.x && y==vobject.y && z==vobject.z);
}

Vector Vector:: operator *(int n)
{
    Vector temp_obj("temp");
    temp_obj.x=x*n;
    temp_obj.y=y*n;
    temp_obj.z=z*n;
    return temp_obj;
}

Vector operator *(int n, Vector vobject)
{
   Vector temp_obj("temp");
    temp_obj.x=vobject.x*n;
    temp_obj.y=vobject.y*n;
    temp_obj.z=vobject.z*n;
    return temp_obj;
}

Vector Vector:: operator *(Vector vobject)
{
    Vector temp_obj("temp");
    temp_obj.x=x*vobject.x;
    temp_obj.y=y*vobject.y;
    temp_obj.z=z*vobject.z;
    return temp_obj;
}

Vector Vector:: operator =(Vector vobject)
{
    x=vobject.x;
    y=vobject.y;
    z=vobject.z;

    return *this;
}


int main()
{
    Vector v1("v1", 1,2,3), v2("v2", 4, 5, -6), v3("Result1"),v4("Result2",-27,18,-3);

    cout << v1;     //Print the components of vector v1
    cout << v2;     //Print the components of vector v2

    v3=v1^v2;       //Calculate the cross product of vector v1 and vector v2 (Consider ^ as cross product for this assignment)
    cout << v3;     //Print the modified components of vector v3 (Name: Result1)

    if(v3==v4)      //Check for equality; if two vectors contain equal component values (x, y, z), then they are equal
        cout<<"Vectors are equal"<<endl;
    else
        cout<<"Vectors are not equal"<<endl;

    v1= v1*2;       //Multiply each component of vector v1 with the given value
    cout << v1;     //Print the modified components of vector v1

    v2=2*v2;        //Multiply each component of vector v2 with the given value
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
