#include <algorithm>
#include <iostream>
#include <vector>
#include "structs.h"

using namespace std;

// Function to perform 0/1 Knapsack
void knapsack(const vector<Station> &stations, int capacity) {
  int n = stations.size();
  vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

  // Fill the dp table
  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= capacity; ++w) {
      if (stations[i - 1].weight <= w) {
        dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - stations[i - 1].weight] +
                                         stations[i - 1].profit);
      } else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  // Find selected items
  int w = capacity;
  vector<char> selectedStations;

  for (int i = n; i > 0 && w > 0;) {
    if (dp[i][w] != dp[i - 1][w]) {
      selectedStations.push_back(stations[i - 1].name);
      w -= stations[i - 1].weight;
      --i;
    } else {
      --i;
    }
  }

  // Print the selected stations
  cout << "Selected Stations for maximum profit within knapsack capacity: ";
  for (int i = selectedStations.size() - 1; i >= 0; --i) {
    cout << selectedStations[i] << " ";
  }
  cout << endl;

  // Print the maximum profit
  cout << "Maximum Profit: " << dp[n][capacity] << endl;
}
