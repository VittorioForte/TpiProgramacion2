#include "fecha.h"

#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

Fecha::Fecha() : dia(1), mes(1), anio(2000) {}

Fecha::Fecha(int aDia, int aMes, int aAnio) : dia(aDia), mes(aMes), anio(aAnio) {}

int Fecha::getDia() const { return dia; }

int Fecha::getMes() const { return mes; }

int Fecha::getAnio() const { return anio; }

void Fecha::setDia(int aDia) { dia = aDia; }

void Fecha::setMes(int aMes) { mes = aMes; }

void Fecha::setAnio(int aAnio) { anio = aAnio; }

bool Fecha::esValida() const {
    if (anio < 1900 || mes < 1 || mes > 12 || dia < 1) {
        return false;
    }

    static const int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int limite = diasPorMes[mes - 1];

    // Anio bisiesto
    bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
    if (mes == 2 && esBisiesto) {
        limite = 29;
    }

    return dia <= limite;
}

string Fecha::toString() const {
    ostringstream oss;
    oss << setfill('0') << setw(2) << dia << "/" << setw(2) << mes << "/" << anio;
    return oss.str();
}

void Fecha::cargar() {
    do {
        cout << "Ingrese dia: ";
        cin >> dia;
        cout << "Ingrese mes: ";
        cin >> mes;
        cout << "Ingrese anio: ";
        cin >> anio;

        if (!esValida()) {
            cout << "Fecha invalida. Ingrese nuevamente." << endl;
        }
    } while (!esValida());
}

void Fecha::mostrar() const { cout << toString(); }
