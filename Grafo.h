#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <cmath>
#include <set>
#include <utility>
#include <iostream>
#include <cmath>
#include <iomanip>

class Grafo {
public:
    Grafo(const std::vector<std::pair<int, int>>& manchas, const std::set<std::pair<int, int>>& barreras);
    void imprimir() const;
    const std::vector<std::vector<double>>& getMatriz() const;

private:
    const std::vector<std::pair<int, int>>& manchas;
    const std::set<std::pair<int, int>>& barreras;
    std::vector<std::vector<double>> matriz;

    // Método para calcular la distancia Euclidiana entre dos puntos
    double calcularDistancia(const std::pair<int, int>& a, const std::pair<int, int>& b) const;

    // Método para determinar si existe una barrera entre dos puntos, también utilizando referencias.
    bool hayBarrera(const std::pair<int, int>& a, const std::pair<int, int>& b) const;


    void crearGrafo();
};

#endif // GRAFO_H
