#ifndef CARRERA_H_INCLUDED
#define CARRERA_H_INCLUDED

#include <string>
#include "Fecha.h"

class Carrera {
private:
    bool estado;
    int idCarrera, idCategoria, cantParticipantes;
    double horaInicio;
    Fecha fecha;
    int vueltasCategoria;
    char nombreCategoria[30];

public:
    Carrera()
        : estado(false), idCarrera(0), idCategoria(0), cantParticipantes(0),
          horaInicio(0), fecha(), vueltasCategoria(0) {
        nombreCategoria[0] = '\0';
    }
    void cargar();
    void mostrar() const;

    // GETTERS
    int getIdCarrera() const { return idCarrera; }
    int getIdCategoria() const { return idCategoria; }
    int getCantParticipantes() const { return cantParticipantes; }
    double getHoraInicio() const { return horaInicio; }
    bool getEstado() const { return estado; }
    Fecha getFecha() const { return fecha; }
    int getVueltasCategoria() const { return vueltasCategoria; }
    std::string getNombreCategoria() const { return std::string(nombreCategoria); }

    // SETTERS
    void setEstado(bool valor) { estado = valor; }
    void setIdCarrera(int valor) { idCarrera = valor; }
    void setHoraInicio(double valor) { horaInicio = valor; }
    void setIdCategoria(int valor) { idCategoria = valor; }
    void setCantParticipantes(int valor) { cantParticipantes = valor; }
    void setFecha(Fecha valor) { fecha = valor; }
    void setVueltasCategoria(int valor) { vueltasCategoria = valor; }
    void setNombreCategoria(const std::string &valor);

    // (estos metodos de archivo los puedes dejar de usar)
    bool escribirDisco(int pos);
    bool leerDisco(int pos);
};

void menuCarreras();

#endif // CARRERA_H_INCLUDED
