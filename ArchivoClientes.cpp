#include <cstdio>
#include "ArchivoClientes.h"

ArchivoClientes::ArchivoClientes(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoClientes::Guardar(Cliente cliente) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&cliente, sizeof(Cliente), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoClientes::Guardar(Cliente cliente, int posicion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == NULL) return false;
    fseek(p, sizeof(Cliente) * posicion, SEEK_SET);
    bool ok = fwrite(&cliente, sizeof(Cliente), 1, p);
    fclose(p);
    return ok;
}

Cliente ArchivoClientes::Leer(int posicion) {
    Cliente cliente;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return cliente;
    fseek(p, sizeof(Cliente) * posicion, SEEK_SET);
    fread(&cliente, sizeof(Cliente), 1, p);
    fclose(p);
    return cliente;
}

int ArchivoClientes::BuscarPorDNI(int dni) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;

    Cliente cliente;
    int pos = 0;
    while (fread(&cliente, sizeof(Cliente), 1, p)) {
        if (cliente.getDni() == dni && cliente.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ArchivoClientes::BuscarPorID(int id) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return -1;

    Cliente cliente;
    int pos = 0;
    while (fread(&cliente, sizeof(Cliente), 1, p)) {
        // La única diferencia es esta línea:
        if (cliente.getIdCliente() == id && cliente.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ArchivoClientes::CantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / sizeof(Cliente);
    fclose(p);
    return cantidad;
}

void ArchivoClientes::LeerTodos(int cantidad, Cliente *vector) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return;
    fread(vector, sizeof(Cliente), cantidad, p);
    fclose(p);
}
