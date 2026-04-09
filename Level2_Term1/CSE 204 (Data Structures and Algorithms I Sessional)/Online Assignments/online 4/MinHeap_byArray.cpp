#include <bits/stdc++.h>

using namespace std;

template <class data_type>
class minHeap
{
private:
    data_type *heap;
    int maxSize;
    int heap_size;

    bool isLeaf(int position)
    {
        return (position >= heap_size / 2) && (position < heap_size);
    }

    int leftchild(int position)
    {
        return 2 * position + 1;
    }

    int rightchild(int position)
    {
        return 2 * position + 2;
    }

    int parent(int position)
    {
        return (position - 1) / 2;
    }

    void rearrange_minHeap(int pos)
    {
        int lc = leftchild(pos);
        int rc = rightchild(pos);
        int set_pos = pos;
        if (lc < heap_size && heap[lc] < heap[pos])
            set_pos = lc;
        if (rc < heap_size && heap[rc] < heap[set_pos])
            set_pos = rc;
        if (set_pos != pos)
        {
            data_type temp = heap[pos];
            heap[pos] = heap[set_pos];
            heap[set_pos] = temp;

            rearrange_minHeap(set_pos);
        }
    }

    int find(data_type item)
    {
        int index = -1;
        for (int i = 0; i < heap_size; i++)
        {
            if (heap[i] == item)
            {
                index = i;
                break;
            }
        }
        return index;
    }

public:
    minHeap(int capacity = 20)
    {
        maxSize = capacity;
        heap_size = 0;
        heap = new data_type[maxSize];
    }
    ~minHeap()
    {
        delete[] heap;
    }

    void Insert(data_type key)
    {
        if (heap_size >= maxSize)
        {
            data_type temp[heap_size];
            for (int i = 0; i < heap_size; i++)
            {
                temp[i] = heap[i];
            }
            delete[] heap;
            heap = new data_type[2 * heap_size];
            for (int i = 0; i <= heap_size; i++)
            {
                heap[i] = temp[i];
            }
            maxSize = 2 * maxSize;
        }

        int pos = heap_size;
        heap[pos] = key;

        while ((pos != 0) && (heap[pos] < heap[parent(pos)]))
        {
            data_type temp = heap[pos];
            heap[pos] = heap[parent(pos)];
            heap[parent(pos)] = temp;

            pos = parent(pos);
        }

        heap_size++;
    }

    data_type FindMin()
    {
        if (heap_size <= 0)
            return -1;

        return heap[0];
    }

    data_type ExtractMin()
    {
        if (heap_size <= 0)
            return -1;

        if (heap_size == 1)
        {
            heap_size--;
            return heap[0];
        }

        int temp = heap[0];
        heap[0] = heap[heap_size - 1];
        heap_size--;
        rearrange_minHeap(0);

        return temp;
    }

    void DecreaseKey(data_type prevKey, data_type newKey)
    {
        int position = find(prevKey);
        if (position == -1)
            return;
        heap[position] = newKey;

        while (position != 0 && heap[parent(position)] > heap[position])
        {
            data_type temp = heap[position];
            heap[position] = heap[parent(position)];
            heap[parent(position)] = temp;

            position = parent(position);
        }
    }

    string Print()
    {
        string print("Printing the binary heap �\n");
        print.append("- - - - - - - - - - - - - - - - - - - -\n");

        if (heap_size == 0)
        {
            print.append("Empty Heap\n");
            print.append("- - - - - - - - - - - - - - - - - - - -\n");
            return print;
        }

        int temp1 = heap_size;
        int level = 0;
        int index = 0;
        while (temp1 != 0)
        {
            temp1 = temp1 / 2;
            level++;
        }
        for (int i = 0; i < level; i++)
        {
            print.append("Level ");
            print.append(to_string(i));
            print.append(": ");
            for (int j = 0; j < pow(2, i); j++)
            {
                print.append(to_string(heap[index]));
                print.append(" ");
                index++;
                if (index >= heap_size)
                    break;
            }
            print.append("\n");
            if (index >= heap_size)
                break;
        }
        print.append("- - - - - - - - - - - - - - - - - - - -\n");
        return print;
    }
};

//--------------------------online-------------------------------------//

void heapify(int given_array[], int n, int i)
{
    int index = i;
    int left_child = 2 * i + 1;
    int right_child = 2 * i + 2;

    if (left_child < n && given_array[left_child] < given_array[index])
        index = left_child;

    if (right_child < n && given_array[right_child] < given_array[index])
        index = right_child;

    if (index != i)
    {
        int temp = given_array[i];
        given_array[i] = given_array[index];
        given_array[index] = temp;

        heapify(given_array, n, index);
    }
}

void buildHeap(int given_array[], int n)
{
    int m = (n / 2) + 1;

    for (int i = m; i >= 0; i--)
    {
        heapify(given_array, n, i);
    }
}

string Print(int given_array[], int n)
    {
        string print("Printing the binary heap ...\n");
        print.append("- - - - - - - - - - - - - - - - - - - -\n");

        if (n == 0)
        {
            print.append("Empty Heap\n");
            print.append("- - - - - - - - - - - - - - - - - - - -\n");
            return print;
        }

        int temp1 = n;
        int level = 0;
        int index = 0;
        while (temp1 != 0)
        {
            temp1 = temp1 / 2;
            level++;
        }
        for (int i = 0; i < level; i++)
        {
            print.append("Level ");
            print.append(to_string(i));
            print.append(": ");
            for (int j = 0; j < pow(2, i); j++)
            {
                print.append(to_string(given_array[index]));
                print.append(" ");
                index++;
                if (index >= n)
                    break;
            }
            print.append("\n");
            if (index >= n)
                break;
        }
        print.append("- - - - - - - - - - - - - - - - - - - -\n");
        return print;
    }

int main()
{
    int array[] = {4,10,8,30,2,3,6,70,25,1};


    int n = 10;

    buildHeap(array, n);
    cout<<Print(array, n);

    return 0;
}
