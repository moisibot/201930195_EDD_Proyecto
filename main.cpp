#include <iostream>
#include <fstream>
#include <sstream>
#include "nlohmann/json.hpp"
#include "estructuras/ArbolB.h"
#include "estructuras/ArbolBinarioBusqueda.h"
#include "estructuras/TablaHash.h"
#include "estructuras/Grafo.h"
#include "estructuras/ListaCircularDoble.h"
#include "reportes/Reportes.h"

using json = nlohmann::json;

void cargarAviones(const std::string& nombreArchivo, ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento, MatrizDispersa& matrizVuelos) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de aviones abierto correctamente." << std::endl;
    json jsonData;
    archivo >> jsonData;
    for (const auto& avionJson : jsonData) {
        Avion avion(
                avionJson["vuelo"],
                avionJson["numero_de_registro"],
                avionJson["modelo"],
                avionJson["capacidad"],
                avionJson["aerolinea"],
                avionJson["ciudad_destino"],
                avionJson["estado"]
        );
        if (avion.getEstado() == "Disponible") {
            arbolAviones.insertar(avion);
            matrizVuelos.insertar(avion.getVuelo(), avion.getCiudadDestino(), nullptr, 0);
        } else if (avion.getEstado() == "Mantenimiento") {
            listaMantenimiento.insertar(avion);
        }
    }
}

void cargarPilotos(const std::string& nombreArchivo, ArbolBinarioBusqueda& arbolPilotos, TablaHash& tablaPilotos, MatrizDispersa& matrizVuelos) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de pilotos abierto correctamente." << std::endl;
    json jsonData;
    archivo >> jsonData;
    for (const auto &pilotoJson: jsonData) {
        Piloto piloto(
                pilotoJson["nombre"],
                pilotoJson["nacionalidad"],
                pilotoJson["numero_de_id"],
                pilotoJson["vuelo"],
                pilotoJson["horas_de_vuelo"],
                pilotoJson["tipo_de_licencia"]
        );
        arbolPilotos.insertar(piloto);
        tablaPilotos.insertar(piloto);
        Piloto *pilotoPtr = tablaPilotos.buscar(piloto.getNumeroDeId());
        if (pilotoPtr) {
            NodoMatriz *nodo = matrizVuelos.obtener(piloto.getVuelo(), "");
            if (nodo) {
                nodo->piloto = pilotoPtr;
            }
        }
        std::cout << "Pilotos cargados exitosamente." << std::endl;
    }
}

void cargarRutas(const std::string& nombreArchivo, Grafo& grafoRutas, MatrizDispersa& matrizVuelos) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de rutas abierto correctamente." << std::endl;
    std::string linea;
    while (std::getline(archivo, linea)) {
        std::istringstream iss(linea);
        std::string origen, destino, distanciaStr;
        std::getline(iss, origen, '/');
        std::getline(iss, destino, '/');
        std::getline(iss, distanciaStr, ';');
        int distancia = std::stoi(distanciaStr);
        Ruta ruta(origen, destino, distancia);
        grafoRutas.agregarRuta(ruta);
       // Ruta rutaInversa(destino, origen, distancia);
        //grafoRutas.agregarRuta(rutaInversa);
        NodoMatriz* nodo = matrizVuelos.obtener("", destino);
        if (nodo) {
            nodo->distancia = distancia;
        }
    }
    archivo.close();
    std::cout << "Carga de rutas completada." << std::endl;
}

