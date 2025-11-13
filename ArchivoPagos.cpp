#include <cstdio>
#include "ArchivoPagos.h"

ArchivoPagos::ArchivoPagos(const std::string& nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoPagos::Guardar(Pago reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == nullptr) return false;
    bool ok = fwrite(&reg, sizeof(Pago), 1, p);
    fclose(p);
    return ok;
}

bool ArchivoPagos::Guardar(Pago reg, int pos) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Pago), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Pago), 1, p);
    fclose(p);
    return ok;
}

Pago ArchivoPagos::Leer(int pos) {
    Pago reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return reg;
    fseek(p, pos * sizeof(Pago), SEEK_SET);
    fread(&reg, sizeof(Pago), 1, p);
    fclose(p);
    return reg;
}

int ArchivoPagos::BuscarPorCarrera(int idCarrera) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;

    Pago reg;
    int pos = 0;
    while (fread(&reg, sizeof(Pago), 1, p)) {
        if (reg.getIdCarrera() == idCarrera && reg.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ArchivoPagos::BuscarPorId(int idPago) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return -1;

    Pago reg;
    int pos = 0;
    while (fread(&reg, sizeof(Pago), 1, p)) {
        if (reg.getIdPago() == idPago && reg.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1;
}

int ArchivoPagos::CantidadRegistros() {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Pago);
}

void ArchivoPagos::Leer(int cantidadRegistros, Pago* vector) {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == nullptr) return;
    fread(vector, sizeof(Pago), cantidadRegistros, p);
    fclose(p);
}

