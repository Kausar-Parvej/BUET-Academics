#include <bits/stdc++.h>
#include <iostream>
#include <fstream>

#include "MyList by LinkedList.cpp"

#define input_file "input.txt"
#define output_file "output.txt"

using namespace std;

class customer
{
public:
    int arrival;
    int departure;

    customer()
    {
        arrival = 0;
        departure = 0;
    }
    customer(int t1, int t2)
    {
        arrival = t1;
        departure = t2;
    }

    void setTimer(int t1, int t2)
    {
        arrival = t1;
        departure = t2;
    }
};

bool compare_time(customer ob1, customer ob2)
{
    if (ob1.departure == ob2.departure)
        return (ob1.arrival < ob2.arrival);

    return (ob1.departure < ob2.departure);
}

int main()
{
    ifstream fin(input_file);
    ofstream fout(output_file);

    int customer_num;
    fin >> customer_num;

    customer input_pair[customer_num];
    MyLinkedList<customer> output_pair;

    int time1, time2;
    for (int i = 0; i < customer_num; i++)
    {
        fin >> time1 >> time2;
        input_pair[i].setTimer(time1, time2);
    }

    //sort(input_pair, input_pair + customer_num, compare_time);

    for(int i=0; i<customer_num-1; i++){
        for(int j=i+1; j<customer_num; j++){
            if(input_pair[i].departure > input_pair[j].departure){
                int temp1=input_pair[i].arrival;
                int temp2=input_pair[i].departure;
                input_pair[i].setTimer(input_pair[j].arrival,input_pair[j].departure);
                input_pair[j].setTimer(temp1,temp2);
            }
            else if (input_pair[i].departure == input_pair[j].departure)
            {
                if (input_pair[i].arrival > input_pair[j].arrival)
                {
                    int temp1 = input_pair[i].arrival;
                    int temp2 = input_pair[i].departure;
                    input_pair[i].setTimer(input_pair[j].arrival, input_pair[j].departure);
                    input_pair[j].setTimer(temp1, temp2);
                }
            }
        }
    }

    output_pair.pushBack(input_pair[0]);
    for (int i = 1; i < customer_num; i++)
    {
        output_pair.setToEnd();
        if (output_pair.getValue().departure <= input_pair[i].arrival)
        {
            output_pair.pushBack(input_pair[i]);
        }
    }

    fout << output_pair.size() << "\n";
    output_pair.setToBegin();
    for (int i = 0; i < output_pair.size(); i++)
    {
        fout << output_pair.getValue().arrival << " " << output_pair.getValue().departure << "\n";
        output_pair.next();
    }

    fin.close();
    fout.close();

    cout << endl
         << "\t------>Check output.txt<------" << endl;

    return 0;
}
