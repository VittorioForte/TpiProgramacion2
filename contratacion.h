#ifndef CONTRATACION_H_INCLUDED
#define CONTRATACION_H_INCLUDED

#include "fecha.h"

class Contratacion {
private:
    bool estado;
    int idContratacion;
    int idCliente;
    int idCarrera;
    float monto;
    Fecha fechaPago;

public:
    Contratacion();

    //GETTERS
    bool getEstado() const;
    int getIdContratacion() const;
    int getIdCliente() const;
    int getIdCarrera() const;
    float getMonto() const;
    Fecha getFechaPago() const;

    //SETTERS
    void setEstado(bool aEstado);
    void setIdContratacion(int aIdContratacion);
    void setIdCliente(int aIdCliente);
    void setIdCarrera(int aIdCarrera);
    void setMonto(float aMonto);
    void setFechaPago(const Fecha &aFecha);

    //METODOS ADICIONALES
    void cargar(int nuevoId);
    void mostrar() const;
    bool grabarEnDisco() const;
    bool leerDeDisco(int pos);
    bool modificarEnDisco(int pos) const;
};

#endif // CONTRATACION_H_INCLUDED
