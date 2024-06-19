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
    double calcularDistancia(std::pair<int, int> a, std::pair<int, int> b) const;
    bool hayBarrera(std::pair<int, int> a, std::pair<int, int> b) const;
    void crearGrafo();
};

#endif // GRAFO_H
