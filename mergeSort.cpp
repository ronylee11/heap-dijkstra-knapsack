#include <vector>

using namespace std;

void merge(vector<int> &dataset, int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    for (int i = 0; i < n1; i++)
        leftArray[i] = dataset[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = dataset[middle + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (leftArray[i] <= rightArray[j])
        {
            dataset[k] = leftArray[i];
            i++;
        }
        else
        {
            dataset[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        dataset[k] = leftArray[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        dataset[k] = rightArray[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &dataset, int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        mergeSort(dataset, left, middle);
        mergeSort(dataset, middle + 1, right);

        merge(dataset, left, middle, right);
    }
}
