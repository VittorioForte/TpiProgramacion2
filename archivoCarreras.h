#pragma once

#include <string>
#include "Carrera.h"

class ArchivoCarreras {
private:
    std::string _nombreArchivo;

public:
    ArchivoCarreras(std::string nombreArchivo);
    bool Guardar(Carrera);
    bool Guardar(Carrera, int);
    int Buscar(int);
    Carrera Leer(int);
    int CantidadRegistros();
    void Leer(int cantidadRegistros, Carrera *vector);
};

