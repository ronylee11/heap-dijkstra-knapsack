#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include "structs.h"

using namespace std;

const int INF = INT_MAX;

// shortest paths
void dijkstra(const vector<vector<int>> &adjacencyMatrix, int startStation)
{
    int totalStations = adjacencyMatrix.size();

    // store shortest distance from A to all other stations
    // set distance of all stations to INF
    vector<int> dist(totalStations, INF);

    // set the distance of src station as 0
    dist[startStation] = 0;

    // shortest paths tree, store visited stations
    // set all stations unvisited
    vector<bool> spTree(totalStations, false);

    // store paths
    vector<vector<int>> paths(totalStations);

    // find the shortest paths for all stations
    for (int i = 0; i < totalStations - 1; i++)
    {
        // pick an unvisited min dist
        int u = -1;

        for (int v = 0; v < totalStations; v++)
            if (!spTree[v] && (u == -1 || dist[v] <= dist[u]))
                u = v;    


        spTree[u] = true; // include u in sptTree, i.e. set station as visited

        // update dist value of all adjacent stations of u
        for (int v = 0; v < totalStations; v++)
        {
            if (!spTree[v] &&                              // v not visited
                adjacencyMatrix[u][v] &&                   // edge uv exist
                dist[u] + adjacencyMatrix[u][v] < dist[v]) // sum of dist[u] + weight uv < dist[v]
                {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                    paths[v] = paths[u];
                    paths[v].push_back(v);
                }
        }
    }

    // print distance & paths from A
    cout << endl;
    cout << "Stations | Distance from A | Path from A" << endl;
    for (int i = 0; i < totalStations; i++) {
        cout << "  " << static_cast<char>('A' + i) << "\t |\t" << dist[i];
        cout << "\t   |  A";
        if (i != 0)
            cout << " -> ";
        for (int j = 0; j < paths[i].size(); j++)
        {
            if (j != 0)
                cout << " -> ";
            cout << static_cast<char>('A' + paths[i][j]);
        }
        cout << endl;
    }
}
