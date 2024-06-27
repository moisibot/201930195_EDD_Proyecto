#ifndef PROYECTO2CONTROLAEROPUERTO_REPORTES_H
#define PROYECTO2CONTROLAEROPUERTO_REPORTES_H
#include <fstream>
#include <string>
#include "../estructuras/ArbolB.h"
#include "../estructuras/ListaCircularDoble.h"
#include "../estructuras/TablaHash.h"
#include "../estructuras/Grafo.h"
#include "../estructuras/MatrizDispersa.h"
#include "../estructuras/ArbolBinarioBusqueda.h"
class Reportes {
public:
    void generarReporteArbolB(ArbolB& arbolAviones);
    void generarReporteListaMantenimiento(ListaCircularDoble& listaMantenimiento);
    void generarReporteArbolBinario(ArbolBinarioBusqueda& arbolPilotos);
    void generarReporteTablaHash(TablaHash& tablaPilotos);
    void generarReporteGrafoDirigido(Grafo& grafoRutas);
    void generarReporteMatrizDispersa(MatrizDispersa& matrizVuelos);
    void generarImagenDesdeArchivoDot(const std::string& archivoEntrada, const std::string& archivoSalida, const std::string& formato);
};
#endif //PROYECTO2CONTROLAEROPUERTO_REPORTES_H