void procesarMovimientos(const std::string& nombreArchivo, ArbolB& arbolAviones, ListaCircularDoble& listaMantenimiento, ArbolBinarioBusqueda& arbolPilotos, MatrizDispersa& matrizVuelos, TablaHash& tablaPilotos) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }
    std::cout << "Archivo de movimientos abierto correctamente." << std::endl;

    std::string linea;
    while (std::getline(archivo, linea)) {
        // Eliminar espacios en blanco al inicio y al final de la línea
        linea.erase(0, linea.find_first_not_of(" \t"));
        linea.erase(linea.find_last_not_of(" \t;") + 1);

        if (linea.find("MantenimientoAviones,Ingreso,") == 0) {
            std::cout << "Comando de ingreso de aviones detectado." << std::endl;
            std::string numeroRegistro = linea.substr(29);
            numeroRegistro.erase(0, numeroRegistro.find_first_not_of(" \t"));
            numeroRegistro.erase(numeroRegistro.find_last_not_of(" \t;") + 1);

            Avion* avion = arbolAviones.buscarYEliminar(numeroRegistro);
            if (avion) {
                std::cout << "Avión " << numeroRegistro << " encontrado en ArbolB. Moviendo a mantenimiento." << std::endl;
                avion->setEstado("Mantenimiento");
                listaMantenimiento.insertar(*avion);
                delete avion;
            } else if (listaMantenimiento.buscarYEliminar(numeroRegistro)) {
                std::cout << "El avión " << numeroRegistro << " ya está en mantenimiento." << std::endl;
            } else {
                std::cout << "El avión " << numeroRegistro << " no se encontró en la lista de disponibles ni en mantenimiento." << std::endl;
            }
        } else if (linea.find("MantenimientoAviones,Salida,") == 0) {
            std::cout << "Comando de salida de aviones detectado." << std::endl;
            std::string numeroRegistro = linea.substr(28);
            numeroRegistro.erase(0, numeroRegistro.find_first_not_of(" \t"));
            numeroRegistro.erase(numeroRegistro.find_last_not_of(" \t;") + 1);

            Avion* avion = listaMantenimiento.buscarYEliminar(numeroRegistro);
            if (avion) {
                std::cout << "Avión " << numeroRegistro << " encontrado en ListaCircularDoble. Moviendo a disponibles." << std::endl;
                avion->setEstado("Disponible");
                arbolAviones.insertar(*avion);
                delete avion;
            } else if (arbolAviones.buscarYEliminar(numeroRegistro)) {
                std::cout << "El avión " << numeroRegistro << " ya está disponible." << std::endl;
            } else {
                std::cout << "El avión " << numeroRegistro << " no se encontró en mantenimiento ni en disponibles." << std::endl;
            }
        } else if (linea.find("DarDeBaja") != std::string::npos) {
            size_t inicio = linea.find('(') + 1;
            size_t fin = linea.find(')');
            if (inicio != std::string::npos && fin != std::string::npos && inicio < fin) {
                std::string numeroRegistro = linea.substr(inicio, fin - inicio);
                std::cout << "Dando de baja al piloto: " << numeroRegistro << std::endl;
                arbolPilotos.eliminar(numeroRegistro);
                matrizVuelos.eliminarPiloto(numeroRegistro);
                tablaPilotos.eliminar(numeroRegistro);
                std::cout << "Piloto " << numeroRegistro << " dado de baja y eliminado de todas las estructuras." << std::endl;
            } else {
                std::cout << "Formato inválido para DarDeBaja: " << linea << std::endl;
            }
        } else {
            std::cout << "Comando no reconocido: " << linea << std::endl;
        }
    }
    archivo.close();
}
void generarImagenDesdeArchivoDot(const std::string& archivoEntrada, const std::string& archivoSalida, const std::string& formato) {
    std::string comando = "dot -T" + formato + " -o " + archivoSalida + " " + archivoEntrada;
    int resultado = std::system(comando.c_str());
    if (resultado != 0) {
        std::cout << "Error al generar la imagen desde el archivo dot." << std::endl;
    } else {
        std::cout << "Imagen generada correctamente: " << archivoSalida << std::endl;
    }
}
void mostrarMenuRecorrido(ArbolBinarioBusqueda& arbolPilotos) {
    int opcion;
    do {
        std::cout << "\n---- Seleccione el recorrido ----" << std::endl;
        std::cout << "1. Preorden" << std::endl;
        std::cout << "2. Inorder" << std::endl;
        std::cout << "3. Postorden" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Recorrido Preorden:" << std::endl;
                arbolPilotos.preorden();
                break;
            case 2:
                std::cout << "Recorrido Inorden:" << std::endl;
                arbolPilotos.inorden();
                break;
            case 3:
                std::cout << "Recorrido Postorden:" << std::endl;
                arbolPilotos.postorden();
                break;
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 0);
}

