#include <iostream>
#include <cstring>
#include <iomanip>
#include <string>
#include "Carrera.h"

using namespace std;

Carrera::Carrera() {
    _idCarrera = 0;
    strcpy(_horaInicio, "00:00");
    _cantParticipantes = 0;
    _idClienteResponsable = 0;
    _estado = true;
    _estadoCarrera = 0;
    _monto = 0.0;
    _pagado = false;
}

void Carrera::cargar() {
    cout << "=== REGISTRAR NUEVA CARRERA ===" << endl;
    _categoria.cargar();
    string nombreCategoria = _categoria.getNombreCat();
    if (nombreCategoria == "PROFESIONAL") {
        _monto = 135000.0;
    }
    else if (nombreCategoria == "AMATEUR") {
        _monto = 100000.0;
    }
    else if (nombreCategoria == "INFANTIL") {
        _monto = 85000.0;
    }
    else {
        _monto = 0.0;
    }
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
    _pagado = false;

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
    cout << fixed << setprecision(2);
    cout << "Monto: $" << _monto << endl;
    cout << "Estado de pago: " << (_pagado ? "PAGADA" : "PENDIENTE") << endl;

    if (_estadoCarrera == 0) {
        cout << "Participantes Inscriptos (" << _cantParticipantes << "):" << endl;
        for (int i = 0; i < _cantParticipantes; i++) {
            cout << "- " << _listaResultados[i].getNombre() << endl;
        }
    }
    else {
        cout << endl << "===========================" << endl;
        cout << endl << "=== TABLA DE POSICIONES ===" << endl;
        cout << endl << "===========================" << endl << endl;

        cout << "Nombre\t\t | Hora Fin\t | T. x Vuelta (min)" << endl;
        cout << "--------------------------------------------------" << endl;
        for (int i = 0; i < _cantParticipantes; i++) {
            _listaResultados[i].mostrarResultado();
        }
        mostrarTop3();
    }
}

void Carrera::cargarResultados() {
    if (_cantParticipantes == 0) {
        cout << "No hay participantes registrados para esta carrera." << endl;
        return;
    }

    cout << endl << "Ingreso de tiempos finales para la carrera ID " << _idCarrera << endl;
    cout << "Categoria: " << _categoria.getNombreCat() << endl;
    cout << "Cantidad de participantes: " << _cantParticipantes << endl;
    cout << "Ingrese los tiempos en minutos." << endl;

    for (int i = 0; i < _cantParticipantes; i++) {
        double tiempoFinal = 0.0;
        double tiempoPromedioVuelta = 0.0;

        cout << endl << "Participante: " << _listaResultados[i].getNombre() << endl;
        cout << "Tiempo final (minutos): ";
        cin >> tiempoFinal;
        while (tiempoFinal <= 0) {
            cout << "El tiempo final debe ser mayor a cero. Ingrese nuevamente: ";
            cin >> tiempoFinal;
        }
        _listaResultados[i].setHoraFinal(tiempoFinal);

        cout << "Tiempo promedio por vuelta (minutos, 0 para calcular automaticamente): ";
        cin >> tiempoPromedioVuelta;
        if (tiempoPromedioVuelta <= 0 && _categoria.getCantVueltas() > 0) {
            tiempoPromedioVuelta = tiempoFinal / _categoria.getCantVueltas();
        }
        _listaResultados[i].setTiempoVueltas(tiempoPromedioVuelta);
    }

    ordenarResultadosPorTiempo();
    _estadoCarrera = 1;

    cout << endl << "Resultados cargados correctamente." << endl;
}

void Carrera::mostrarTop3() const {
    if (_estadoCarrera == 0) {
        return;
    }

    int limite = _cantParticipantes < 3 ? _cantParticipantes : 3;
    if (limite == 0) {
        return;
    }
    cout << endl << "=== TOP 3 ===" << endl;
    for (int i = 0; i < limite; i++) {
        const Participantes& participante = _listaResultados[i];
        cout << i + 1 << ") " << participante.getNombre()
             << " - Tiempo Final: " << participante.getHoraFinal() << " min" << endl << endl;
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
void Carrera::setMonto(double monto) {
    _monto = monto;
}
void Carrera::setPagado(bool pagado) {
    _pagado = pagado;
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
double Carrera::getMonto() const { return _monto; }
bool Carrera::getPagado() const { return _pagado; }

void Carrera::ordenarResultadosPorTiempo() {
    for (int i = 0; i < _cantParticipantes - 1; i++) {
        for (int j = i + 1; j < _cantParticipantes; j++) {
            if (_listaResultados[j].getHoraFinal() < _listaResultados[i].getHoraFinal()) {
                Participantes aux = _listaResultados[i];
                _listaResultados[i] = _listaResultados[j];
                _listaResultados[j] = aux;
            }
        }
    }
}


