#include <bits/stdc++.h>
using namespace std;

void merge_array(int array[], int begin, int middle, int end);

vector<int> inverted_pair;
int counter = 0;

void divide_array(int array[], int begin, int end)
{
    if ((begin + 1) >= end)
    {
        return;
    }

    int middle = (begin + end) / 2;

    divide_array(array, begin, middle);
    divide_array(array, middle, end);
    merge_array(array, begin, middle, end);

    // return (count_and_sort(array, begin, middle) + count_and_sort(array, middle, end) + merge_array(array, begin, middle, end));
}

void merge_array(int array[], int begin, int middle, int end)
{
    // int counter = 0;
    int leftArray_size = middle - begin;
    int rightArray_size = end - middle;

    int leftArray[leftArray_size];
    int rightArray[rightArray_size];

    for (int i = 0; i < leftArray_size; i++)
        leftArray[i] = array[begin + i];
    for (int j = 0; j < rightArray_size; j++)
        rightArray[j] = array[middle + j];

    int leftCount = 0;
    int rightCount = 0;

    if (leftArray[leftArray_size - 1] - 1 == rightArray[0])
    {
        leftCount=1;
        rightCount=1;
        for(int i = leftArray_size-1; i> 0; i--){
            if(leftArray[i-1]-1 == leftArray[i]){
                leftCount++;
            }
        }
        for(int j = 0; j<rightArray_size-1; j++){
            if(rightArray[j]-1 == rightArray[j+1]){
                rightCount++;
            }
        }
        cout<<"\n"<<leftCount<<","<<rightCount<<"\n";
    }
    counter += leftCount*rightCount;
    // return counter;
}

int main()
{
    string str;
    cin >> str;

    // int number_of_invertedPair = divide_array(array, 0, n);
    // cout << number_of_invertedPair << "\n";
    int n = str.size();
    int array[n];
    for (int i = 0; i < n; i++)
    {
        int a = (int)str[i];
        array[i] = a;
        //cout<<array[i]<<" ";
    }
    cout<<"\n";

    divide_array(array, 0, n);
    cout << counter << "\n";

    return 0;
}