void mostrarMenu() {
    std::cout << "=== Sistema de Gestión de Aeropuerto ===" << std::endl;
    std::cout << "1. Cargar aviones" << std::endl;
    std::cout << "2. Cargar pilotos" << std::endl;
    std::cout << "3. Cargar rutas" << std::endl;
    std::cout << "4. Cargar movimientos" << std::endl;
    std::cout << "5. Consultar horas de vuelo (pilotos)" << std::endl;
    std::cout << "6. Recomendar ruta más corta" << std::endl;
    std::cout << "7. Generar reportes" << std::endl;
    std::cout << "8. Ver recorridos" << std::endl;
    std::cout << "9. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}

int main() {
    ArbolB arbolAviones(4);
    ArbolBinarioBusqueda arbol;
    ListaCircularDoble listaMantenimiento;
    ArbolBinarioBusqueda arbolPilotos;
    TablaHash tablaPilotos;
    Grafo grafoRutas;
    MatrizDispersa matrizVuelos;
    std::string origen, destino;

    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;

        switch(opcion) {
            case 1:
                cargarAviones("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/aviones.json", arbolAviones,
                              listaMantenimiento, matrizVuelos);
                break;
            case 2:
                cargarPilotos("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/pilotos.json", arbolPilotos,
                              tablaPilotos, matrizVuelos);
                break;3;
            case 3:
                cargarRutas("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/rutas.txt", grafoRutas, matrizVuelos);
                //grafoRutas.imprimirGrafo();
                break;
            case 4:
                procesarMovimientos("/home/moisibot/CLionProjects/Proyecto2ControlAeropuerto/movimientos.txt",
                                    arbolAviones, listaMantenimiento, arbolPilotos, matrizVuelos, tablaPilotos);
                break;
            case 5:
                std::cout << "Horas de vuelo de los pilotos:" << std::endl;
                arbolPilotos.preorden();
                break;
            case 6:
                std::cout << "Ingrese la ciudad de origen: ";
                std::cin >> origen;
                std::cout << "Ingrese la ciudad de destino: ";
                std::cin >> destino;
                grafoRutas.dijkstra(origen, destino);
                break;
            case 7:
                int opcionReportes;
                do {
                    std::cout << "=== Menú de Reportes ===" << std::endl;
                    std::cout << "1. Generar reporte de árbol B con aviones disponibles" << std::endl;
                    std::cout << "2. Generar reporte de lista de aviones en mantenimiento" << std::endl;
                    std::cout << "3. Generar reporte de árbol binario de búsqueda con horas de vuelo de pilotos" << std::endl;
                    std::cout << "4. Generar reporte de tabla hash de pilotos" << std::endl;
                    std::cout << "5. Generar reporte de grafo dirigido de rutas" << std::endl;
                    std::cout << "6. Generar reporte de matriz dispersa de vuelos y ciudades" << std::endl;
                    std::cout << "7. Regresar al menú principal" << std::endl;
                    std::cin >> opcionReportes;
                    Reportes reportes;
                    switch (opcionReportes) {
                        case 1:
                            arbolAviones.generarReporte("arbol_b_disponibles.dot");
                            std::cout << "Reporte del árbol generado como 'arbol_b_disponibles.png'" << std::endl;
                            break;
                        case 2:
                            listaMantenimiento.generarReporte("lista_mantenimiento.dot");
                            std::cout << "Reporte del árbol generado como 'lista_mantenimiento.png'" << std::endl;
                            break;
                        case 3:
                            arbolPilotos.generarReporte("reporte_arbol.dot");
                            std::cout << "Reporte del árbol generado como 'arbol_binario.png'" << std::endl;
                            break;
                        case 4:
                            tablaPilotos.generarReporte("reporte_tabla_hash_pilotos.dot");
                            std::cout << "Reporte de la tabla hash de pilotos generado como 'tabla_hash_pilotos.png'" << std::endl;
                            break;
                        case 5:
                            grafoRutas.generarReporte("grafoRutas.dot");
                            std::cout << "Reporte de la tabla hash de pilotos generado como 'grafoRutas.png'" << std::endl;
                            break;
                        case 6:
                            matrizVuelos.imprimir();
                            matrizVuelos.generarReporte("matrizVuelos.dot");
                            std::cout << "Reporte de matriz vuelos generado como 'matrizVuelos.png'" << std::endl;
                            break;
                        case 7:
                            std::cout << "Regresando al menú principal..." << std::endl;
                            break;
                        default:
                            std::cout << "Opción inválida. Intente de nuevo." << std::endl;
                            break;
                    }
                } while (opcionReportes != 7);
                break;
            case 8:
                mostrarMenuRecorrido(arbolPilotos);
                break;
            case 9:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo." << std::endl;
        }
    } while (opcion != 9);
    return 0;
}
