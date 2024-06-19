#include "Imagen.h"
#include "Filtro.h"
#include "Grafo.h"
#include "Hamilton.h"

using namespace std;

int main() {
    Imagen imagen("C:\\Users\\Ivan\\CLionProjects\\AyED-TPFINAL\\imagen.txt");
    imagen.imprimir();
    std::cout << std::endl;

    Filtro filtro(imagen);
    filtro.encontrarManchas();

    Grafo grafo(filtro.getManchas(), imagen.getBarreras());
    grafo.imprimir();

    Hamilton hamilton;  // Crear instancia de la clase Hamilton

    vector<double> dist;

    std::vector<int> caminoHamiltoniano;
    hamilton.busquedaAmplitud(grafo, caminoHamiltoniano);

}
