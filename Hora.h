#pragma once
#include <string>

class Hora {
private:
    int _hora;
    int _minuto;

public:
    Hora();

    void cargar();

    std::string toString() const;

    int getTotalMinutos() const;
};
