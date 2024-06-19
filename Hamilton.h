#ifndef HAMILTON_H
#define HAMILTON_H

#include "Cola.h"
#include "Grafo.h"
#include <tuple>
#include <limits>
#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <fstream>

class Hamilton {
public:
    double busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino);
};

#endif // HAMILTON_H
