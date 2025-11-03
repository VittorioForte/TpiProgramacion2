#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cstdlib>
#include "carrera.h"

using namespace std;

namespace {
const char *FILE_CARRERAS = "carreras.dat";
}

Carrera::Carrera() {
    estado = false;
    idCarrera = 0;
    idCategoria = 0;
    cantParticipantes = 0;
    horaInicio = 0.0;
}

bool Carrera::getEstado() const { return estado; }
int Carrera::getIdCarrera() const { return idCarrera; }
int Carrera::getIdCategoria() const { return idCategoria; }
int Carrera::getCantParticipantes() const { return cantParticipantes; }
double Carrera::getHoraInicio() const { return horaInicio; }
Fecha Carrera::getFecha() const { return fecha; }

void Carrera::setEstado(bool aEstado) { estado = aEstado; }
void Carrera::setIdCarrera(int aIdCarrera) { idCarrera = aIdCarrera; }
void Carrera::setIdCategoria(int aIdCategoria) { idCategoria = aIdCategoria; }
void Carrera::setCantParticipantes(int aCantidad) { cantParticipantes = aCantidad; }
void Carrera::setHoraInicio(double aHoraInicio) { horaInicio = aHoraInicio; }
void Carrera::setFecha(const Fecha &aFecha) { fecha = aFecha; }

void Carrera::cargarCabecera() {
    setEstado(true);

    cout << "Numero de carrera: ";
    cin >> idCarrera;

    cout << "ID de categoria (1 Profesional / 2 Amateur / 3 Infantil): ";
    cin >> idCategoria;

    cout << "Cantidad de participantes: ";
    cin >> cantParticipantes;

    cout << "Hora de inicio (en minutos decimales): ";
    cin >> horaInicio;

    cout << "Fecha de la carrera" << endl;
    fecha.cargar();
}

void Carrera::mostrarCabecera() const {
    cout << "Carrera N°: " << idCarrera << '\n';
    cout << "Categoria: " << idCategoria << '\n';
    cout << "Participantes: " << cantParticipantes << '\n';
    cout << "Hora de inicio: " << fixed << setprecision(2) << horaInicio << '\n';
    cout << "Fecha: ";
    fecha.mostrar();
    cout << "Estado: " << (estado ? "Activa" : "Inactiva") << "\n";
}

bool Carrera::grabarEnDisco() const {
    FILE *p = fopen(FILE_CARRERAS, "ab");
    if (p == nullptr) {
        return false;
    }
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Carrera::leerDeDisco(int pos) {
    FILE *p = fopen(FILE_CARRERAS, "rb");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fread(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

bool Carrera::modificarEnDisco(int pos) const {
    FILE *p = fopen(FILE_CARRERAS, "rb+");
    if (p == nullptr) {
        return false;
    }
    fseek(p, pos * sizeof(*this), SEEK_SET);
    bool ok = fwrite(this, sizeof(*this), 1, p) == 1;
    fclose(p);
    return ok;
}

void menuCarreras(){

    int opcion;
    do {
        system("cls");
        cout << "=======MENU CARRERAS=======\n";
        cout << "1) Nueva carrera\n";
        cout << "2) Listar carreras \n";
        cout << "3) Buscar carrera por numero\n";
        cout << "4) listar carrera por participante\n";
        cout << "0) Volver para atras\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;


        switch (opcion) {
            case 1: {
                Carrera nueva;
                nueva.cargarCabecera();
                if (nueva.grabarEnDisco()) {
                    cout << "Carrera guardada correctamente." << endl;
                } else {
                    cout << "No se pudo guardar la carrera." << endl;
                }
                system("pause");
                break;
            }
            case 2: {
                Carrera registro;
                int pos = 0;
                while (registro.leerDeDisco(pos++)) {
                    if (registro.getEstado()) {
                        registro.mostrarCabecera();
                        cout << "-----------------------------" << endl;
                    }
                }
                system("pause");
                break;
            }
            case 3:
            case 4:
                cout << "Opcion en desarrollo." << endl;
                system("pause");
                break;
            case 0:
                cout << "Volviendo al Menu Principal...\n";
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }

    } while (opcion != 0);


}
