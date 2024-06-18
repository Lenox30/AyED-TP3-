#ifndef FILTRO_H
#define FILTRO_H

#include "Imagen.h"

class Filtro {
public:
    Filtro(const Imagen& imagen);
    void encontrarManchas();
    const std::vector<std::pair<int, int>>& getManchas() const;

private:
    const Imagen& imagen;
    std::vector<std::pair<int, int>> manchas;

};

#endif // FILTRO_H
