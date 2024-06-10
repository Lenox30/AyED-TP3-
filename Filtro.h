#ifndef FILTRO_H
#define FILTRO_H

#include "Imagen.h"
#include <vector>

class Filtro {
public:
    Filtro(const Imagen& imagen);
    void encontrarManchas();

private:
    const Imagen& imagen;
    std::vector<std::pair<int, int>> manchas;
};

#endif // FILTRO_H
