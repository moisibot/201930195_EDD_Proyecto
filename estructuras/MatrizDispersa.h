#ifndef PROYECTO2CONTROLAEROPUERTO_MATRIZDISPERSA_H
#define PROYECTO2CONTROLAEROPUERTO_MATRIZDISPERSA_H
#include <iostream>
#include "../Objetos/Piloto.h"
class NodoMatriz {
public:
    std::string vuelo;
    std::string ciudadDestino;
    Piloto* piloto;
    NodoMatriz* derecha;
    NodoMatriz* abajo;
    NodoMatriz(const std::string& vuelo, const std::string& ciudadDestino, Piloto* piloto);
};
class MatrizDispersa {
private:
    NodoMatriz* filas;
    NodoMatriz* columnas;
    NodoMatriz* buscarOCrearFila(const std::string& vuelo);
    NodoMatriz* buscarOCrearColumna(const std::string& ciudadDestino);
public:
    MatrizDispersa();
    ~MatrizDispersa();
    void insertar(const std::string& vuelo, const std::string& ciudadDestino, Piloto* piloto);
    void eliminar(const std::string& vuelo, const std::string& ciudadDestino);
    Piloto* obtener(const std::string& vuelo, const std::string& ciudadDestino);
    void imprimir();
    void generarReporte(const std::string& nombreArchivo);

    void eliminarPiloto(const std::string &pilotoId);
};
#endif //PROYECTO2CONTROLAEROPUERTO_MATRIZDISPERSA_H
