#include <iostream>
#include <vector>

using namespace std;

const int ID = 1211311027;

void printArray(vector<int> dataset)
{
    for (int i : dataset)
    {
        printf("%d ", i);
    }
}

vector<int> generateDataset(int size)
{
    srand(ID);
    vector<int> dataset;

    for (int i = 0; i < size; i++)
    {
        dataset.push_back(rand() % size);
    }
    return dataset;
}

int main()
{
    vector<int> dataset1 = generateDataset(100);
    printArray(dataset1);
    vector<int> dataset2 = generateDataset(1000);
    vector<int> dataset3 = generateDataset(10000);
    vector<int> dataset4 = generateDataset(100000);
    vector<int> dataset5 = generateDataset(500000);

    float distance;
}
