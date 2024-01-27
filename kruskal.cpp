#include <iostream>
#include <vector>
#include <algorithm>
#include "structs.h"

using namespace std;

bool routeComparator(const Route &a, const Route &b) {
    return a.weight < b.weight;
}

bool mstComparator(const Route &a, const Route &b) {
    return a.from < b.from;
}

char findStation(char station[], char route) {
    if (station[route - 'A'] == route)
        return route;
    return findStation(station, station[route - 'A']);
}

// minimum spanning tree
void kruskal(const vector<Station> &stations)
{
    // make all routes into one vector
    vector<Route> allRoutes;
    for(const auto &station : stations) {
        allRoutes.insert(allRoutes.end(), station.routes.begin(), station.routes.end());
    }
        
    // sort all routes in non-decreasing order of weight 
    sort(allRoutes.begin(), allRoutes.end(), routeComparator);

    
    char station[20];
    for (char c = 'A'; c <= 'T'; ++c)
    {
        station[c - 'A'] = c;
    }

    vector<Route> mst;
    int totalWeight = 0;

    for(const auto &route: allRoutes) {
        char fromStation = findStation(station, route.from);
        char toStation = findStation(station, route.to);

        if(fromStation != toStation) {
            mst.push_back(route);
            station[fromStation - 'A'] = toStation;
            totalWeight += route.weight;
        }
    }

    sort(mst.begin(), mst.end(), mstComparator);

    cout << "Minimum Spanning Tree:" << endl;
    for (const auto &route : mst)
    {
        cout << route.from << " - " << route.to << ", Weight: " << route.weight << endl;
    }

    cout << "Total Weight of MST: " << totalWeight << endl;
}
