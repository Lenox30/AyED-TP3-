#ifndef HAMILTON_H
#define HAMILTON_H

#include "Cola.h"
#include "Grafo.h"
#include <vector>
#include <queue>
#include <tuple>
#include <limits>
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;

class Hamilton {
public:
    vector<pair<int, int>> Prim(const Grafo& grafo);
    double busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino);
};

#endif // HAMILTON_H
