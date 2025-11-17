#include "Pago.h"
#include "rlutil.h"
#include "Carrera.h"
#include "Clientes.h"
#include <iostream>
#include <string>

using namespace std;

Pago::Pago() {
    _idPago = 0;
    _idCarrera = 0;
    _idCliente = 0;
    _monto = 0;
    _estado = true;
    _fechaPago = Fecha();
}

void Pago::mostrar(int fila, ArchivoCarreras& archCarreras, ArchivoClientes& archClientes) const {
    if (!_estado) return;

    rlutil::locate(1, fila); cout << _idPago;
    rlutil::locate(8, fila); cout << "$" << (int)_monto;
    rlutil::locate(20, fila); cout << _fechaPago.toString();
    rlutil::locate(35, fila);
    int posCarrera = archCarreras.Buscar(_idCarrera);
    if (posCarrera != -1) {
        Carrera c = archCarreras.Leer(posCarrera);
        cout << c.getCategoria().getNombreCat() << " (ID " << _idCarrera << ")";
    } else {
        cout << "Carrera Error";
    }
    rlutil::locate(55, fila);
    int posCliente = archClientes.BuscarPorID(_idCliente);
    if (posCliente != -1) {
        Cliente cli = archClientes.Leer(posCliente);
        string nombre = string(cli.getNombre()) + " " + string(cli.getApellido());
        if (nombre.length() > 20) nombre = nombre.substr(0, 20);
        cout << nombre;
    } else {
        cout << "Cliente Error";
    }
}

int Pago::getIdPago() const { return _idPago; }
int Pago::getIdCarrera() const { return _idCarrera; }
int Pago::getIdCliente() const { return _idCliente; }
int Pago::getMonto() const { return _monto; }
bool Pago::getEstado() const { return _estado; }
Fecha Pago::getFechaPago() const { return _fechaPago; }

void Pago::setIdPago(int idPago) { _idPago = idPago; }
void Pago::setIdCarrera(int idCarrera) { _idCarrera = idCarrera; }
void Pago::setIdCliente(int idCliente) { _idCliente = idCliente; }
void Pago::setMonto(int monto) { _monto = monto; }
void Pago::setEstado(bool estado) { _estado = estado; }
void Pago::setFechaPago(const Fecha& fechaPago) { _fechaPago = fechaPago; }

