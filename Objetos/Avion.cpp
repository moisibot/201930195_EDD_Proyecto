#include "Avion.h"

Avion::Avion() : capacidad(0) {}

Avion::Avion(const std::string& vuelo, const std::string& numero_de_registro, const std::string& modelo,
             int capacidad, const std::string& aerolinea, const std::string& ciudad_destino, const std::string& estado)
        : vuelo(vuelo), numero_de_registro(numero_de_registro), modelo(modelo), capacidad(capacidad),
          aerolinea(aerolinea), ciudad_destino(ciudad_destino), estado(estado) {}

std::string Avion::getVuelo() const { return vuelo; }
std::string Avion::getNumeroDeRegistro() const { return numero_de_registro; }
std::string Avion::getModelo() const { return modelo; }
int Avion::getCapacidad() const { return capacidad; }
std::string Avion::getAerolinea() const { return aerolinea; }
std::string Avion::getCiudadDestino() const { return ciudad_destino; }
std::string Avion::getEstado() const { return estado; }

void Avion::setVuelo(const std::string& vuelo) { this->vuelo = vuelo; }
void Avion::setNumeroDeRegistro(const std::string& numero_de_registro) { this->numero_de_registro = numero_de_registro; }
void Avion::setModelo(const std::string& modelo) { this->modelo = modelo; }
void Avion::setCapacidad(int capacidad) { this->capacidad = capacidad; }
void Avion::setAerolinea(const std::string& aerolinea) { this->aerolinea = aerolinea; }
void Avion::setCiudadDestino(const std::string& ciudad_destino) { this->ciudad_destino = ciudad_destino; }
void Avion::setEstado(const std::string& estado) { this->estado = estado; }