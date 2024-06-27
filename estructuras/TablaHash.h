#ifndef PROYECTO2CONTROLAEROPUERTO_TABLAHASH_H
#define PROYECTO2CONTROLAEROPUERTO_TABLAHASH_H
#include "../Objetos/Avion.h"
#include "../Objetos/Piloto.h"
#include <string>

class NodoHash {
public:
    Piloto dato;
    NodoHash* siguiente;
    NodoHash(const Piloto& piloto);
};

class TablaHash {
private:
    static const int TAMANO_INICIAL = 18;
    NodoHash** tabla;
    int tamanio;
    int elementos;
    int funcionHash(const std::string& id) const;
    void redimensionar();

public:
    TablaHash();
    ~TablaHash();
    void insertar(const Piloto& piloto);
    bool eliminar(const std::string& id);
    Piloto* buscar(const std::string& id);
    void generarReporte(const std::string& nombreArchivo) const;
    void imprimir() const;
    double factorCarga() const;
};
#endif //PROYECTO2CONTROLAEROPUERTO_TABLAHASH_H

