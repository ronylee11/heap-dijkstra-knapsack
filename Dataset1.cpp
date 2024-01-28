#include <iostream>
#include <vector>
#include <chrono>
#include "heapSort.cpp"
#include "mergeSort.cpp"

using namespace std;

const int ID = 1211311027;

/* Print dataset(whole)
void printArray(vector<int> dataset)
{
    for (int i : dataset)
    {
        printf("%d ", i);
    }
}
*/

// Print dataset first 50 value and last 50 value
void printArray(vector<int> dataset)
{
    int displayCount = 50;
    int n = dataset.size();

    if (n <= 100)
    {
        for (int i : dataset)
        {
            printf("%d ", i);
        }
    }
    else
    {
        // Display the first 50 elements
        for (int i = 0; i < displayCount; i++)
        {
            printf("%d ", dataset[i]);
        }

        cout << "... ";

        // Display the last 50 elements
        for (int i = n - displayCount; i < n; i++)
        {
            printf("%d ", dataset[i]);
        }
    }

    cout << "\n";
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
    int datasetSize;

    // Continue asking user to choose dataset size until a valid choice is entered
    while (true)
    {
        int choice;
        cout << "Choose dataset size:\n"
             << "Set 1: 100\n"
             << "Set 2: 1,000\n"
             << "Set 3: 10,000\n"
             << "Set 4: 100,000\n"
             << "Set 5: 500,000\n"
             << "Your Choice: ";

        // Check input
        if (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            datasetSize = 100;
            break;
        case 2:
            datasetSize = 1000;
            break;
        case 3:
            datasetSize = 10000;
            break;
        case 4:
            datasetSize = 100000;
            break;
        case 5:
            datasetSize = 500000;
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 5.\n\n";
            continue;
        }
        break;
    }

    // Generate dataset
    vector<int> dataset = generateDataset(datasetSize);
    cout << "\nOriginal dataset: ";
    printArray(dataset);

    // Heap Sort
    vector<int> heapSortDataset = dataset;
    auto heapSortStart = chrono::system_clock::now();
    heapSort(heapSortDataset);
    auto heapSortEnd = chrono::system_clock::now();
    chrono::duration<double, milli> heapSortDuration = heapSortEnd - heapSortStart;

    cout << "\nHeap Sort Result: ";
    printArray(heapSortDataset);
    cout << "Heap Sort Time: " << heapSortDuration.count() << " milliseconds" << endl;

    // Merge Sort
    vector<int> mergeSortDataset = dataset;
    auto mergeSortStart = chrono::system_clock::now();
    mergeSort(mergeSortDataset, 0, mergeSortDataset.size() - 1);
    auto mergeSortEnd = chrono::system_clock::now();
    chrono::duration<double, milli> mergeSortDuration = mergeSortEnd - mergeSortStart;

    cout << "\nMerge Sort Result: ";
    printArray(mergeSortDataset);
    cout << "Merge Sort Time: " << mergeSortDuration.count() << " milliseconds\n" << endl;

    return 0;
}
