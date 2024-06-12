#include "DijkstraPrim.h"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>
#include <numeric>

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
double busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    double min_cost = std::numeric_limits<double>::infinity();
    std::vector<int> best_path;

    // Cola para almacenar el estado de búsqueda: (nodo actual, máscara de visitados, costo actual, camino actual)
    std::queue<std::tuple<int, int, double, std::vector<int>>> q;
    q.push({0, 1, 0.0, {0}}); // Comenzamos en el nodo 0 con la máscara que indica que solo el nodo 0 ha sido visitado

    while (!q.empty()) {
        auto [u, mask, cost, path] = q.front();
        q.pop();

        // Si todos los nodos han sido visitados, intentamos regresar al nodo inicial
        if (mask == (1 << n) - 1) {
            double total_cost = cost + matriz[u][0];
            if (total_cost < min_cost) {
                min_cost = total_cost;
                best_path = path;
                best_path.push_back(0);
            }
            continue;
        }

        // Explorar todos los vecinos
        for (int v = 0; v < n; ++v) {
            if (!(mask & (1 << v)) && matriz[u][v] != INFINITY) {
                auto new_path = path;
                new_path.push_back(v);
                q.push({v, mask | (1 << v), cost + matriz[u][v], new_path});
            }
        }
    }

    // Verificar si no se encontró un ciclo válido
    if (min_cost == std::numeric_limits<double>::infinity()) {
        std::cout << "No se pudo encontrar un ciclo Hamiltoniano valido debido a las barreras." << std::endl;

        // Buscar todos los posibles caminos que visitan todas las manchas
        std::vector<int> nodos(n);
        std::iota(nodos.begin(), nodos.end(), 0);

        do {
            bool valido = true;
            double cost = 0;
            for (int i = 0; i < n - 1; ++i) {
                if (matriz[nodos[i]][nodos[i + 1]] == INFINITY) {
                    valido = false;
                    break;
                }
                cost += matriz[nodos[i]][nodos[i + 1]];
            }
            if (valido && matriz[nodos[n - 1]][nodos[0]] != INFINITY) {
                cost += matriz[nodos[n - 1]][nodos[0]];
                std::cout << "Posible ciclo Hamiltoniano: ";
                for (int i = 0; i < n; ++i) {
                    std::cout << nodos[i] << "->";
                }
                std::cout << nodos[0] << " con costo " << cost << std::endl;
            }
        } while (std::next_permutation(nodos.begin(), nodos.end()));
    } else {
        // Mostrar el camino del ciclo Hamiltoniano de costo mínimo
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << min_cost << std::endl;
        std::cout << "Camino: ";
        for (int i = 0; i < best_path.size(); ++i) {
            std::cout << best_path[i] << (i == best_path.size() - 1 ? "" : "->");
        }
        std::cout << std::endl;
        camino = best_path;
    }

    return min_cost;
}