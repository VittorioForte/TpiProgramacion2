#ifndef CARRERA_H_INCLUDED
#define CARRERA_H_INCLUDED

#include "fecha.h"
#include "categorias.h"

class Carrera {
private:
    bool estado;
    int idCarrera;
    int idCategoria;
    int cantParticipantes;
    double horaInicio;
    Fecha fecha;

public:
    Carrera();

    //GETTERS
    bool getEstado() const;
    int getIdCarrera() const;
    int getIdCategoria() const;
    int getCantParticipantes() const;
    double getHoraInicio() const;
    Fecha getFecha() const;

    //SETTERS
    void setEstado(bool aEstado);
    void setIdCarrera(int aIdCarrera);
    void setIdCategoria(int aIdCategoria);
    void setCantParticipantes(int aCantidad);
    void setHoraInicio(double aHoraInicio);
    void setFecha(const Fecha &aFecha);

    //METODOS ADICIONALES
    void cargarCabecera();
    void mostrarCabecera() const;
    bool grabarEnDisco() const;
    bool leerDeDisco(int pos);
    bool modificarEnDisco(int pos) const;
};

void menuCarreras();

#endif // CARRERA_H_INCLUDED
