#include <iostream>
#include <iomanip>
#include "fecha.h"

using namespace std;

Fecha::Fecha() {
    dia = 1;
    mes = 1;
    anio = 2000;
}

Fecha::Fecha(int aDia, int aMes, int aAnio) {
    setDia(aDia);
    setMes(aMes);
    setAnio(aAnio);
}

int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int aDia) {
    if (aDia >= 1 && aDia <= 31) {
        dia = aDia;
    }
}

void Fecha::setMes(int aMes) {
    if (aMes >= 1 && aMes <= 12) {
        mes = aMes;
    }
}

void Fecha::setAnio(int aAnio) {
    if (aAnio >= 1900) {
        anio = aAnio;
    }
}

void Fecha::cargar() {
    cout << "Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
}

void Fecha::mostrar() const {
    cout << setfill('0') << setw(2) << dia << '/'
         << setw(2) << mes << '/' << setw(4) << anio << setfill(' ') << '\n';
}
