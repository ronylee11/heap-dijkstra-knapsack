#include <vector>

using namespace std;

void merge(vector<int> &dataset, int left, int middle, int right)
{
    // Calculate sizes of two subarrays to be merged
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary vectors to store the left and right subarrays
    vector<int> leftArray(n1);
    vector<int> rightArray(n2);

    // Copy data to temporary vectors leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++)
        leftArray[i] = dataset[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = dataset[middle + 1 + j];

    // Merge the two subarrays back into the original array dataset[]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        // Compare elements of leftArray and rightArray, and merge them in sorted order
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

    // Copy the remaining elements of leftArray[], if any
    while (i < n1)
    {
        dataset[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < n2)
    {
        dataset[k] = rightArray[j];
        j++;
        k++;
    }
}

// Merge Sort function: Recursively sorts the subarrays
void mergeSort(vector<int> &dataset, int left, int right)
{
    // Check if there are more than one element in the subarray
    if (left < right)
    {
        // Find the middle point of the array
        int middle = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(dataset, left, middle);
        mergeSort(dataset, middle + 1, right);

        // Merge the sorted halves
        merge(dataset, left, middle, right);
    }
}
