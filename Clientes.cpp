#include <iostream>
#include <cstring>
#include "Clientes.h"
using namespace std;

Cliente::Cliente() {
    _idCliente = 0;
    strcpy(_nombre, "");
    strcpy(_apellido, "");
    strcpy(_telefono, "");
    _dni = 0;
    _estado = true;
}

void Cliente::cargar() {
    cout << "Ingrese nombre: ";
    cin.ignore();
    cin.getline(_nombre, 30);
    cout << "Ingrese apellido: ";
    cin.getline(_apellido, 30);
    cout << "Ingrese telefono: ";
    cin.getline(_telefono, 20);
    cout << "Ingrese DNI: ";
    cin >> _dni;
    _estado = true;
}

void Cliente::mostrar() const {
    if (!_estado) return;
    cout << "--------------------------------" << endl;
    cout << "ID: " << _idCliente << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Telefono: " << _telefono << endl;
    cout << "DNI: " << _dni << endl;
}

// Getters
int Cliente::getIdCliente() const { return _idCliente; }
int Cliente::getDni() const { return _dni; }
const char* Cliente::getNombre() const { return _nombre; }
const char* Cliente::getApellido() const { return _apellido; }
bool Cliente::getEstado() const { return _estado; }

// Setters
void Cliente::setEstado(bool estado) {
    _estado = estado; // _miembro = parametro
}

void Cliente::setIdCliente(int idCliente) {
    _idCliente = idCliente; // _miembro = parametro
}
