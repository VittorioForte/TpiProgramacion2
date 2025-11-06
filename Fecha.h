#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED

#include <iostream>
#include <ctime>
using namespace std;

class Fecha {
private:
    int dia, mes, anio;

public:
    // Carga la fecha actual automáticamente
    void CargarFechaActual();

    // Muestra la fecha en formato dd/mm/aaaa
    void Mostrar() const;

    // Setters y getters
    void setDia(int d) { dia = d; }
    void setMes(int m) { mes = m; }
    void setAnio(int a) { anio = a; }

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAnio() const { return anio; }
};

#endif // FECHA_H_INCLUDED
