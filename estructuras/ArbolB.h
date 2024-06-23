#ifndef PROYECTO2CONTROLAEROPUERTO_ARBOLB_H
#define PROYECTO2CONTROLAEROPUERTO_ARBOLB_H
#include "../Objetos/Avion.h"
#include <iostream>
class NodoB {
public:
    Avion* claves;
    NodoB** hijos;
    int numClaves;
    bool esHoja;
    NodoB(int t);
    ~NodoB();
};
class ArbolB {
private:
    NodoB* raiz;
    int t;  // Grado mínimo del árbol B
    void dividirHijo(NodoB* padre, int indice, NodoB* hijo);
    void insertarNoLleno(NodoB* nodo, const Avion& avion);
    void liberarMemoriaRecursiva(NodoB* nodo);
public:
    void generarReporte(const std::string &nombreArchivo);
    ArbolB(int t);
    ~ArbolB();
    void insertar(const Avion& avion);
    void imprimirArbol();
private:
    void imprimirNodo(NodoB* nodo, int nivel);
     void generarReporteRecursivo(NodoB *nodo, std::ofstream &archivo);
};
#endif //PROYECTO2CONTROLAEROPUERTO_ARBOLB_H