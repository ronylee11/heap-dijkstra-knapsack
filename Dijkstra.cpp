#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "structs.h"

using namespace std;

const int INF = INT_MAX;

int minDistance(const vector<int> &dist, const vector<bool> &sptSet)
{
    int min = INF;
    int u;

    for (int v = 0; v < 20; v++)
    {
        if (!sptSet[v] && dist[v] <= min)
        {
            min = dist[v];
            u = v;
        }
    }

    return u;
}

// shortest paths
void dijkstra(const vector<vector<int>> &adjacencyMatrix, int startStation)
{
    int totalStations = adjacencyMatrix.size();

    // store the shortest distance from A to all other stations
    // set the distance of all stations to INF
    vector<int> dist(totalStations, INF);

    // shortest paths tree
    // set all stations unvisited
    vector<bool> spTree(totalStations, false);

    // set the distance of start station as 0
    dist[startStation] = 0;

    // find the shortest paths for all stations
    for (int i = 0; i < totalStations - 1; i++)
    {
        int u = minDistance(dist, spTree);
        spTree[u] = true; // set station as visited

        for (int v = 0; v < totalStations; v++)
        {
            if (!spTree[v] && 
                adjacencyMatrix[u][v] &&
                dist[u] != INF &&
                dist[u] + adjacencyMatrix[u][v] < dist[v])
                dist[v] = dist[u] + adjacencyMatrix[u][v];
        }
    }

    // print
    cout << "Stations | Distance from A" << endl;
    for (int i = 0; i < 20; i++)
        cout << "  " << static_cast<char>('A' + i) << "\t\t" << dist[i] << endl;
}