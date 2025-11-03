#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Fecha {
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int aDia, int aMes, int aAnio);

    int getDia() const;
    int getMes() const;
    int getAnio() const;

    void setDia(int aDia);
    void setMes(int aMes);
    void setAnio(int aAnio);

    bool esValida() const;
    string toString() const;

    void cargar();
    void mostrar() const;
};

#endif // FECHA_H_INCLUDED
