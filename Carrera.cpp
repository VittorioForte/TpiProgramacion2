#include <iostream>
#include <cstdio>
#include "Carrera.h"
#include "Fecha.h"
using namespace std;

void Carrera::cargar() {
    cout << "Ingrese ID de categoria: ";
    cin >> idCategoria;

    cout << "Ingrese cantidad de participantes: ";
    cin >> cantParticipantes;

    cout << "Ingrese hora de inicio (ejemplo 13.30): ";
    cin >> horaInicio;

    fecha.CargarFechaActual();
    estado = true;
}


void Carrera::mostrar() const {
    if (!estado) return;

    cout << "-----------------------------" << endl;
    cout << "ID Carrera: " << idCarrera << endl;
    cout << "Categoria: " << idCategoria << endl;
    cout << "Participantes: " << cantParticipantes << endl;
    cout << "Hora de inicio: " << horaInicio << " hs" << endl;
    cout << "Fecha de creacion: ";
    fecha.Mostrar();
    cout << endl;
    cout << "-----------------------------" << endl;
}


bool Carrera::escribirDisco(int pos) {
    FILE *p;
    if (pos >= 0) {
        p = fopen("carreras.dat", "rb+");
        if (p == NULL) return false;
        fseek(p, sizeof(Carrera) * pos, SEEK_SET);
    } else {
        p = fopen("carreras.dat", "ab");
        if (p == NULL) return false;
    }
    bool ok = fwrite(this, sizeof(Carrera), 1, p);
    fclose(p);
    return ok;
}

bool Carrera::leerDisco(int pos) {
    FILE *p = fopen("carreras.dat", "rb");
    if (p == NULL) return false;
    fseek(p, sizeof(Carrera) * pos, SEEK_SET);
    bool ok = fread(this, sizeof(Carrera), 1, p);
    fclose(p);
    return ok;
}
