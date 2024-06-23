#include "Ruta.h"
#include <sstream>
Ruta::Ruta() : distancia_de_ruta(0) {}
Ruta::Ruta(const std::string& origen, const std::string& destino, int distancia_de_ruta)
        : origen(origen), destino(destino), distancia_de_ruta(distancia_de_ruta) {}

std::string Ruta::getOrigen() const { return origen; }
std::string Ruta::getDestino() const { return destino; }
int Ruta::getDistanciaDeRuta() const { return distancia_de_ruta; }

void Ruta::setOrigen(const std::string& origen) { this->origen = origen; }
void Ruta::setDestino(const std::string& destino) { this->destino = destino; }
void Ruta::setDistanciaDeRuta(int distancia_de_ruta) { this->distancia_de_ruta = distancia_de_ruta; }

Ruta Ruta::fromString(const std::string& line) {
    std::istringstream iss(line);
    std::string origen, destino, distancia_str;
    std::getline(iss, origen, '/');
    std::getline(iss, destino, '/');
    std::getline(iss, distancia_str, ';');

    int distancia = std::stoi(distancia_str);
    return Ruta(origen, destino, distancia);
}

std::string Ruta::toString() const {
    return origen + "/" + destino + "/" + std::to_string(distancia_de_ruta) + ";";
}