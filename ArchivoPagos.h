#pragma once

#include <string>
#include "Pago.h"

class ArchivoPagos {
private:
    std::string _nombreArchivo;

public:
    ArchivoPagos(std::string nombreArchivo);

    bool Guardar(Pago pago);
    bool Guardar(Pago pago, int posicion);
    Pago Leer(int posicion);
    int BuscarPorCarrera(int idCarrera);
    int CantidadRegistros();
};

