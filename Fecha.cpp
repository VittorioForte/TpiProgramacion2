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
    while (aDia < 1 || aDia > 31) {
        cout << "Dia invalido. Ingrese nuevamente el dia: ";
        cin >> aDia;
    }
    dia = aDia;
}

void Fecha::setMes(int aMes) {
    while (aMes < 1 || aMes > 12) {
        cout << "Mes invalido. Ingrese nuevamente el mes: ";
        cin >> aMes;
    }
    mes = aMes;
}

void Fecha::setAnio(int aAnio) {
    while (aAnio < 1900) {
        cout << "Anio invalido. Ingrese nuevamente el anio: ";
        cin >> aAnio;
    }
    anio = aAnio;
}


void Fecha::cargar() {
    cout << "Dia: ";
    while (!(cin >> dia) || dia < 1 || dia > 31) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingrese un dia valido (1-31): ";
    }

    cout << "Mes: ";
    while (!(cin >> mes) || mes < 1 || mes > 12) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingrese un mes valido (1-12): ";
    }

    cout << "Anio: ";
    while (!(cin >> anio) || anio < 1900) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingrese un anio valido (>=1900): ";
    }
}


void Fecha::mostrar() const {
    cout << setfill('0') << setw(2) << dia << '/'
         << setw(2) << mes << '/' << setw(4) << anio << setfill(' ') << '\n';
}
