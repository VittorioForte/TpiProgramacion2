#include <iostream>
#include <cstring>
#include "Clientes.h"
using namespace std;

void Cliente::cargar() {
    cout << "Ingrese nombre: ";
    cin.ignore();
    cin.getline(nombre, 30);
    cout << "Ingrese apellido: ";
    cin.getline(apellido, 30);
    cout << "Ingrese telefono: ";
    cin.getline(telefono, 20);
    cout << "Ingrese DNI: ";
    cin >> dni;
    estado = true;
}

void Cliente::mostrar() const {
    if (!estado) return;
    cout << "--------------------------------\n";
    cout << "ID: " << idCliente << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "DNI: " << dni << endl;
}
