#include "participantes.h"

#include <limits>

using namespace std;

Participantes::Participantes()
    : estado(false), idCliente(0), horaFinal(0.0), tiempoTotal(0.0) {}

Participantes::Participantes(int aIdCliente, double aHoraFinal, double aTiempoTotal, bool aEstado)
    : estado(aEstado), idCliente(aIdCliente), horaFinal(aHoraFinal), tiempoTotal(aTiempoTotal) {}

int Participantes::getIdCliente() const { return idCliente; }

double Participantes::getHoraFinal() const { return horaFinal; }

double Participantes::getTiempoTotal() const { return tiempoTotal; }

bool Participantes::getEstado() const { return estado; }

void Participantes::setIdCliente(int aIdCliente) { idCliente = aIdCliente; }

void Participantes::setHoraFinal(double aHoraFinal) { horaFinal = aHoraFinal; }

void Participantes::setTiempoTotal(double aTiempoTotal) { tiempoTotal = aTiempoTotal; }

void Participantes::setEstado(bool aEstado) { estado = aEstado; }

void Participantes::cargar(int numeroParticipante) {
    estado = true;

    cout << "Ingrese ID del cliente para el participante " << numeroParticipante << ": ";
    cin >> idCliente;

    cout << "Ingrese la hora de finalizacion (formato HH.MM): ";
    cin >> horaFinal;

    cout << "Ingrese el tiempo total empleado (en segundos): ";
    cin >> tiempoTotal;
}

void Participantes::mostrar() const {
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Hora finalizacion: " << horaFinal << endl;
    cout << "Tiempo total: " << tiempoTotal << " segundos" << endl;
}

double Participantes::calcularPromedio(int cantidadVueltas) const {
    if (cantidadVueltas <= 0) {
        return 0.0;
    }
    return tiempoTotal / static_cast<double>(cantidadVueltas);
}
