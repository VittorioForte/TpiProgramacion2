#include <iostream>
#include <cstdio>
#include <algorithm>
#include "Carrera.h"
#include "Fecha.h"
#include "Categorias.h"
using namespace std;

void Carrera::setNombreCategoria(const std::string &valor) {
    fill_n(nombreCategoria, sizeof(nombreCategoria), '\0');
    size_t length = min(valor.size(), sizeof(nombreCategoria) - 1);
    valor.copy(nombreCategoria, length);
    nombreCategoria[length] = '\0';
}

void Carrera::cargar() {
    Categorias categoriaSeleccionada;
    do {
        categoriaSeleccionada.cargar();
        if (!categoriaSeleccionada.getEstado()) {
            cout << "La categoria ingresada no es valida. Intente nuevamente.\n";
        }
    } while (!categoriaSeleccionada.getEstado());

    setIdCategoria(categoriaSeleccionada.getIdCategoria());
    setNombreCategoria(categoriaSeleccionada.getNombreCat());
    setVueltasCategoria(categoriaSeleccionada.getCantVueltas());

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
    cout << "Categoria (ID): " << idCategoria;
    if (nombreCategoria[0] != '\0') {
        cout << " - " << nombreCategoria;
    }
    cout << endl;
    if (vueltasCategoria > 0) {
        cout << "Vueltas de la categoria: " << vueltasCategoria << endl;
    } else {
        cout << "Vueltas de la categoria: No registrado" << endl;
    }
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
