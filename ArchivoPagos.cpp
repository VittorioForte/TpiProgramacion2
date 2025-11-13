#include "ArchivoPagos.h"
#include <cstdio>

ArchivoPagos::ArchivoPagos(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPagos::Guardar(Pago pago) {
    FILE *p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == nullptr) return false;
    bool ok = fwrite(&pago, sizeof(Pago), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoPagos::Guardar(Pago pago, int posicion) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == nullptr) return false;
    fseek(p, sizeof(Pago) * posicion, SEEK_SET);
    bool ok = fwrite(&pago, sizeof(Pago), 1, p);
    fclose(p);
    return ok;
}

Pago ArchivoPagos::Leer(int posicion) {
    Pago pago;
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return pago;
    fseek(p, sizeof(Pago) * posicion, SEEK_SET);
    fread(&pago, sizeof(Pago), 1, p);
    fclose(p);
    return pago;
}

int ArchivoPagos::BuscarPorCarrera(int idCarrera) {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;

    Pago pago;
    int pos = 0;
    while (fread(&pago, sizeof(Pago), 1, p)) {
        if (pago.getIdCarrera() == idCarrera) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ArchivoPagos::CantidadRegistros() {
    FILE *p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cantidad = ftell(p) / sizeof(Pago);
    fclose(p);
    return cantidad;
}

