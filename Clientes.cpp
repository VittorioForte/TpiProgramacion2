#include <iostream>
#include <cstring>
#include <limits>
#include <cstdio>
#include "clientes.h"

using namespace std;

namespace {
const char *FILE_CLIENTES = "clientes.dat";
}

Clientes::Clientes() {
    estado = false;
    idCliente = 0;
    nombre[0] = '\0';
    apellido[0] = '\0';
    telefono[0] = '\0';
    dni[0] = '\0';
}

int Clientes::getIdCliente() const { return idCliente; }
const char *Clientes::getNombre() const { return nombre; }
const char *Clientes::getApellido() const { return apellido; }
const char *Clientes::getTelefono() const { return telefono; }
const char *Clientes::getDni() const { return dni; }
bool Clientes::getEstado() const { return estado; }

void Clientes::setIdCliente(int aId) { idCliente = aId; }

void Clientes::setNombre(const char *aNombre) {
    if (aNombre != nullptr) {
        strncpy(nombre, aNombre, sizeof(nombre) - 1);
        nombre[sizeof(nombre) - 1] = '\0';
    }
}

void Clientes::setApellido(const char *aApellido) {
    if (aApellido != nullptr) {
        strncpy(apellido, aApellido, sizeof(apellido) - 1);
        apellido[sizeof(apellido) - 1] = '\0';
    }
}

void Clientes::setTelefono(const char *aTelefono) {
    if (aTelefono != nullptr) {
        strncpy(telefono, aTelefono, sizeof(telefono) - 1);
        telefono[sizeof(telefono) - 1] = '\0';
    }
}

void Clientes::setDni(const char *aDni) {
    if (aDni != nullptr) {
        strncpy(dni, aDni, sizeof(dni) - 1);
        dni[sizeof(dni) - 1] = '\0';
    }
}

void Clientes::setEstado(bool aEstado) { estado = aEstado; }

void Clientes::cargar(int nuevoId) {
    setIdCliente(nuevoId);
    setEstado(true);

    cout << "Nombre: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(nombre, sizeof(nombre));

    cout << "Apellido: ";
    cin.getline(apellido, sizeof(apellido));

    cout << "Telefono: ";
    cin.getline(telefono, sizeof(telefono));

    cout << "DNI: ";
    cin.getline(dni, sizeof(dni));
}

void Clientes::mostrar() const {
    cout << "ID: " << idCliente << "\n";
    cout << "Nombre: " << nombre << "\n";
    cout << "Apellido: " << apellido << "\n";
    cout << "Telefono: " << telefono << "\n";
    cout << "DNI: " << dni << "\n";
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << "\n";
}

bool Clientes::grabarEnDisco() const {
    FILE *p = fopen(FILE_CLIENTES, "ab");
    if (p == nullptr) {
        return false;
    }
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Clientes::leerDeDisco(int pos) {
    FILE *p = fopen(FILE_CLIENTES, "rb");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fread(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Clientes::modificarEnDisco(int pos) const {
    FILE *p = fopen(FILE_CLIENTES, "rb+");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

void menuClientes() {
    cout << "Menu de clientes\n";
}
