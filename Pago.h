#pragma once

#include "Fecha.h"

class Pago {
private:
    int _idPago;
    int _idCarrera;
    int _idCliente;
    double _monto;
    bool _pagado;
    Fecha _fechaPago;

public:
    Pago();

    int getIdPago() const;
    int getIdCarrera() const;
    int getIdCliente() const;
    double getMonto() const;
    bool getPagado() const;
    Fecha getFechaPago() const;

    void setIdPago(int idPago);
    void setIdCarrera(int idCarrera);
    void setIdCliente(int idCliente);
    void setMonto(double monto);
    void setPagado(bool pagado);
    void setFechaPago(const Fecha& fechaPago);
};

