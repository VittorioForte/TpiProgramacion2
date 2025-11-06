#ifndef ARCHIVOCARRERAS_H_INCLUDED
#define ARCHIVOCARRERAS_H_INCLUDED

#include <string>
#include "Carrera.h"

class ArchivoCarreras {
private:
    std::string _nombreArchivo;

public:
    ArchivoCarreras(std::string nombreArchivo);

    bool Guardar(const Carrera &c);
    Carrera Leer(int pos);
    int CantidadRegistros();
};

#endif // ARCHIVOCARRERAS_H_INCLUDED
