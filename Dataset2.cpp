#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "structs.h"
#include "dijkstra.cpp"
#include "kruskal.cpp"
#include "dynamicProgramming.cpp"

using namespace std;

const double ID1 = 1211306086;
const double ID2 = 1211307001;

int calculateDistance(const Station &s1, const Station &s2)
{
  return sqrt(pow(s1.x - s2.x, 2) + pow(s1.y - s2.y, 2) + pow(s1.z - s2.z, 2));
}

vector<char> generateRandomStationName()
{
  vector<char> stationNames;
  for (char c = 'A'; c <= 'T'; ++c)
  {
    stationNames.push_back(c);
  }

  for (int i = stationNames.size() - 1; i > 0; --i)
  {
    int j = rand() % (i + 1);
    swap(stationNames[i], stationNames[j]);
  }

  return stationNames;
}

void updateRoute(Station &fromStation, Station &toStation)
{
  Route route;
  route.from = fromStation.name;
  route.to = toStation.name;
  route.distance = calculateDistance(fromStation, toStation);
  fromStation.routes.push_back(route);
}

bool ifValidRoute(const Station &station1, const Station &station2)
{
  if (station1.name == station2.name)
  {
    return false;
  }

  for (const auto &route : station1.routes)
  {
    if (route.to == station2.name)
    {
      return false;
    }
  }

  return true;
}

void generateRoute(int oriRow, int oriCol, vector<vector<Station>> &stations, int &totalGeneratedRoutes)
{
  Station station1 = stations[oriRow][oriCol];
  Station station2;
  int newRow = oriRow, newCol = oriCol;

  int direction = rand() % 6;

  switch (direction)
  {
  case 0: // left
    newCol = max(0, oriCol - 1);
    break;
  case 1: // right
    newCol = min(3, oriCol + 1);
    break;
  case 2: // up
    newRow = max(0, oriRow - (rand() % 3));
    break;
  case 3: // down
    newRow = min(4, oriRow + (rand() % 3));
    break;
  case 4: // right up OR left up
    if (oriRow == 1 || oriRow == 3)
    {
      newCol = min(3, oriCol + 1);
      newRow = max(0, oriRow - 1);
    }
    else
    {
      newCol = max(0, oriCol - 1);
      newRow = max(0, oriRow - 1);
    }
    break;
  case 5: // right down OR left down
    if (oriRow == 1 || oriRow == 3)
    {
      newCol = min(3, oriCol + 1);
      newRow = min(4, oriRow + 1);
    }
    else
    {
      newCol = max(0, oriCol - 1);
      newRow = min(4, oriRow + 1);
    }
    break;
  }

  station2 = stations[newRow][newCol];

  if (ifValidRoute(station1, station2))
  {
    updateRoute(station1, station2);
    stations[oriRow][oriCol] = station1;

    // reverse
    updateRoute(station2, station1);
    stations[newRow][newCol] = station2;
    totalGeneratedRoutes++;
  }
}

void generateData(vector<vector<Station>> &stations)
{
  srand(ID1 + ID2);

  // randomise station names
  vector<char> stationNames = generateRandomStationName();

  // generate 20 stations, from A to T
  int rows = 5;
  int cols = 4;
  int k = 0;
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      stations[i][j].name = stationNames[k++];
      stations[i][j].x = rand() % 80 + 1;
      stations[i][j].y = rand() % 80 + 1;
      stations[i][j].z = rand() % 80 + 1;
      stations[i][j].weight = rand() % 160;
      stations[i][j].profit = rand() % 160;
    }
  }

  // generate routes
  int totalGeneratedRoutes = 0;

  // target 1: ensure each station connects to at least 3 other stations
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      while (stations[i][j].routes.size() < 3)
      {
        generateRoute(i, j, stations, totalGeneratedRoutes);
      }
    }
  }

  // target 2: ensure there is 54 routes
  while (totalGeneratedRoutes < 54)
  {
    int i = rand() % rows;
    int j = rand() % cols;
    generateRoute(i, j, stations, totalGeneratedRoutes);
  }
}

vector<vector<int>> generateAdjacencyMatrix(const vector<Station> &stations)
{ // weighted, and (un?)directed graph
  // Initialize the adjacency matrix with 0s
  vector<vector<int>> adjacencyMatrix(stations.size(), vector<int>(stations.size(), 0));

  for (Station station : stations)
  {
    // For each route
    for (const Route &route : station.routes)
    {
      // Find the indices of the 'from' and 'to' stations
      int fromIndex = route.from - 'A';
      int toIndex = route.to - 'A';

      // generate route with weight
      adjacencyMatrix[fromIndex][toIndex] = route.distance;
    }
  }
  return adjacencyMatrix;
}

void printToGraph(vector<Station> stations) {
  for (const auto &station : stations) {
      for (const Route &route : station.routes) {
          cout << route.from << " " << route.to << " " << endl;
      }
      cout << endl;
  }
}

void printArray(vector<Station> stations)
{
  // print stations
  for (const auto &station : stations)
  {
    cout << "Station " << station.name << " " << station.x << " " << station.y
         << " " << station.z << " " << station.weight << " " << station.profit
         << endl;

    // print routes
    for (const Route &route : station.routes)
    {
      cout << route.from << " -> " << route.to
           << ", Distance: " << route.distance << endl;
    }

    cout << endl;
  }
  //printToGraph(stations);
}

void printAdjacencyMatrix(vector<vector<int>> adjacencyMatrix)
{
  //  add column number
  printf("     ");
  for (int x = 0; x < adjacencyMatrix[0].size(); x++)
  {
    printf("%3c ", (x + 'A'));
  }
  printf(" \n");
  for (int i = 0; i < adjacencyMatrix.size(); i++)
  {
    printf("%3c [ ", (i + 'A')); // add row number
    for (const auto &cell : adjacencyMatrix[i])
    {
      printf("%3d ", cell);
    }
    printf("]");
    cout << endl;
  }
}

bool stationComparator(const Station &a, const Station &b)
{
  return a.name < b.name;
}

int main()
{
  vector<vector<Station>> stations2D(5, vector<Station>(4));
  generateData(stations2D);

  // turn the 2D vector to 1D to rearrange the alphabets for neat printing
  vector<Station> stations1D;
  for (const auto &stationCol : stations2D)
  {
    stations1D.insert(stations1D.end(), stationCol.begin(), stationCol.end());
  }
  sort(stations1D.begin(), stations1D.end(), stationComparator);

  vector<vector<int>> adjacencyMatrix = generateAdjacencyMatrix(stations1D);
  printArray(stations1D);
  printAdjacencyMatrix(adjacencyMatrix);

  cout << "\nChoose an algorithm" << endl;
  cout << "1. Shortest Paths" << endl;
  cout << "2. Minimum Spanning Tree" << endl;
  cout << "3. Dynamic Programming" << endl;
  cout << "> ";
  int option;
  cin >> option;
  cout << endl;

  if (option == 1) {
    dijkstra(adjacencyMatrix, 0);
  }
  else if (option == 2) {
    kruskal(stations1D);
  }
  else if (option == 3) {
      // Set capacity to 800kg
      int knapsackCapacity = 800;

      // Call knapsack function
      auto knapsackStart = chrono::system_clock::now();
      knapsack(knapsackCapacity, stations1D);
      auto knapsackEnd = chrono::system_clock::now();
      chrono::duration<double, milli> knapsackDuration = knapsackEnd - knapsackStart;
      cout << "Knapsack duration: " << knapsackDuration.count() << "ms" << endl;
  } else {
      cout << "Invalid option, only numbers 1-3 are allowed!" << endl;
  }
}
