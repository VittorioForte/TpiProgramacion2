#include "Fecha.h"

void Fecha::CargarFechaActual() {
    time_t t = time(nullptr);
    tm *f = localtime(&t);
    dia = f->tm_mday;
    mes = f->tm_mon + 1;
    anio = f->tm_year + 1900;
}

void Fecha::Mostrar() const {
    cout << dia << "/" << mes << "/" << anio;
}
