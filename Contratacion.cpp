#include <iostream>
#include <cstdio>
#include <iomanip>
#include "contratacion.h"

using namespace std;

namespace {
const char *FILE_CONTRATACIONES = "contrataciones.dat";
}

Contratacion::Contratacion() {
    estado = false;
    idContratacion = 0;
    idCliente = 0;
    idCarrera = 0;
    monto = 0.0f;
}

bool Contratacion::getEstado() const { return estado; }
int Contratacion::getIdContratacion() const { return idContratacion; }
int Contratacion::getIdCliente() const { return idCliente; }
int Contratacion::getIdCarrera() const { return idCarrera; }
float Contratacion::getMonto() const { return monto; }
Fecha Contratacion::getFechaPago() const { return fechaPago; }

void Contratacion::setEstado(bool aEstado) { estado = aEstado; }
void Contratacion::setIdContratacion(int aIdContratacion) { idContratacion = aIdContratacion; }
void Contratacion::setIdCliente(int aIdCliente) { idCliente = aIdCliente; }
void Contratacion::setIdCarrera(int aIdCarrera) { idCarrera = aIdCarrera; }
void Contratacion::setMonto(float aMonto) { monto = aMonto; }
void Contratacion::setFechaPago(const Fecha &aFecha) { fechaPago = aFecha; }

void Contratacion::cargar(int nuevoId) {
    setEstado(true);
    setIdContratacion(nuevoId);

    cout << "ID del cliente: ";
    cin >> idCliente;

    cout << "ID de la carrera: ";
    cin >> idCarrera;

    cout << "Monto abonado: ";
    cin >> monto;

    cout << "Fecha de pago" << endl;
    fechaPago.cargar();
}

void Contratacion::mostrar() const {
    cout << "Contratacion N°: " << idContratacion << '\n';
    cout << "Cliente: " << idCliente << '\n';
    cout << "Carrera: " << idCarrera << '\n';
    cout << "Monto: $" << fixed << setprecision(2) << monto << '\n';
    cout << "Fecha de pago: ";
    fechaPago.mostrar();
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << "\n";
}

bool Contratacion::grabarEnDisco() const {
    FILE *p = fopen(FILE_CONTRATACIONES, "ab");
    if (p == nullptr) {
        return false;
    }
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Contratacion::leerDeDisco(int pos) {
    FILE *p = fopen(FILE_CONTRATACIONES, "rb");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fread(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Contratacion::modificarEnDisco(int pos) const {
    FILE *p = fopen(FILE_CONTRATACIONES, "rb+");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}
