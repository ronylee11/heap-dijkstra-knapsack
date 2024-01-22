#include <vector>
#include <queue>

using namespace std;

void heapSort(vector<int> &dataset)
{
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    // Inserting elements into the priority queue
    for (int i : dataset)
    {
        minHeap.push(i);
    }

    // Dequeuing elements to sort the array
    for (int i = 0; i < dataset.size(); i++)
    {
        dataset[i] = minHeap.top();
        minHeap.pop();
    }
}
