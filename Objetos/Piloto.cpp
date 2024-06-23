#include "Piloto.h"
Piloto::Piloto() : horas_de_vuelo(0) {}
Piloto::Piloto(const std::string& nombre, const std::string& nacionalidad, const std::string& numero_de_id,
               const std::string& vuelo, int horas_de_vuelo, const std::string& tipo_de_licencia)
        : nombre(nombre), nacionalidad(nacionalidad), numero_de_id(numero_de_id),
          vuelo(vuelo), horas_de_vuelo(horas_de_vuelo), tipo_de_licencia(tipo_de_licencia) {}

std::string Piloto::getNombre() const { return nombre; }
std::string Piloto::getNacionalidad() const { return nacionalidad; }
std::string Piloto::getNumeroDeId() const { return numero_de_id; }
std::string Piloto::getVuelo() const { return vuelo; }
int Piloto::getHorasDeVuelo() const { return horas_de_vuelo; }
std::string Piloto::getTipoDeLicencia() const { return tipo_de_licencia; }

void Piloto::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Piloto::setNacionalidad(const std::string& nacionalidad) { this->nacionalidad = nacionalidad; }
void Piloto::setNumeroDeId(const std::string& numero_de_id) { this->numero_de_id = numero_de_id; }
void Piloto::setVuelo(const std::string& vuelo) { this->vuelo = vuelo; }
void Piloto::setHorasDeVuelo(int horas_de_vuelo) { this->horas_de_vuelo = horas_de_vuelo; }
void Piloto::setTipoDeLicencia(const std::string& tipo_de_licencia) { this->tipo_de_licencia = tipo_de_licencia; }