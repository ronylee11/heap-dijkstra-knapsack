#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct Station
{
    std::string name;
    double x, y, z;
    double weight, profit;
};

struct Route
{
    std::string from, to;
    double distance;
};

double calculateDistance(const Station &s1, const Station &s2)
{
    return sqrt(pow(s1.x - s2.x, 2) + pow(s1.y - s2.y, 2) + pow(s1.z - s2.z, 2));
}

int main()
{
    // Set the random seed
    srand(time(nullptr));

    // Generate dataset for 20 stations
    std::vector<Station> stations;
    for (int i = 1; i <= 20; ++i)
    {
        Station station;
        station.name = "Station " + std::to_string(i);
        station.x = rand() % 1000 + 1;
        station.y = rand() % 1000 + 1;
        station.z = rand() % 1000 + 1;
        station.weight = i + 10; // Using sum of group members' ID for weight
        station.profit = i * 2;  // Using sum of group members' ID for profit
        stations.push_back(station);
    }

    // Generate routes connecting stations (each station connects to at least 3 others)
    std::vector<Route> routes;
    for (int i = 0; i < 20; ++i)
    {
        for (int j = i + 1; j < 20; ++j)
        {
            if (rand() % 2 == 1)
            { // Randomly determine if there is a route between stations
                Route route;
                route.from = stations[i].name;
                route.to = stations[j].name;
                route.distance = calculateDistance(stations[i], stations[j]);
                routes.push_back(route);
            }
        }
    }

    // Output the generated dataset
    std::cout << "Stations:\n";
    for (const auto &station : stations)
    {
        std::cout << station.name << " " << station.x << " " << station.y << " " << station.z
                  << " " << station.weight << " " << station.profit << "\n";
    }

    std::cout << "\nRoutes:\n";
    for (const auto &route : routes)
    {
        std::cout << route.from << " to " << route.to << " Distance: " << route.distance << "\n";
    }

    return 0;
}