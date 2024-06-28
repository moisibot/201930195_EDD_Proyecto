#ifndef PROYECTO2CONTROLAEROPUERTO_ARBOLBINARIO_H
#define PROYECTO2CONTROLAEROPUERTO_ARBOLBINARIO_H
#include "../Objetos/Piloto.h"
#include <iostream>
#include <fstream>
#include <string>

class NodoABB {
public:
    Piloto dato;
    NodoABB* izquierdo;
    NodoABB* derecho;
    NodoABB(const Piloto& piloto);
};

class ArbolBinarioBusqueda {
private:
    NodoABB* raiz;
    void insertarRecursivo(NodoABB*& nodo, const Piloto& piloto);
    void inordenRecursivo(NodoABB* nodo) const;
    void preordenRecursivo(NodoABB* nodo) const;
    void postordenRecursivo(NodoABB* nodo) const;
    void destruirRecursivo(NodoABB* nodo);
    void generarDotRecursivo(NodoABB* nodo, std::ofstream& archivo) const;

public:
    ArbolBinarioBusqueda();
    ~ArbolBinarioBusqueda();
    void insertar(const Piloto& piloto);
    void inorden() const;
    void preorden() const;
    void postorden() const;
    void generarReporte(const std::string& nombreArchivo) const;

    NodoABB *eliminarRecursivo(NodoABB *nodo, const std::string &id);

    void eliminar(const std::string &id);

    NodoABB *encontrarMinimo(NodoABB *nodo);
};
#endif //PROYECTO2CONTROLAEROPUERTO_ARBOLBINARIO_H