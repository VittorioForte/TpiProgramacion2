#pragma once

#include <iostream>
#include <string>

class Fecha {
private:
    int _dia, _mes, _anio;

public:
    Fecha();
    Fecha(int dia, int mes, int anio);

    // Getters
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // Setters
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    void Cargar();
    std::string toString() const;
};

