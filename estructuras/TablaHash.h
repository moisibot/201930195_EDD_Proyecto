#ifndef PROYECTO2CONTROLAEROPUERTO_TABLAHASH_H
#define PROYECTO2CONTROLAEROPUERTO_TABLAHASH_H
#include "../Objetos/Avion.h"
#include "../Objetos/Piloto.h"
#include <string>
#include <iostream>
class NodoHash {
public:
    Piloto dato;
    NodoHash* siguiente;
    NodoHash(const Piloto& piloto);
};
class TablaHash {
private:
    NodoHash** tabla;
    int tamanio;
    int elementos;
    int funcionHash(const std::string& id);
    void redimensionar();
public:
    TablaHash(int tamanioInicial = 37);
    ~TablaHash();
    void insertar(const Piloto& piloto);
    bool eliminar(const std::string& id);
    Piloto* buscar(const std::string& id);
    void generarReporte(const std::string& nombreArchivo);
    void imprimir();
};
#endif //PROYECTO2CONTROLAEROPUERTO_TABLAHASH_H

