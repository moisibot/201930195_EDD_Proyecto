#ifndef PROYECTO2CONTROLAEROPUERTO_PILOTO_H
#define PROYECTO2CONTROLAEROPUERTO_PILOTO_H
#include <string>
class Piloto {
private:
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_id;
    std::string vuelo;
    int horas_de_vuelo;
    std::string tipo_de_licencia;
public:
    Piloto();
    Piloto(const std::string& nombre, const std::string& nacionalidad, const std::string& numero_de_id,
           const std::string& vuelo, int horas_de_vuelo, const std::string& tipo_de_licencia);

    std::string getNombre() const;
    std::string getNacionalidad() const;
    std::string getNumeroDeId() const;
    std::string getVuelo() const;
    int getHorasDeVuelo() const;
    std::string getTipoDeLicencia() const;

    void setNombre(const std::string& nombre);
    void setNacionalidad(const std::string& nacionalidad);
    void setNumeroDeId(const std::string& numero_de_id);
    void setVuelo(const std::string& vuelo);
    void setHorasDeVuelo(int horas_de_vuelo);
    void setTipoDeLicencia(const std::string& tipo_de_licencia);
};
#endif //PROYECTO2CONTROLAEROPUERTO_PILOTO_H
