#ifndef PROYECTO2CONTROLAEROPUERTO_GRAFO_H
#define PROYECTO2CONTROLAEROPUERTO_GRAFO_H
#include <iostream>
#include <unordered_map>
#include <list>
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
};
class Grafo {
private:
    NodoVertice* vertices;
    NodoVertice* buscarVertice(const std::string& ciudad);
    NodoVertice* agregarVertice(const std::string& ciudad);
public:
    Grafo();
    ~Grafo();
    void agregarRuta(const Ruta& ruta);
    void imprimirGrafo();
    void generarReporte(const std::string& nombreArchivo);
    // agregar métodos para encontrar la ruta más corta
};
#endif //PROYECTO2CONTROLAEROPUERTO_GRAFO_H
