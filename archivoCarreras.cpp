#include <iostream>
#include <cstdio>
#include "archivoCarreras.h"
using namespace std;

ArchivoCarreras::ArchivoCarreras(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoCarreras::Guardar(const Carrera &c) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) {
        cout << "[ERROR] No se pudo abrir el archivo " << _nombreArchivo << endl;
        return false;
    }

    bool ok = fwrite(&c, sizeof(Carrera), 1, p);
    if (!ok) cout << "[ERROR] No se pudo escribir en disco." << endl;

    fclose(p);
    return ok;
}

Carrera ArchivoCarreras::Leer(int pos) {
    Carrera obj;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return obj;

    fseek(p, pos * sizeof(Carrera), SEEK_SET);
    fread(&obj, sizeof(Carrera), 1, p);

    fclose(p);
    return obj;
}

int ArchivoCarreras::CantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    long bytes = ftell(p);
    fclose(p);

    return bytes / sizeof(Carrera);
}
