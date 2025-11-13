#pragma once

#include <string>
#include "Pago.h"

class ArchivoPagos {
private:
    std::string _nombreArchivo;

public:
    ArchivoPagos(const std::string& nombreArchivo);
    bool Guardar(Pago reg);
    bool Guardar(Pago reg, int pos);
    Pago Leer(int pos);
    int BuscarPorCarrera(int idCarrera);
    int BuscarPorId(int idPago);
    int CantidadRegistros();
    void Leer(int cantidadRegistros, Pago* vector);
};

