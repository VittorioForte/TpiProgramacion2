#include "Pago.h"

Pago::Pago() {
    _idPago = 0;
    _idCarrera = 0;
    _idCliente = 0;
    _monto = 0;
    _pagado = false;
    _fechaPago = Fecha();
}

int Pago::getIdPago() const { return _idPago; }
int Pago::getIdCarrera() const { return _idCarrera; }
int Pago::getIdCliente() const { return _idCliente; }
double Pago::getMonto() const { return _monto; }
bool Pago::getPagado() const { return _pagado; }
Fecha Pago::getFechaPago() const { return _fechaPago; }

void Pago::setIdPago(int idPago) { _idPago = idPago; }
void Pago::setIdCarrera(int idCarrera) { _idCarrera = idCarrera; }
void Pago::setIdCliente(int idCliente) { _idCliente = idCliente; }
void Pago::setMonto(double monto) { _monto = monto; }
void Pago::setPagado(bool pagado) { _pagado = pagado; }
void Pago::setFechaPago(const Fecha& fechaPago) { _fechaPago = fechaPago; }

