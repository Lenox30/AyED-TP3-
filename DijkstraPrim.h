#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include "Grafo.h"
#include <vector>
#include <queue>
#include <limits>

std::vector<int> dijkstra(const Grafo& grafo, int inicio);
std::vector<std::pair<int, int>> prim(const Grafo& grafo);
double busquedaAmplitud(const Grafo& grafo);

#endif // ALGORITMOS_H
