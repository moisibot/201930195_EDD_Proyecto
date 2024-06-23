#ifndef PROYECTO2CONTROLAEROPUERTO_ARBOLBINARIO_H
#define PROYECTO2CONTROLAEROPUERTO_ARBOLBINARIO_H
#include "../Objetos/Piloto.h"
#include <iostream>
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
    void inordenRecursivo(NodoABB* nodo);
    void preordenRecursivo(NodoABB* nodo);
    void postordenRecursivo(NodoABB* nodo);
    void destruirRecursivo(NodoABB* nodo);
    NodoABB* eliminarNodo(NodoABB* nodo, int horasDeVuelo);
    NodoABB* encontrarMinimo(NodoABB* nodo);
    void generarDotRecursivo(NodoABB* nodo, std::ofstream& dotFile);
    void generarReporteRecursivo(NodoABB* nodo, std::ofstream& archivo);
public:
    ArbolBinarioBusqueda();
    ~ArbolBinarioBusqueda();
    void insertar(const Piloto& piloto);
    void inorden();
    void preorden();
    void postorden();
    void eliminarPiloto(int horasDeVuelo);
    void generarReporte(const std::string& nombreArchivo);

};
#endif //PROYECTO2CONTROLAEROPUERTO_ARBOLBINARIO_H