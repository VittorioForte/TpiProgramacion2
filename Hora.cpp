#include "Hora.h"
#include <iostream>
#include <string>

using namespace std;

Hora::Hora() {
    _hora = 0;
    _minuto = 0;
}

void Hora::cargar() {
    cout << "Ingrese Hora (0-23): ";
    cin >> _hora;
    while (_hora < 0 || _hora > 23) {
        cout << "Hora invalida. Ingrese (0-23): ";
        cin >> _hora;
    }

    cout << "Ingrese Minutos (0-59): ";
    cin >> _minuto;
    while (_minuto < 0 || _minuto > 59) {
        cout << "Minutos invalidos. Ingrese (0-59): ";
        cin >> _minuto;
    }
}

std::string Hora::toString() const {
    std::string h_str = std::to_string(_hora);
    std::string m_str = std::to_string(_minuto);
    if (_hora < 10) {
        h_str = "0" + h_str;
    }
    if (_minuto < 10) {
        m_str = "0" + m_str;
    }

    return h_str + ":" + m_str;
}

int Hora::getTotalMinutos() const {
    return (_hora * 60) + _minuto;
}
