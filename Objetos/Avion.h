#ifndef PROYECTO2CONTROLAEROPUERTO_AVION_H
#define PROYECTO2CONTROLAEROPUERTO_AVION_H
#include <string>
class Avion {
private:
    std::string vuelo;
    std::string numero_de_registro;
    std::string modelo;
    int capacidad;
    std::string aerolinea;
    std::string ciudad_destino;
    std::string estado;
public:
    Avion();
    Avion(const std::string& vuelo, const std::string& numero_de_registro, const std::string& modelo,
          int capacidad, const std::string& aerolinea, const std::string& ciudad_destino, const std::string& estado);

    std::string getVuelo() const;
    std::string getNumeroDeRegistro() const;
    std::string getModelo() const;
    int getCapacidad() const;
    std::string getAerolinea() const;
    std::string getCiudadDestino() const;
    std::string getEstado() const;

    void setVuelo(const std::string& vuelo);
    void setNumeroDeRegistro(const std::string& numero_de_registro);
    void setModelo(const std::string& modelo);
    void setCapacidad(int capacidad);
    void setAerolinea(const std::string& aerolinea);
    void setCiudadDestino(const std::string& ciudad_destino);
    void setEstado(const std::string& estado);
};
#endif //PROYECTO2CONTROLAEROPUERTO_AVION_H
