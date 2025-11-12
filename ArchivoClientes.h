#pragma once

#include <string>
#include "Clientes.h"

class ArchivoClientes {
private:
    std::string _nombreArchivo;

public:
    ArchivoClientes(std::string nombreArchivo);

    bool Guardar(Cliente cliente);
    bool Guardar(Cliente cliente, int posicion);
    Cliente Leer(int posicion);
    int BuscarPorDNI(int dni);
    int BuscarPorID(int id);
    int CantidadRegistros();
    void LeerTodos(int cantidad, Cliente *vector);
};

