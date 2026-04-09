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

    //return (count_and_sort(array, begin, middle) + count_and_sort(array, middle, end) + merge_array(array, begin, middle, end));
}

void merge_array(int array[], int begin, int middle, int end)
{
    //int counter = 0;
    int leftArray_size = middle - begin;
    int rightArray_size = end - middle;

    int leftArray[leftArray_size];
    int rightArray[rightArray_size];

    for (int i = 0; i < leftArray_size; i++)
        leftArray[i] = array[begin + i];
    for (int j = 0; j < rightArray_size; j++)
        rightArray[j] = array[middle + j];

    for (int left = 0, right = 0; left < leftArray_size || right < rightArray_size;)
    {
        if (right >= rightArray_size)
        {
            array[begin] = leftArray[left];
            begin++;
            left++;
        }
        else if (left >= leftArray_size)
        {
            array[begin] = rightArray[right];
            begin++;
            right++;
        }
        else if (leftArray[left] > rightArray[right])
        {
            array[begin] = rightArray[right];
            begin++;
            right++;
            counter += leftArray_size - left;
            for (int i = 0; i < leftArray_size - left; i++)
            {
                inverted_pair.push_back(leftArray[left+i]);
                inverted_pair.push_back(rightArray[right - 1]);
            }
        }
        else
        {
            array[begin] = leftArray[left];
            begin++;
            left++;
        }
    }
    //return counter;
}

int main()
{
    int n;
    cin >> n;

    int array[n];
    for (int i = 0; i < n; i++)
    {
        cin >> array[i];
    }

    //int number_of_invertedPair = divide_array(array, 0, n);
    //cout << number_of_invertedPair << "\n";

    divide_array(array, 0, n);
    cout<<counter<<"\n";
   
    cout << "The inverted pairs are: ";
    for (int i = 0; i < inverted_pair.size(); i += 2)
    {
        cout << "(" << inverted_pair[i] << "," << inverted_pair[i + 1] << ")";
        if((i+2) != inverted_pair.size())
            cout<<", ";
    }
    cout << "\n";

    // sorted Array
    /*for(int i=0; i<n; i++){
        cout<<array[i]<<" ";
    }*/

    return 0;
}
