#include "Fecha.h"
#include <iostream>
using namespace std;

Fecha::Fecha() {
    _dia = 0;
    _mes = 0;
    _anio = 0;
}

Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
}


void Fecha::Cargar() {
    cout << "Ingrese Dia: ";
    cin >> _dia;
    cout << "Ingrese Mes: ";
    cin >> _mes;
    cout << "Ingrese Anio: ";
    cin >> _anio;
}

std::string Fecha::toString() const {
    return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio);
}

// Getters
int Fecha::getDia() const { return _dia; }
int Fecha::getMes() const { return _mes; }
int Fecha::getAnio() const { return _anio; }

// Setters
void Fecha::setDia(int dia) { _dia = dia; }
void Fecha::setMes(int mes) { _mes = mes; }
void Fecha::setAnio(int anio) { _anio = anio; }
