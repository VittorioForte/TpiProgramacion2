#include "ArchivoCarreras.h"
#include <cstdio>

ArchivoCarreras::ArchivoCarreras(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoCarreras::Guardar(Carrera reg) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == nullptr) return false;
    bool ok = fwrite(&reg, sizeof(Carrera), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoCarreras::Guardar(Carrera reg, int pos) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Carrera), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Carrera), 1, p);
    fclose(p);
    return ok;
}

Carrera ArchivoCarreras::Leer(int pos) {
    Carrera reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Carrera), SEEK_SET);
    fread(&reg, sizeof(Carrera), 1, p);
    fclose(p);
    return reg;
}

int ArchivoCarreras::Buscar(int id) {
    Carrera reg;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;

    int i = 0;
    while (fread(&reg, sizeof(Carrera), 1, p)) {
        if (reg.getIdCarrera() == id) {
            fclose(p);
            return i;
        }
        i++;
    }
    fclose(p);
    return -1;
}

int ArchivoCarreras::CantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Carrera);
}

void ArchivoCarreras::Leer(int cantidadRegistros, Carrera *vector) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return;
    fread(vector, sizeof(Carrera), cantidadRegistros, p);
    fclose(p);
}
