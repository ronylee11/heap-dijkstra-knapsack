#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

const double ID1 = 1211306086;
const double ID2 = 1211307001;

struct Route {
  char from, to;
  int distance;
};

struct Station {
  char name;
  int x, y, z;
  int weight, profit;
  vector<Route> routes;
};

int calculateDistance(const Station &s1, const Station &s2) {
  return sqrt(pow(s1.x - s2.x, 2) + pow(s1.y - s2.y, 2) + pow(s1.z - s2.z, 2));
}

void detectSameStationAndRoute(Station &station1, Station &station2,
                               vector<Station> &stations) // O(n^3)
{
  bool routeExist = false;
  do {
    station2 = stations[rand() % 20];

    if (station1.name == station2.name) // detectSameStation
      continue;

    for (const auto &route : station1.routes) // detectSameStationAndRoute
    {
      if (route.to == station2.name)
        continue;
      routeExist = true;
    }
  } while (routeExist = false);
}

void updateStation(Station &station, vector<Station> &stations) {
  for (Station &s : stations) {
    if (s.name == station.name) {
      s = station;
      break;
    }
  }
}

void generateRoute(Station &station1,
                   vector<Station> &stations) // non-directed graph
{                                             // generate one specific route
  Station station2 = stations[rand() % 20];

  // CASES
  // 1. cannot route back to same station
  // 2. cannot route to same station twice
  // 3. if A -> B, then B -> A

  // (1. same station)
  // (2. same route)
  detectSameStationAndRoute(station1, station2, stations);

  Route route;
  route.from = station1.name;
  route.to = station2.name;
  route.distance = calculateDistance(station1, station2);
  station1.routes.push_back(route);
  // replace station1 with its index in stations
  updateStation(station1, stations);

  // (3. A -> B, B -> A)
  Route route2;
  route2.from = station2.name;
  route2.to = station1.name;
  route2.distance = calculateDistance(station2, station1);
  station2.routes.push_back(route2);
  updateStation(station2, stations);
}

void generateData(vector<Station> &stations) // points to stations variable
{
  srand(ID1 + ID2);
  // generate 20 stations without routes
  for (char stationName = 'A'; stationName <= 'T'; ++stationName) {
    // A to T is 20 steps
    Station station;
    station.name = stationName;
    station.x = rand() % 80 + 1;
    station.y = rand() % 80 + 1;
    station.z = rand() % 80 + 1;
    station.weight = rand() % 20;
    station.profit = rand() % 50;
    stations.push_back(station); // the reason why routes is not saved
  }

  // generate more routes if any station has less than 3 routes
  for (int i = 0; i < 20; i++) {
    Station station1 = stations[i];
    while (station1.routes.size() < 3) {
      generateRoute(station1, stations);
    }
  }
}

// ************
// NOT DONE YET
// ************
vector<vector<int>> generateAdjacencyMatrix(
    const vector<Station> &stations) { // weighted, and directed graph
  // Initialize the adjacency matrix with 0s
  vector<vector<int>> adjacencyMatrix(stations.size(),
                                      vector<int>(stations.size(), 0));

  for (Station station : stations) {
    // For each route
    for (const Route &route : station.routes) {
      // Find the indices of the 'from' and 'to' stations
      int fromIndex = route.from - 'A';
      int toIndex = route.to - 'A';

      // Set the corresponding cell in the adjacency matrix to 1
      adjacencyMatrix[fromIndex][toIndex] = 1;
    }
  }

  // generate route with weight

  return adjacencyMatrix;
}

void printArray(vector<Station> stations) {

  printf("Printing the station...\n");
  for (const auto &station : stations) {
    cout << "Station " << station.name << " " << station.x << " " << station.y
         << " " << station.z << " " << station.weight << " " << station.profit
         << endl;

    // printf("Printing the routes...\n");
    cout << "Printing the routes of Station " << station.name << "..." << endl;
    for (const Route &route : station.routes) {
      cout << "Route from Station " << route.from << " to Station " << route.to
           << ", Distance: " << route.distance << endl;
      printf("Route printed\n");
    }
    printf("\n");
  }
}

void printAdjacencyMatrix(vector<vector<int>> adjacencyMatrix) {

  // add column number
  printf("     ");
  for (int x = 1; x <= adjacencyMatrix[0].size(); x++) {
    printf("%2d ", x);
  }
  printf(" \n");
  for (int i = 0; i < adjacencyMatrix.size(); i++) {
    printf("%2d [ ", i); // add row number
    for (const auto &cell : adjacencyMatrix[i]) {
      printf("%2d ", cell);
    }
    printf("]");
    cout << endl;
  }
}

int main() {
  vector<Station> stations;
  generateData(stations);
  vector<vector<int>> adjacencyMatrix = generateAdjacencyMatrix(stations);
  printArray(stations);
  printAdjacencyMatrix(adjacencyMatrix);
}
