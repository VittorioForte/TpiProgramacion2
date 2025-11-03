#ifndef CARRERA_H_INCLUDED
#define CARRERA_H_INCLUDED

#include <string>
#include <vector>

#include "categorias.h"
#include "clientes.h"
#include "fecha.h"
#include "participantes.h"

using namespace std;

class Carrera {
private:
    bool estado;
    int idCarrera;
    int idCategoria;
    int cantParticipantes;
    int idClientePago;
    double horaInicio;
    Fecha fecha;
    vector<Participantes> participantes;

public:
    Carrera();

    // GETTERS
    bool getEstado() const;
    int getIdCarrera() const;
    int getIdCategoria() const;
    int getCantParticipantes() const;
    int getIdClientePago() const;
    double getHoraInicio() const;
    const Fecha &getFecha() const;
    const vector<Participantes> &getParticipantes() const;

    // SETTERS
    void setEstado(bool aEstado);
    void setIdCarrera(int aIdCarrera);
    void setIdCategoria(int aIdCategoria);
    void setCantParticipantes(int aCantParticipantes);
    void setIdClientePago(int aIdClientePago);
    void setHoraInicio(double aHoraInicio);
    void setFecha(const Fecha &aFecha);
    void setParticipantes(const vector<Participantes> &aParticipantes);

    void agregarParticipante(const Participantes &participante);
    double promedioParticipante(size_t indiceParticipante, int cantidadVueltas) const;
    void mostrarResumen(const Categorias &categoria, const Clientes *clientePago) const;
};

void menuCarreras(vector<Carrera> &carreras, const vector<Categorias> &categorias,
                  const vector<Clientes> &clientes);

bool registrarCarrera(vector<Carrera> &carreras, const vector<Categorias> &categorias,
                      const vector<Clientes> &clientes);

void mostrarPodioRecords(const vector<Carrera> &carreras, const vector<Categorias> &categorias,
                         const vector<Clientes> &clientes);

bool guardarCarreras(const vector<Carrera> &carreras, const string &rutaArchivo);
bool cargarCarreras(vector<Carrera> &carreras, const string &rutaArchivo);

#endif // CARRERA_H_INCLUDED
