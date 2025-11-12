#pragma once

#include <iostream>
#include <string>
#include "Fecha.h"
#include "Categorias.h"
#include "Participantes.h"

class Carrera {
private:
    int _idCarrera;
    Categorias _categoria;
    Fecha _fecha;
    char _horaInicio[6];
    int _cantParticipantes;
    Participantes _listaResultados[10];
    int _idClienteResponsable;
    bool _estado;
    int _estadoCarrera;
    void ordenarResultadosPorTiempo();

public:
    Carrera();

    void cargar();
    void mostrar() const;
    void cargarResultados();
    void mostrarTop3() const;

    void setIdCarrera(int idCarrera);
    void setIdClienteResponsable(int idClienteResponsable);
    void setEstado(bool estado);

    int getIdCarrera() const;
    bool getEstado() const;
    int getIdClienteResponsable() const;
    int getEstadoCarrera() const;
    Fecha getFecha() const;
    const char* getHoraInicio() const;

    Categorias getCategoria() const;
    int getCantParticipantes() const;
};

