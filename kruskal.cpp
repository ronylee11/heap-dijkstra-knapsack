#include <iostream>
#include <vector>
#include <algorithm>
#include "structs.h"

using namespace std;

bool routeComparator(const Route &a, const Route &b) {
    return a.weight < b.weight;
}

char findRoot(char parent[], char vertex) {
    // if parent of current vertex = vertex itself, it is the root
    if (parent[vertex - 'A'] == vertex)
        return vertex;

    // else, find root
    return findRoot(parent, parent[vertex - 'A']);
}

// minimum spanning tree
void kruskal(const vector<Station> &stations)
{
    // make all routes into one vector
    vector<Route> allRoutes;
    for(const auto &station : stations)
        allRoutes.insert(allRoutes.end(), station.routes.begin(), station.routes.end());
    
    // sort all routes from smallest in order of weight 
    sort(allRoutes.begin(), allRoutes.end(), routeComparator);
    
    // initialise station
    char parent[20];
    for (char c = 'A'; c <= 'T'; ++c)
        parent[c - 'A'] = c;

    vector<Route> mst;
    int totalWeight = 0;

    // iterate until stations.size()-1 routes
    for(const auto &route: allRoutes) {
        char fromStation = findRoot(parent, route.from);
        char toStation = findRoot(parent, route.to);

        // check if adding this route will form a cycle
        // if not, include the edge
        if(fromStation != toStation) {
            mst.push_back(route);
            parent[fromStation - 'A'] = toStation;
            totalWeight += route.weight;
        }
    }

    // print 
    cout << "Minimum spanning tree:" << endl;
    for (const auto &route : mst)
    {
        cout << route.from << " - " << route.to << ", weight: " << route.weight << ", distance: " << route.distance << endl;
    }

    cout << "\nTotal weight of MST: " << totalWeight << endl;
}
