#ifndef PROYECTO2CONTROLAEROPUERTO_RUTA_H
#define PROYECTO2CONTROLAEROPUERTO_RUTA_H
#include <string>
class Ruta {
private:
    std::string origen;
    std::string destino;
    int distancia_de_ruta;
public:
    Ruta();
    Ruta(const std::string& origen, const std::string& destino, int distancia_de_ruta);
    std::string getOrigen() const;
    std::string getDestino() const;
    int getDistanciaDeRuta() const;
    void setOrigen(const std::string& origen);
    void setDestino(const std::string& destino);
    void setDistanciaDeRuta(int distancia_de_ruta);
    static Ruta fromString(const std::string& line);
    std::string toString() const;
};
#endif //PROYECTO2CONTROLAEROPUERTO_RUTA_H
