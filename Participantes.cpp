#include "Participantes.h"
#include <iostream>
#include <cstring>
using namespace std;

Participantes::Participantes() {
    strcpy(_nombre, "-VACIO-");
    _horaFinal = 0.0;
    _tiempoVueltas = 0.0;
}

// Setters
void Participantes::setNombre(string nombre) {
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}

void Participantes::setHoraFinal(double horaFinal) {
    _horaFinal = horaFinal;
}

void Participantes::setTiempoVueltas(double tiempoVueltas) {
    _tiempoVueltas = tiempoVueltas;
}

// Getters
const char* Participantes::getNombre() const { return _nombre; }
double Participantes::getHoraFinal() const { return _horaFinal; }
double Participantes::getTiempoVueltas() const { return _tiempoVueltas; }

// Mostrar
void Participantes::mostrarResultado() const {
    cout << _nombre << "\t\t | "
         << _horaFinal << "\t | "
         << _tiempoVueltas << endl;
}
