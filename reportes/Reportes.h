#ifndef PROYECTO2CONTROLAEROPUERTO_REPORTES_H
#define PROYECTO2CONTROLAEROPUERTO_REPORTES_H
#include <fstream>
#include <string>
#include "../estructuras/ListaCircularDoble.h"
#include "../estructuras/ArbolB.h"
#include "../estructuras/ArbolBinarioBusqueda.h"
#include "../estructuras/TablaHash.h"
#include "../estructuras/MatrizDispersa.h"
#include "../estructuras/Grafo.h"
class Reportes {
public:
    static void generarReporteArbolB(const ArbolB* arbol);
    static void generarReporteListaCircularDoble(const ListaCircularDoble* lista);
    static void generarReporteArbolBinario(const ArbolBinarioBusqueda* arbol);
    static void generarReporteTablaHash(const TablaHash* tabla);
    static void generarReporteGrafo(const Grafo* grafo);
    static void generarReporteMatrizDispersa(const MatrizDispersa* matriz);

private:
    static void ejecutarGraphviz(const std::string& nombreArchivo);
};
#endif //PROYECTO2CONTROLAEROPUERTO_REPORTES_H