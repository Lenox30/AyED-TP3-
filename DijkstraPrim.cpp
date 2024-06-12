#include "DijkstraPrim.h"
#include <vector>
#include <queue>
#include <limits>

std::vector<int> dijkstra(const Grafo& grafo, int inicio) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> predecesor(n, -1);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    dist[inicio] = 0;
    pq.push({0, inicio});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < n; ++v) {
            if (matriz[u][v] != INFINITY && dist[u] + matriz[u][v] < dist[v]) {
                dist[v] = dist[u] + matriz[u][v];
                predecesor[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    return predecesor;
}

std::vector<std::pair<int, int>> prim(const Grafo& grafo) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    std::vector<bool> enMST(n, false);
    std::vector<double> clave(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<>> pq;

    clave[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        enMST[u] = true;

        for (int v = 0; v < n; ++v) {
            if (matriz[u][v] != INFINITY && !enMST[v] && matriz[u][v] < clave[v]) {
                clave[v] = matriz[u][v];
                parent[v] = u;
                pq.push({clave[v], v});
            }
        }
    }

    std::vector<std::pair<int, int>> result;
    for (int i = 1; i < n; ++i) {
        if (parent[i] != -1) {
            result.push_back({parent[i], i});
        }
    }

    return result;
}

// encontrar el ciclo Hamiltoniano de costo mínimo
double busquedaAmplitud(const Grafo& grafo) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    double min_cost = std::numeric_limits<double>::infinity();

    // Cola para almacenar el estado de búsqueda: (nodo actual, máscara de visitados, costo actual)
    std::queue<std::tuple<int, int, double>> q;
    q.push({0, 1, 0.0}); // Comenzamos en el nodo 0 con la máscara que indica que solo el nodo 0 ha sido visitado

    while (!q.empty()) {
        auto [u, mask, cost] = q.front();
        q.pop();

        // Si todos los nodos han sido visitados, intentamos regresar al nodo inicial
        if (mask == (1 << n) - 1) {
            min_cost = std::min(min_cost, cost + matriz[u][0]);
            continue;
        }

        // Explorar todos los vecinos
        for (int v = 0; v < n; ++v) {
            if (!(mask & (1 << v)) && matriz[u][v] != INFINITY) {
                q.push({v, mask | (1 << v), cost + matriz[u][v]});
            }
        }
    }

    // Verificar si no se encontró un ciclo válido
    if (min_cost == std::numeric_limits<double>::infinity()) {
        std::cout << "No se pudo encontrar un ciclo Hamiltoniano valido debido a las barreras." << std::endl;
    }

    return min_cost;
}