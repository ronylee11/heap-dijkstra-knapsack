#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

const double ID1 = 1211306086;
const double ID2 = 1211307001;

struct Route
{
    char from, to;
    int distance;
};

struct Station
{
    char name;
    int x, y, z;
    int weight, profit;
    vector<Route> routes;
};

int calculateDistance(const Station &s1, const Station &s2)
{
    return sqrt(pow(s1.x - s2.x, 2) + pow(s1.y - s2.y, 2) + pow(s1.z - s2.z, 2));
}

void generateRoute(Station &station1, vector<Station> &stations)
{ // generate one specific route
    Station station2 = stations[rand() % 20];

    do
    { // if station 1 == station 2, generate another station
        station2 = stations[rand() % 20];
    } while (station1.name == station2.name);

    Route route;
    route.from = station1.name;
    route.to = station2.name;
    route.distance = calculateDistance(station1, station2);
    station1.routes.push_back(route);
}

void generateData(vector<Station> &stations) // points to stations variable
{
    srand(ID1 + ID2);
    for (char stationName = 'A'; stationName <= 'T'; ++stationName)
    { // generate 20 stations // A to T is 20 steps
        Station station;
        station.name = stationName;
        station.x = rand() % 80 + 1;
        station.y = rand() % 80 + 1;
        station.z = rand() % 80 + 1;
        station.weight = rand() % 20;
        station.profit = rand() % 50;
        stations.push_back(station);
    }

    // generate 54 routes
    for (int i = 0; i < 54; i++)
    {
        Station station1 = stations[rand() % 20];

        // recheck station, if station has less than 3 routes, generate more route
        while (station1.routes.size() < 3)
            generateRoute(station1, stations);
    }
}

// ************
// NOT DONE YET
// ************
vector<vector<int>> generateAdjacencyMatrix(const vector<Station> &stations)
{ // weighted, and directed graph
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

            // Set the corresponding cell in the adjacency matrix to 1
            adjacencyMatrix[fromIndex][toIndex] = 1;
        }
    }

    // generate route with weight

    return adjacencyMatrix;
}

void printArray(vector<Station> stations)
{
    for (const auto &station : stations)
    {
        cout << "Station " << station.name << " " << station.x << " " << station.y << " " << station.z << " "
             << station.weight << " " << station.profit << endl;

        for (const auto &route : station.routes)
        {
            cout << "Route from Station " << route.from << " to Station " << route.to
                 << ", Distance: " << route.distance << endl;
        }
    }
}

void printAdjacencyMatrix(vector<vector<int>> adjacencyMatrix)
{

    // add column number
    printf("     ");
    for (int x = 1; x <= adjacencyMatrix[0].size(); x++)
    {
        printf("%2d ", x);
    }
    printf(" \n");
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
        printf("%2d [ ", i); // add row number
        for (const auto &cell : adjacencyMatrix[i])
        {
            printf("%2d ", cell);
        }
        printf("]");
        cout << endl;
    }
}

int main()
{
    vector<Station> stations;
    generateData(stations);
    vector<vector<int>> adjacencyMatrix = generateAdjacencyMatrix(stations);
    printArray(stations);
    printAdjacencyMatrix(adjacencyMatrix);
}