#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED

#include <string>
#include <vector>

#include "fecha.h"

using namespace std;

class Contratacion {
private:
    bool estado;
    int idContratacion;
    int idCliente;
    int idCarrera;
    double monto;
    Fecha fechaPago;

public:
    Contratacion();
    Contratacion(int aIdContratacion, int aIdCliente, int aIdCarrera, double aMonto, const Fecha &aFecha, bool aEstado = true);

    // GETTERS
    bool getEstado() const;
    int getIdContratacion() const;
    int getIdCliente() const;
    int getIdCarrera() const;
    double getMonto() const;
    const Fecha &getFechaPago() const;

    // SETTERS
    void setEstado(bool aEstado);
    void setIdContratacion(int aIdContratacion);
    void setIdCliente(int aIdCliente);
    void setIdCarrera(int aIdCarrera);
    void setMonto(double aMonto);
    void setFechaPago(const Fecha &aFecha);

    // METODOS ADICIONALES
    void mostrar() const;
};

class Carrera;
class Clientes;

void menuContrataciones(vector<Contratacion> &contrataciones, const vector<Carrera> &carreras,
                        const vector<Clientes> &clientes);

double calcularRecaudacionTotal(const vector<Contratacion> &contrataciones);

double calcularRecaudacionPorCliente(const vector<Contratacion> &contrataciones, int idCliente);

bool guardarContrataciones(const vector<Contratacion> &contrataciones, const string &rutaArchivo);
bool cargarContrataciones(vector<Contratacion> &contrataciones, const string &rutaArchivo);

#endif // CONTRATACION_H_INCLUDED
