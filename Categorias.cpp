#include "Categorias.h"
#include <cstring>
#include <iostream>
using namespace std;

Categorias::Categorias() {
    _estado = false;
    _idCategoria = 0;
    _cantVueltas = 0;
    strcpy(_nombreCat, "");
}

Categorias::Categorias(int idCategoria, int cantVueltas, bool estado, string nombreCat) {
    setIdCategoria(idCategoria);
    setCantVueltas(cantVueltas);
    setEstado(estado);
    setNombreCat(nombreCat);
}

// GETTERS
bool Categorias::getEstado() const { return _estado; }
int Categorias::getIdCategoria() const { return _idCategoria; }
int Categorias::getCantVueltas() const { return _cantVueltas; }
const char* Categorias::getNombreCat() const { return _nombreCat; }
int Categorias::getPrecio() const { return _precio; }

// SETTERS
void Categorias::setEstado(bool estado) { _estado = estado; }
void Categorias::setIdCategoria(int idCategoria) { _idCategoria = idCategoria; }
void Categorias::setCantVueltas(int cantVueltas) { _cantVueltas = cantVueltas; }

void Categorias::setNombreCat(string nombreCat) {
    strncpy(_nombreCat, nombreCat.c_str(), 29);
    _nombreCat[29] = '\0';

    if (nombreCat == "PROFESIONAL") {
        _cantVueltas = 20;
        _idCategoria = 1;
        _estado = true;
        _precio = 135000;
    }
    else if (nombreCat == "AMATEUR") {
        _cantVueltas = 15;
        _idCategoria = 2;
        _estado = true;
        _precio = 100000;
    }
    else if (nombreCat == "INFANTIL") {
        _cantVueltas = 10;
        _idCategoria = 3;
        _estado = true;
        _precio = 85000;
    }
    else {
        _cantVueltas = 0;
        _idCategoria = 0;
        _estado = false;
    }
}

// MÉTODOS
void Categorias::cargar() {
    cout << "Ingrese nombre de categoria en mayuscula (PROFESIONAL / AMATEUR / INFANTIL): ";
    string tempNombre;

    cin >> tempNombre;
    setNombreCat(tempNombre);

    if (!_estado) {
        cout << "Categoria no valida..." << endl;
    }
}

void Categorias::mostrar() const {
    cout << "--------------------------------" << endl;
    cout << "ID Categoria: " << _idCategoria << endl;
    cout << "Nombre: " << _nombreCat << endl;
    cout << "Cantidad de vueltas: " << _cantVueltas << endl;
    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;
}
