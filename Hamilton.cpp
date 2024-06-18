#include "Hamilton.h"
#include "Cola.h"
#include <unordered_set>


std::vector<std::pair<int, int>> Hamilton::prim(const Grafo& grafo) {
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
            if (matriz[u][v] != std::numeric_limits<double>::infinity() && !enMST[v] && matriz[u][v] < clave[v]) {
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

double Hamilton::busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino) {
    const auto& matriz = grafo.getMatriz();
    int n = matriz.size();
    double min_cost = std::numeric_limits<double>::infinity();
    std::vector<int> best_path;

    Cola<std::tuple<int, int, double, std::vector<int>>> q;
    q.encolar(std::make_tuple(0, 1, 0.0, std::vector<int>{0}));

    while (!q.colavacia()) {
        auto [u, mask, cost, path] = q.tope();
        q.desencolar();

        // Si todos los nodos han sido visitados, verifica si es posible regresar al nodo inicial.
        if (mask == (1 << n) - 1) {
            if (matriz[u][0] != std::numeric_limits<double>::infinity()) {
                double total_cost = cost + matriz[u][0];
                // Imprime el ciclo hamiltoniano encontrado.
                std::cout << "Ciclo Hamiltoniano encontrado: ";
                for (int i = 0; i < path.size(); ++i) {
                    std::cout << path[i] << "->";
                }
                std::cout << "0 con costo " << total_cost << std::endl;

                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = path;
                    best_path.push_back(0);
                }
            }
            continue;
        }

        // Explorar todos los vecinos
        for (int v = 0; v < n; ++v) {
            if (!(mask & (1 << v)) && matriz[u][v] != std::numeric_limits<double>::infinity()) {
                auto new_path = path;
                new_path.push_back(v);
                q.encolar(std::make_tuple(v, mask | (1 << v), cost + matriz[u][v], new_path));
            }
        }
    }

    if (min_cost != std::numeric_limits<double>::infinity()) {
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << min_cost << std::endl;
        std::cout << "Camino: ";
        for (int i = 0; i < best_path.size(); ++i) {
            std::cout << best_path[i] << (i == best_path.size() - 1 ? "" : "->");
        }
        std::cout << std::endl;
        camino = best_path;
    } else {
        std::cout << "No se pudo encontrar un ciclo Hamiltoniano valido debido a las barreras." << std::endl;
    }

    return min_cost;
}