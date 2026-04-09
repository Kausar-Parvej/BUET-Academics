#include <iostream>
using namespace std;

class Distance
{
private:
    int feet, inches;
public:
    Distance()
    {
        feet = 0;
        inches = 0;
    }
    Distance(int ft, int in)
    {
        feet = ft;
        inches = in;
    }
    friend ostream &operator<<(ostream &output, Distance &D);
    friend istream &operator>>(istream &input,  Distance &D);
	// your code
};

// your code

ostream &operator<<( ostream &output, Distance &D )
{
    output << "Feet: " << D.feet << " Inches: " << D.inches << endl;
    return output;
}

istream &operator>>( istream  &input, Distance &D )
{
    cout << "Enter feet and inches: ";
    input >> D.feet >> D.inches;
    return input;
}


int main()
{
    Distance d1, d2, d3, d4, d5, d6;
    cin >> d1;          // take input for feet and inches of d1
    cin >> d2;          // take input for feet and inches of d2
    cout << d1;         // output feet and inches of d1
    cout << d2;         // output feet and inches of d2
    d3 = d1 + d2;       // d3 is the sum of d1 and d2
    cout << d3;         // output feet and inches of d3
    d4 = d1 + d2 + d3;  // d4 is the sum of d1, d2, and d3
    cout << d4;         // output feet and inches of d4
    d5 = d1 + 3;        // d5 is d1 plus 3 inches
    cout << d5;         // output feet and inches of d5
    d6 = 4 + d1;        // d6 is d1 plus 4 feet
    cout << d6;         // output feet and inches of d6
    if(d1 < d2)         // compare d1 and d2
        cout << "d1 is less than d2" << endl;
    else
        cout << "d1 is greater than (or equal to) d2" << endl;
    d1+=d2;             // d1 is d1 plus d2
    cout << d1;         // output feet and inches of d1
    return 0;
}

/* sample output
Enter feet and inches: 12 5
Enter feet and inches: 11 6
Feet: 12 Inches: 5
Feet: 11 Inches: 6
Feet: 23 Inches: 11
Feet: 47 Inches: 10
Feet: 12 Inches: 8
Feet: 16 Inches: 5
d1 is greater than (or equal to) d2
*/
