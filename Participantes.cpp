#include <iostream>
#include <iomanip>
#include <cstdio>
#include "participantes.h"

using namespace std;

namespace {
const char *FILE_PARTICIPANTES = "participantes.dat";
}

Participantes::Participantes() {
    estado = false;
    idCliente = 0;
    tiempoVueltas = 0;
    horaFinal = 0.0;
}

int Participantes::getIdCliente() const { return idCliente; }
double Participantes::getHoraFinal() const { return horaFinal; }
int Participantes::getTiempoVueltas() const { return tiempoVueltas; }
bool Participantes::getEstado() const { return estado; }

void Participantes::setIdCliente(int aIdCliente) { idCliente = aIdCliente; }
void Participantes::setHoraFinal(double aHoraFinal) { horaFinal = aHoraFinal; }
void Participantes::setTiempoVueltas(int aTiempo) { tiempoVueltas = aTiempo; }
void Participantes::setEstado(bool aEstado) { estado = aEstado; }

void Participantes::cargar(int numeroVueltas) {
    setEstado(true);
    cout << "ID del cliente participante: ";
    cin >> idCliente;

    cout << "Hora de finalizacion (en minutos decimales): ";
    cin >> horaFinal;

    if (numeroVueltas > 0) {
        cout << "Tiempo total de vueltas (en minutos): ";
        cin >> tiempoVueltas;
    } else {
        tiempoVueltas = 0;
    }
}

void Participantes::mostrar() const {
    cout << left << setw(15) << idCliente
         << setw(15) << fixed << setprecision(2) << horaFinal
         << setw(15) << tiempoVueltas
         << (estado ? "Activo" : "Inactivo") << '\n';
}

double Participantes::calcularPromedio(int cantidadVueltas, double horaInicio) const {
    if (!estado || cantidadVueltas <= 0) {
        return 0.0;
    }
    double duracion = horaFinal - horaInicio;
    if (duracion < 0) {
        return 0.0;
    }
    return duracion / static_cast<double>(cantidadVueltas);
}

bool Participantes::grabarEnDisco() const {
    FILE *p = fopen(FILE_PARTICIPANTES, "ab");
    if (p == nullptr) {
        return false;
    }
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Participantes::leerDeDisco(int pos) {
    FILE *p = fopen(FILE_PARTICIPANTES, "rb");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fread(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Participantes::modificarEnDisco(int pos) const {
    FILE *p = fopen(FILE_PARTICIPANTES, "rb+");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

void menuParticipantes() {
    cout << "Menu de participantes" << endl;
}
