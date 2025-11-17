#pragma once

#include "Fecha.h"
#include "ArchivoCarreras.h"
#include "ArchivoClientes.h"

class Pago {
private:
    int _idPago;
    int _idCarrera;
    int _idCliente;
    int _monto;
    bool _estado;
    Fecha _fechaPago;

public:
    Pago();

    int getIdPago() const;
    int getIdCarrera() const;
    int getIdCliente() const;
    int getMonto() const;
    bool getEstado() const;
    Fecha getFechaPago() const;

    void setIdPago(int idPago);
    void setIdCarrera(int idCarrera);
    void setIdCliente(int idCliente);
    void setMonto(int monto);
    void setEstado(bool estado);
    void setFechaPago(const Fecha& fechaPago);

    void mostrar(int fila, ArchivoCarreras& archCarreras, ArchivoClientes& archClientes) const;
};

