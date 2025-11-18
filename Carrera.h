#pragma once

#include <iostream>
#include <string>
#include "Fecha.h"
#include "Categorias.h"
#include "ArchivoClientes.h"
#include "Participantes.h"
#include "Hora.h"

class Carrera {
private:
    int _idCarrera;
    Categorias _categoria;
    Fecha _fecha;
    Hora _horaInicio;
    int _cantParticipantes;
    Participantes _listaResultados[10];
    int _idClienteResponsable;
    bool _estado;
    int _estadoCarrera;
    void ordenarResultadosPorTiempo();

public:
    Carrera();

    void cargar();
    void mostrar(int fila, ArchivoClientes& archClientes) const;
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
    Hora getHoraInicio() const;
    const Participantes& getParticipante(int index) const;

    Categorias getCategoria() const;
    int getCantParticipantes() const;
};

