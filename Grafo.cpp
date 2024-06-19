#include "Grafo.h"
#include <algorithm>  // Para std::sort


// Constructor: Inicializa el grafo con las manchas y barreras proporcionadas.
Grafo::Grafo(const std::vector<std::pair<int, int>>& manchas, const std::set<std::pair<int, int>>& barreras)
        : manchas(manchas), barreras(barreras) {
    crearGrafo();  // Llama a crearGrafo para construir la matriz de adyacencia del grafo.
}

// Método para calcular la distancia Euclidiana entre dos puntos.
double Grafo::calcularDistancia(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

// Método para determinar si existe una barrera entre dos puntos.
bool Grafo::hayBarrera(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
    // Convertir set a vector para poder ordenar y acceder secuencialmente
    std::vector<std::pair<int, int>> barrerasOrdenadas(barreras.begin(), barreras.end());
    // Ordenar barreras primero por x, luego por y para detectar fácilmente segmentos continuos
    std::sort(barrerasOrdenadas.begin(), barrerasOrdenadas.end());

    // Procesar barreras ordenadas para detectar segmentos
    for (size_t i = 0; i < barrerasOrdenadas.size(); ++i) {
        std::pair<int, int> c = barrerasOrdenadas[i];
        std::pair<int, int> d;  // Punto final del segmento

        // Determinar si el siguiente punto forma un segmento horizontal o vertical
        if (i + 1 < barrerasOrdenadas.size()) {
            if (barrerasOrdenadas[i + 1].first == c.first && barrerasOrdenadas[i + 1].second == c.second + 1) {
                // Segmento vertical
                d = {c.first, c.second + 1};
            } else if (barrerasOrdenadas[i + 1].first == c.first + 1 && barrerasOrdenadas[i + 1].second == c.second) {
                // Segmento horizontal
                d = {c.first + 1, c.second};
            } else {
                // No forma un segmento con el siguiente, asume segmento mínimo de 1 unidad
                continue;
            }
        } else {
            // Último punto, no puede formar un segmento con un punto siguiente
            continue;
        }

        // Calcular los vectores del segmento (a, b) y del segmento (c, d)
        int dx1 = b.first - a.first;
        int dy1 = b.second - a.second;
        int dx2 = d.first - c.first;
        int dy2 = d.second - c.second;
        int vx = c.first - a.first;
        int vy = c.second - a.second;

        // Determinar si los segmentos se intersectan mediante el producto vectorial
        double vp = dx1 * dy2 - dx2 * dy1;
        if (vp == 0) continue;  // Segmentos paralelos, continuar la búsqueda

        // Calcular las escalas en las que los segmentos se intersectarían si fueran a hacerlo
        double k1 = (vx * dy2 - vy * dx2) / vp;
        double k2 = (vx * dy1 - vy * dx1) / vp;

        // Verificar si las escalas están dentro de los segmentos, lo que indica una intersección
        if (k1 >= 0 && k1 <= 1 && k2 >= 0 && k2 <= 1) {
            return true;  // Intersección encontrada
        }
    }
    return false;  // No se encontraron intersecciones
}

// Método para construir la matriz de adyacencia del grafo.
void Grafo::crearGrafo() {
    int n = manchas.size();
    matriz.resize(n, std::vector<double>(n, INFINITY));  // Inicializa la matriz con infinito.
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Verificar que no se calcule la distancia de un nodo a sí mismo y que no haya barreras.
            if (i != j && !hayBarrera(manchas[i], manchas[j])) {
                matriz[i][j] = calcularDistancia(manchas[i], manchas[j]);  // Calcular distancia y asignar.
            }
        }
    }
}

// Método para imprimir la matriz de adyacencia del grafo.
void Grafo::imprimir() const {
    int n = manchas.size();
    // Imprimir los encabezados de las columnas.
    for (int i = 0; i < n; ++i) {
        std::cout << "\tM" << i;
    }
    std::cout << "\n";
    // Imprimir cada fila de la matriz.
    for (int i = 0; i < n; ++i) {
        std::cout << "M" << i << ":\t";
        for (int j = 0; j < n; ++j) {
            if (matriz[i][j] == INFINITY) {
                std::cout << "INF\t";
            } else {
                std::cout << std::fixed << std::setprecision(2) << matriz[i][j] << "\t";
            }
        }
        std::cout << std::endl;
    }
}

// Método para obtener la matriz de adyacencia.
const std::vector<std::vector<double>>& Grafo::getMatriz() const {
    return matriz;  // Devuelve la matriz de adyacencia.
}