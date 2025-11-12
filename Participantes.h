#pragma once

#include <string>

class Participantes {
private:
    char _nombre[50];
    double _horaFinal;
    double _tiempoVueltas;

public:
    Participantes();

    // Getters
    const char* getNombre() const;
    double getHoraFinal() const;
    double getTiempoVueltas() const;

    // Setters
    void setNombre(std::string nombre);
    void setHoraFinal(double horaFinal);
    void setTiempoVueltas(double tiempoVueltas);

    void mostrarResultado() const;
};

