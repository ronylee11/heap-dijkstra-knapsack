#include "structs.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int knapsack(int maxWeight, const vector<Station> &stations) {
  int numOfItems = stations.size();
  int dpTable[numOfItems + 1][maxWeight + 1];

  // dynamic programming table
  for (int i = 0; i <= numOfItems; i++) {
    for (int w = 0; w <= maxWeight; w++) {
      if (i == 0 || w == 0)
        dpTable[i][w] = 0;
      else if (stations[i - 1].weight <= w)
        dpTable[i][w] = max(stations[i - 1].profit +
                                dpTable[i - 1][w - stations[i - 1].weight],
                            dpTable[i - 1][w]);
      else
        dpTable[i][w] = dpTable[i - 1][w];
    }
  }

  // display table
  for (int i = 0; i <= numOfItems; i++) { // n is 10 items
    cout << "item = " << i << "\n";
    for (int j = 0; j <= maxWeight; j++) { // W is  max weight
      cout << dpTable[i][j] << " ";
    }
    cout << "\n\n";
  }

  // find selected items
  int result = dpTable[numOfItems][maxWeight];
  int weight = maxWeight;
  vector<int> selectedStations;
  int totalWeight = 0;

  for (int i = numOfItems; i > 0 && result > 0; i--) {
    if (result == dpTable[i - 1][weight]) {
      continue;
    } else {
      // if the result is not from the top, then the item is included
      selectedStations.insert(selectedStations.begin(), i - 1);

      // since this weight is included its profit is deducted   
      result = result - stations[i - 1].profit;
      weight = weight - stations[i - 1].weight;
    }
  }

  // display all stations
  cout << "All Stations: \n";
  cout << "-------------------------------------------------\n| \t\tAll Stations\t\t\t|" << endl;
  cout << "-------------------------------------------------";
  cout << "\n|Station name   |weight\t\t|profit\t\t|\n-------------------------------------------------" << endl;
  for (int i = 0; i <= stations.size() - 1; i++) {
    cout << "|" <<  stations[i].name << "\t\t|" << stations[i].weight << "\t\t|" << stations[i].profit << "\t\t|" << endl;
  }
  cout << "-------------------------------------------------\n" << endl;



  // display selected stations
  cout << "Selected Stations for maximum profit within knapsack capacity: \n";
  cout << "-------------------------------------------------\n| \t\tChosen Stations\t\t\t|" << endl;
  cout << "-------------------------------------------------";
  cout << "\n|Station name   |weight\t\t|profit\t\t|\n-------------------------------------------------" << endl;
  for (int i = 0; i <= selectedStations.size() - 1; i++) {
    cout << "|" << stations[selectedStations[i]].name << "\t\t|" << stations[selectedStations[i]].weight << "\t\t|" << stations[selectedStations[i]].profit << "\t\t|" << endl;
  }
  cout << "-------------------------------------------------" << endl;

  // calculate total weight
  for (int i = 0; i < selectedStations.size(); i++) {
    totalWeight += stations[selectedStations[i]].weight;
  }

  // display total weight
  cout << "Total weight: " << totalWeight << "/" << maxWeight << endl;

  // display maximum profit
  cout << "Maximum Profit: " << dpTable[numOfItems][maxWeight] << endl;

  return dpTable[numOfItems][maxWeight];
}
