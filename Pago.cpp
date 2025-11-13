#include <iostream>
#include <iomanip>
#include "Pago.h"

using namespace std;

Pago::Pago() {
    _idPago = 0;
    _idCarrera = 0;
    _idCliente = 0;
    _monto = 0.0;
    _pagado = false;
    _estado = true;
}

void Pago::setIdPago(int idPago) { _idPago = idPago; }
void Pago::setIdCarrera(int idCarrera) { _idCarrera = idCarrera; }
void Pago::setIdCliente(int idCliente) { _idCliente = idCliente; }
void Pago::setMonto(double monto) { _monto = monto; }
void Pago::setPagado(bool pagado) { _pagado = pagado; }
void Pago::setEstado(bool estado) { _estado = estado; }

int Pago::getIdPago() const { return _idPago; }
int Pago::getIdCarrera() const { return _idCarrera; }
int Pago::getIdCliente() const { return _idCliente; }
double Pago::getMonto() const { return _monto; }
bool Pago::getPagado() const { return _pagado; }
bool Pago::getEstado() const { return _estado; }

void Pago::mostrar() const {
    if (!_estado) return;
    cout << fixed << setprecision(2);
    cout << "ID Pago: " << _idPago << endl;
    cout << "ID Carrera: " << _idCarrera << endl;
    cout << "ID Cliente: " << _idCliente << endl;
    cout << "Monto: $" << _monto << endl;
    cout << "Estado: " << (_pagado ? "PAGADO" : "PENDIENTE") << endl;
}

