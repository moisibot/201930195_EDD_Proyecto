#ifndef PROYECTO2CONTROLAEROPUERTO_LISTACIRCULARDOBLE_H
#define PROYECTO2CONTROLAEROPUERTO_LISTACIRCULARDOBLE_H
#include "../Objetos/Avion.h"
#include <iostream>

class NodoLCD {
public:
    Avion dato;
    NodoLCD* siguiente;
    NodoLCD* anterior;
    NodoLCD(const Avion& avion);
};

class ListaCircularDoble {
private:
    NodoLCD* cabeza;
public:
    ListaCircularDoble();
    ~ListaCircularDoble();
    void insertar(const Avion& avion);
    bool eliminar(const std::string& numeroRegistro);
    void imprimir();
    void generarReporte(const std::string& nombreArchivo);
    Avion* buscarYEliminar(const std::string& numeroRegistro);
};

#endif //PROYECTO2CONTROLAEROPUERTO_LISTACIRCULARDOBLE_H