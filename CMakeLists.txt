cmake_minimum_required(VERSION 3.28)
project(Proyecto2ControlAeropuerto)

set(CMAKE_CXX_STANDARD 17)

add_executable(Proyecto2ControlAeropuerto main.cpp
        reportes/Reportes.cpp
        reportes/Reportes.h
        Objetos/Avion.cpp
        Objetos/Avion.h
        Objetos/Piloto.cpp
        Objetos/Piloto.h
        Objetos/Ruta.cpp
        Objetos/Ruta.h
        estructuras/ArbolB.cpp
        estructuras/ArbolB.h
        estructuras/ListaCircularDoble.cpp
        estructuras/ListaCircularDoble.h
        estructuras/ArbolBinarioBusqueda.cpp
        estructuras/ArbolBinarioBusqueda.h
        estructuras/TablaHash.cpp
        estructuras/TablaHash.h
        estructuras/MatrizDispersa.cpp
        estructuras/MatrizDispersa.h
        estructuras/Grafo.cpp
        estructuras/Grafo.h)
