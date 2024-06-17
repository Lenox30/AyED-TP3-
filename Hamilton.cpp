

/**
#define INFI std::numeric_limits<double>::infinity()
#define MAXNODOS 10
#define MIEMBRO 1
#define NO_MIEMBRO 0

// C[i][j] Costo de la arista de i a j
// D[i] costo del camino mínimo conocido hasta el momento de s a i
// S[i] conjunto de nodos cuya distancia mínima a s es conocida y permanente, inicialmente S[] solo contiene a s
// Pre[i] contiene el vértice que precede a i en el camino mínimo encontrado hasta el momento

// Implementación de la función dijkstra
// Implementación de la función dijkstra
// Implementación de la función dijkstra
#include <vector>
#include <iostream>
#include <iomanip>

#include <vector>
#include <iostream>
#include <iomanip>

// Implementación de la función dijkstra
std::vector<int> dijkstra(Grafo& grafo, int s, int t, std::vector<double>& dist) {
    const auto& matriz = grafo.getMatriz(); // Obtener la matriz de costos del grafo
    int n = matriz.size(); // Número de nodos en el grafo
    dist.assign(n, INFINITY); // Inicializar distancias a infinito
    std::vector<int> predecesor(n, -1); // Inicializar predecesores a -1
    std::vector<int> visited(n, 0); // Inicializar todos los nodos como no visitados
    dist[s] = 0; // La distancia al nodo fuente es 0

    while (true) {
        int u = -1;

        // Seleccionar el nodo no visitado con la distancia mínima
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        if (u == -1 || dist[u] == INFINITY) {
            break; // No quedan nodos no visitados o el nodo alcanzable más cercano tiene distancia infinita
        }

        visited[u] = 1; // Marcar el nodo u como visitado

        // Actualizar las distancias de los nodos vecinos
        for (int v = 0; v < n; ++v) {
            if (matriz[u][v] != INFINITY && !visited[v]) { // Si hay una arista y el nodo no ha sido visitado
                double newDist = dist[u] + matriz[u][v];
                if (newDist < dist[v]) { // Si se encuentra una distancia menor
                    dist[v] = newDist; // Actualizar la distancia mínima al nodo v
                    predecesor[v] = u; // Establecer el predecesor de v como u
                    std::cout << "Actualizando predecesor de " << v << " a " << u << " (distancia: " << newDist << ")\n";
                }
            }
        }

        // Imprimir las tablas D, S y Pre después de cada iteración
        std::cout << "\n\n         D     S     Pre\n";
        for (int i = 0; i < n; ++i) {
            std::cout << "[" << std::setw(2) << i << "] ";
            if (dist[i] == INFINITY) {
                std::cout << std::setw(5) << "INF";
            } else {
                std::cout << std::setw(5) << dist[i];
            }
            std::cout << std::setw(6) << visited[i];
            std::cout << std::setw(7) << predecesor[i] << "\n";
        }
    }

    return predecesor; // Retornar el vector de predecesores
}

void camino(const std::vector<int>& P, int s, int t) {
    if (t == s)
        std::cout << s << " ";
    else {
        camino(P, s, P[t]);
        std::cout << t << " ";
    }
}
**/

#include "Hamilton.h"

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

    // Cola para almacenar el estado de búsqueda: (nodo actual, máscara de visitados, costo actual, camino actual)
    std::queue<std::tuple<int, int, double, std::vector<int>>> q;
    q.push({0, 1, 0.0, {0}}); // Comenzamos en el nodo 0 con la máscara que indica que solo el nodo 0 ha sido visitado

    while (!q.empty()) {
        auto [u, mask, cost, path] = q.front();
        q.pop();

        // Si todos los nodos han sido visitados, intentamos regresar al nodo inicial
        if (mask == (1 << n) - 1) {
            if (matriz[u][0] != std::numeric_limits<double>::infinity()) {
                double total_cost = cost + matriz[u][0];
                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = path;
                    best_path.push_back(0);
                }
                // Imprimir el ciclo hamiltoniano encontrado
                std::cout << "Ciclo Hamiltoniano encontrado: ";
                for (int i = 0; i < path.size(); ++i) {
                    std::cout << path[i] << "->";
                }
                std::cout << "0 con costo " << total_cost << std::endl;
            }
            continue;
        }

        // Explorar todos los vecinos
        for (int v = 0; v < n; ++v) {
            if (!(mask & (1 << v)) && matriz[u][v] != std::numeric_limits<double>::infinity()) {
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
                if (matriz[nodos[i]][nodos[i + 1]] == std::numeric_limits<double>::infinity()) {
                    valido = false;
                    break;
                }
                cost += matriz[nodos[i]][nodos[i + 1]];
            }
            if (valido && matriz[nodos[n - 1]][nodos[0]] != std::numeric_limits<double>::infinity()) {
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
