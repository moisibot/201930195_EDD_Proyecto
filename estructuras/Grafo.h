#ifndef PROYECTO2CONTROLAEROPUERTO_GRAFO_H
#define PROYECTO2CONTROLAEROPUERTO_GRAFO_H
#include <string>
#include "../Objetos/Ruta.h"
class NodoAdyacencia {
public:
    Ruta ruta;
    NodoAdyacencia* siguiente;
    NodoAdyacencia(const Ruta& r);
};

class NodoVertice {
public:
    std::string ciudad;
    NodoAdyacencia* listaAdyacencia;
    NodoVertice* siguiente;
    NodoVertice(const std::string& c);
    int distancia;
    NodoVertice* padre;
};
class NodoCamino {
public:
    std::string ciudad;
    NodoCamino* siguiente;
    NodoCamino(const std::string& c);
};
class Grafo {
private:
    NodoVertice* vertices;
    NodoVertice* agregarVertice(const std::string& ciudad);
    void encontrarTodasLasRutasAux(NodoVertice* verticeActual, const std::string& destino, NodoCamino* camino, NodoCamino*& rutas);
public:
    Grafo();
    ~Grafo();
    void agregarRuta(const Ruta& ruta);
    void imprimirGrafo();
    void generarReporte(const std::string& nombreArchivo);
    NodoVertice* buscarVertice(const std::string& ciudad);
    NodoCamino* encontrarTodasLasRutas(const std::string& origen, const std::string& destino);
    void recomendarRutas(const std::string& origen, const std::string& destino);
    void imprimirRutasDesde(const std::string& ciudad);
    void dijkstra(const std::string& origen, const std::string& destino);
    void mostrarCamino(NodoVertice* origen, NodoVertice* destino);
};
#endif //PROYECTO2CONTROLAEROPUERTO_GRAFO_H
