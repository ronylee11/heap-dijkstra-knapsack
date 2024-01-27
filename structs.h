#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <vector>

using namespace std;

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

#endif // STRUCTS_H_
