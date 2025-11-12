#include <iostream>
#include <cstring>
#include "Carrera.h"

using namespace std;

Carrera::Carrera() {
    _idCarrera = 0;
    strcpy(_horaInicio, "00:00");
    _cantParticipantes = 0;
    _idClienteResponsable = 0;
    _estado = true;
    _estadoCarrera = 0;
}

void Carrera::cargar() {
    cout << "=== REGISTRAR NUEVA CARRERA ===" << endl;
    _categoria.cargar();
    cout << "Ingrese la fecha de la carrera:" << endl;
    _fecha.Cargar();
    cout << "Ingrese hora de inicio (formato hh:mm): ";
    cin.ignore();
    cin.getline(_horaInicio, 6);
    cout << "Ingrese cantidad de participantes (max 10): ";
    cin >> _cantParticipantes;
    if (_cantParticipantes > 10) _cantParticipantes = 10;

    for (int i = 0; i < _cantParticipantes; i++) {
        string nombre;
        cout << "Nombre Participante #" << i + 1 << ": ";
        cin >> nombre;
        _listaResultados[i].setNombre(nombre);
    }

    _estadoCarrera = 0;
    _estado = true;

    cout << endl << "Datos de la carrera cargados." << endl;
}

void Carrera::mostrar() const {
    cout << "==================================" << endl;
    cout << "ID Carrera: " << _idCarrera << endl;
    cout << "Estado Carrera: " << (_estadoCarrera == 0 ? "PENDIENTE" : "TERMINADA") << endl;

    cout << "Categoria: " << _categoria.getNombreCat() << endl;
    cout << "Cantidad de vueltas: " << _categoria.getCantVueltas() << endl;

    cout << "Fecha: " << _fecha.toString() << endl;
    cout << "Hora inicio: " << _horaInicio << endl;

    if (_estadoCarrera == 0) {
        cout << "Participantes Inscriptos (" << _cantParticipantes << "):" << endl;
        for (int i = 0; i < _cantParticipantes; i++) {
            cout << "- " << _listaResultados[i].getNombre() << endl;
        }
    }
    else {
        cout << endl << "--- TABLA DE POSICIONES ---" << endl;
        cout << "Nombre\t\t | Hora Fin\t | T. x Vuelta (min)" << endl;
        cout << "-------------------------------------------------" << endl;
        for (int i = 0; i < _cantParticipantes; i++) {
            _listaResultados[i].mostrarResultado();
        }
    }
}


// Setters
void Carrera::setIdCarrera(int idCarrera) {
    _idCarrera = idCarrera;
}
void Carrera::setIdClienteResponsable(int idClienteResponsable) {
    _idClienteResponsable = idClienteResponsable;
}
void Carrera::setEstado(bool estado) {
    _estado = estado;
}

// Getters
int Carrera::getIdCarrera() const { return _idCarrera; }
bool Carrera::getEstado() const { return _estado; }
int Carrera::getIdClienteResponsable() const { return _idClienteResponsable; }
int Carrera::getEstadoCarrera() const { return _estadoCarrera; }
Fecha Carrera::getFecha() const { return _fecha; }
const char* Carrera::getHoraInicio() const { return _horaInicio; }
Categorias Carrera::getCategoria() const { return _categoria; }
int Carrera::getCantParticipantes() const { return _cantParticipantes; }


