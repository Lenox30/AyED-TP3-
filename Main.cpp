#include <iostream>
#include "Imagen.h"
#include "Filtro.h"
#include "Filtro.cpp"
#include "Imagen.cpp"

int main() {
    Imagen imagen("C:\\Users\\lenox\\Desktop\\AyED\\Parciales\\Terceer Paricial\\Codigo\\imagen.txt");
    imagen.imprimir();

    Filtro filtro(imagen);
    filtro.encontrarManchas();

    return 0;
}

