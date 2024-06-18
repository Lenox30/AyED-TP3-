#include "Hamilton.h"

double Hamilton::busquedaAmplitud(const Grafo& grafo, std::vector<int>& camino) {
    // Obtiene la matriz de adyacencia del grafo
    const auto& matriz = grafo.getMatriz();
    // Obtiene el número de nodos en el grafo
    int n = matriz.size();
    // Inicializa el costo mínimo como infinito
    double min_cost = std::numeric_limits<double>::infinity();
    // Vector para almacenar el mejor camino encontrado
    std::vector<int> best_path;

    // Inicializa la cola para la búsqueda en amplitud.
    // Utilizamos un tuple que almacena el nodo actual (int), la máscara de visitados (std::vector<bool>), el costo acumulado (double), y un vector con el camino recorrido (std::vector<int>)
    Cola<std::tuple<int, std::vector<bool>, double, std::vector<int>>> q;
    // Inicializa la máscara de visitados con todos los nodos no visitados (false)
    std::vector<bool> visitados(n, false);
    // Marca el nodo inicial (0) como visitado
    visitados[0] = true;
    // Encola el estado inicial: nodo 0, vector , costo 0, y camino inicial con nodo 0
    q.encolar(std::make_tuple(0, visitados, 0.0, std::vector<int>{0}));

    // Mientras la cola no esté vacía
    while (!q.colavacia()) {
        // Obtiene el estado en el tope de la cola
        auto [u, visitados, cost, path] = q.tope();
        // Desencola el estado del tope
        q.desencolar();

        // Si todos los nodos han sido visitados, verifica si es posible regresar al nodo inicial
        if (std::all_of(visitados.begin(), visitados.end(), [](bool v){ return v; })) {
            // Si hay una arista de regreso al nodo inicial
            if (matriz[u][0] != std::numeric_limits<double>::infinity()) {
                // Calcula el costo total del ciclo hamiltoniano
                double total_cost = cost + matriz[u][0];
                // Imprime el ciclo hamiltoniano encontrado
                std::cout << "Ciclo Hamiltoniano encontrado: ";
                for (int i = 0; i < path.size(); ++i) {
                    std::cout << path[i] << "->";
                }
                std::cout << "0 con costo " << total_cost << std::endl;

                // Actualiza el ciclo de menor costo si es necesario
                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = path;
                    best_path.push_back(0);
                }
            }
            continue;
        }

        // Explora todos los vecinos del nodo actual
        for (int v = 0; v < n; ++v) {
            // Si el nodo v no ha sido visitado y hay una arista del nodo u al nodo v
            if (!visitados[v] && matriz[u][v] != std::numeric_limits<double>::infinity()) {
                // Crea un nuevo camino agregando el nodo v
                auto new_path = path;
                new_path.push_back(v);
                // Crea una nueva máscara de visitados
                auto new_visitados = visitados;
                // Marca el nodo v como visitado
                new_visitados[v] = true;
                // Encola el nuevo estado: nodo v, máscara de visitados actualizada, nuevo costo, y el nuevo camino
                q.encolar(std::make_tuple(v, new_visitados, cost + matriz[u][v], new_path));
            }
        }
    }

    // Si se encontró un ciclo Hamiltoniano, muestra el costo mínimo y el camino
    if (min_cost != std::numeric_limits<double>::infinity()) {
        std::cout << "Costo minimo del ciclo Hamiltoniano: " << min_cost << std::endl;
        std::cout << "Camino: ";
        for (int i = 0; i < best_path.size(); ++i) {
            std::cout << best_path[i] << (i == best_path.size() - 1 ? "" : "->");
        }
        std::cout << std::endl;
        // Actualiza el camino proporcionado con el mejor camino encontrado
        camino = best_path;
    } else {
        // Informa que no se pudo encontrar un ciclo Hamiltoniano válido
        std::cout << "No se pudo encontrar un ciclo Hamiltoniano valido debido a las barreras." << std::endl;
    }

    // Devuelve el costo mínimo del ciclo Hamiltoniano encontrado
    return min_cost;
}