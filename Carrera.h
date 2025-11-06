#ifndef CARRERA_H_INCLUDED
#define CARRERA_H_INCLUDED

#include "Fecha.h"

class Carrera {
private:
    bool estado;
    int idCarrera, idCategoria, cantParticipantes;
    double horaInicio;
    Fecha fecha;

public:
    void cargar();
    void mostrar() const;

    // GETTERS
    int getIdCarrera() const { return idCarrera; }
    int getIdCategoria() const { return idCategoria; }   // estaba mal en tu repo
    int getCantParticipantes() const { return cantParticipantes; }
    double getHoraInicio() const { return horaInicio; }
    bool getEstado() const { return estado; }
    Fecha getFecha() const { return fecha; }

    // SETTERS
    void setEstado(bool valor) { estado = valor; }
    void setIdCarrera(int valor) { idCarrera = valor; }
    void setHoraInicio(double valor) { horaInicio = valor; }
    void setIdCategoria(int valor) { idCategoria = valor; }
    void setCantParticipantes(int valor) { cantParticipantes = valor; }
    void setFecha(Fecha valor) { fecha = valor; }

    // (estos métodos de archivo los puedes dejar de usar)
    bool escribirDisco(int pos);
    bool leerDisco(int pos);
};

void menuCarreras();

#endif // CARRERA_H_INCLUDED
