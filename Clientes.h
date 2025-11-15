#pragma once

#include <cstring>

class Cliente {
private:

    int _idCliente;
    char _nombre[30];
    char _apellido[30];
    char _telefono[20];
    int _dni;
    bool _estado;

public:
    Cliente();

    void cargar();
    void mostrar(int fila) const;

    int getIdCliente() const;
    int getDni() const;
    const char* getNombre() const;
    const char* getApellido() const;
    bool getEstado() const;

    void setEstado(bool estado);
    void setIdCliente(int idCliente);
};

