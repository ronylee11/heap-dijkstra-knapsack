#include <iostream>
#include <math.h>
#include <vector>

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

void updateRoute(Station &fromStation, Station &toStation) {
    Route route;
    route.from = fromStation.name;
    route.to = toStation.name;
    route.distance = calculateDistance(fromStation, toStation);
    fromStation.routes.push_back(route);
}

void generateRoute(int stationIndex1, vector<Station> &stations, int &totalGeneratedRoutes)
{
    int stationIndex2 = rand() % 20;

    // prevent station1 pointing to itself
    while (stationIndex1 == stationIndex2)
    {
        stationIndex2 = rand() % 20;
    }

    Station station1 = stations[stationIndex1];
    Station station2 = stations[stationIndex2];

    // prevent duplicated routes
    bool routeExist = false;
    for (const auto &route : station1.routes)
    {
        if (route.to == station2.name)
        {
            routeExist = true;
            break;
        }
    }

    if (!routeExist)
    {
        updateRoute(station1, station2);
        stations[stationIndex1] = station1;

        // reverse
        updateRoute(station2, station1);
        stations[stationIndex2] = station2;
        totalGeneratedRoutes++;
    }
}

void generateData(vector<Station> &stations)
{
    srand(ID1 + ID2);

    // generate 20 stations, from A to T
    for (char stationName = 'A'; stationName <= 'T'; ++stationName)
    {
        Station station;
        station.name = stationName;
        station.x = rand() % 80 + 1;
        station.y = rand() % 80 + 1;
        station.z = rand() % 80 + 1;
        station.weight = rand() % 20;
        station.profit = rand() % 50;
        stations.push_back(station);
    }

    // generate routes
    int totalGeneratedRoutes = 0;

    // target 1: ensure each station connects to at least 3 other stations
    for (int i = 0; i < 20; i++)
    {
        while (stations[i].routes.size() < 3)
        {
            generateRoute(i, stations, totalGeneratedRoutes);
        }
    }

    // target 2: ensure there is 54 routes
    while (totalGeneratedRoutes < 54)
    {
        int stationIndex1 = rand() % 20;
        generateRoute(stationIndex1, stations, totalGeneratedRoutes);
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
        printf("\n");
    }
}

int main()
{
    vector<Station> stations;
    generateData(stations);
    printArray(stations);
}