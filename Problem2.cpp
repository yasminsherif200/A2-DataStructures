#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
struct Patient
{
    int id;
    string name;
    int severity;
    int arrivalTime;
};
vector<Patient> heap;

// compare priority
bool hasHighPriority(Patient a, Patient b)
{

    if (a.severity > b.severity)
        return true;

    if (a.severity == b.severity &&
        a.arrivalTime < b.arrivalTime)
        return true;

    return false;
}

// helper functions for index calculations

int parentIndex(int i)
{
    return (i - 1) / 2;
}

int leftChildIndex(int i)
{
    return 2 * i + 1;
}

int rightChildIndex(int i)
{
    return 2 * i + 2;
}

// heapify up
void heapifyUp(int index)
{

    while (index > 0)
    {

        int parent = parentIndex(index);

        if (hasHighPriority(heap[index], heap[parent]))
        {

            swap(heap[index], heap[parent]);

            index = parent;
        }
        else
        {
            break;
        }
    }
}