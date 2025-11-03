#ifndef PARTICIPANTES_H_INCLUDED
#define PARTICIPANTES_H_INCLUDED

#include <iostream>

using namespace std;

class Participantes {
private:
    bool estado;
    int idCliente;
    double horaFinal;
    double tiempoTotal;

public:
    Participantes();
    Participantes(int aIdCliente, double aHoraFinal, double aTiempoTotal, bool aEstado = true);

    // GETTERS
    int getIdCliente() const;
    double getHoraFinal() const;
    double getTiempoTotal() const;
    bool getEstado() const;

    // SETTERS
    void setIdCliente(int aIdCliente);
    void setHoraFinal(double aHoraFinal);
    void setTiempoTotal(double aTiempoTotal);
    void setEstado(bool aEstado);

    // METODOS ADICIONALES
    void cargar(int numeroParticipante);
    void mostrar() const;
    double calcularPromedio(int cantidadVueltas) const;
};

#endif // PARTICIPANTES_H_INCLUDED
