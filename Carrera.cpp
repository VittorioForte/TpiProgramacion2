#include <iostream>
#include <cstring>
#include "Carrera.h"
#include "rlutil.h"

using namespace std;

Carrera::Carrera() {
    _idCarrera = 0;
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
    cout << "Ingrese hora de inicio (formato hh:mm): " << endl;
    _horaInicio.cargar();
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

void Carrera::mostrar(int fila, ArchivoClientes& archClientes) const {
    if (!_estado) return;
    rlutil::locate(1, fila);  cout << _idCarrera;
    rlutil::locate(4, fila);  cout << (_estadoCarrera == 0 ? "PENDIENTE" : "TERMINADA");
    rlutil::locate(16, fila); cout << _categoria.getNombreCat();
    rlutil::locate(30, fila); cout << _categoria.getCantVueltas();
    rlutil::locate(38, fila); cout << _horaInicio.toString();
    rlutil::locate(50, fila);
    int idResp = _idClienteResponsable;
    if (idResp == 0) {
        cout << "Sin cliente asignado";
    } else {
        int posCli = archClientes.BuscarPorID(idResp);
        if (posCli != -1) {
            Cliente cli = archClientes.Leer(posCli);
            string nombreCompleto = string(cli.getNombre()) + " " + string(cli.getApellido());
            if(nombreCompleto.length() > 20) nombreCompleto = nombreCompleto.substr(0, 20);
            cout << nombreCompleto;
        } else {
            cout << "ID Error";
        }
    }

    rlutil::locate(1, fila + 1);
    if (_estadoCarrera == 0) {
        cout << "  Participantes (" << _cantParticipantes << "): ";
        for (int i = 0; i < _cantParticipantes; i++) {
            cout << _listaResultados[i].getNombre();
            if (i < _cantParticipantes - 1) {
                cout << ", ";
            }
        }
    }
    else {
        cout << "  Podio: ";
        int limite = _cantParticipantes < 3 ? _cantParticipantes : 3;

        if (limite == 0) {
            cout << "Sin participantes.";
        }

        for (int i = 0; i < limite; i++) {
            const Participantes& p = _listaResultados[i];
            cout << i + 1 << ". " << p.getNombre();
            cout << " (" << p.getTiempoVueltas() << " min/vuelta)";
            if (i < limite - 1) {
                cout << ", ";
            }
        }
    }
}

void Carrera::cargarResultados() {
    if (_cantParticipantes == 0) {
        cout << "No hay participantes registrados para esta carrera." << endl;
        return;
    }

    cout << endl << "Ingreso de tiempos finales para la carrera ID " << _idCarrera << endl;
    cout << "Categoria: " << _categoria.getNombreCat() << endl;

    cout << "Hora de Inicio: " << _horaInicio.toString() << endl;
    int horaInicioMin = _horaInicio.getTotalMinutos();
    int cantVueltas = _categoria.getCantVueltas();

    for (int i = 0; i < _cantParticipantes; i++) {

        Hora horaFin;
        int horaFinMin = 0;

        cout << endl << "Participante: " << _listaResultados[i].getNombre() << endl;

        while(horaFinMin <= horaInicioMin) {
            cout << "Hora de finalizacion:" << endl;
            horaFin.cargar();
            horaFinMin = horaFin.getTotalMinutos();

            if (horaFinMin <= horaInicioMin) {
                cout << "La hora de fin debe ser posterior a la de inicio." << endl;
            }
        }

        int duracionEnMinutos = horaFinMin - horaInicioMin;

        _listaResultados[i].setHoraFinal(duracionEnMinutos);

        double tiempoPromedioVuelta = 0.0;
        if (cantVueltas > 0) {
            tiempoPromedioVuelta = (double)duracionEnMinutos / cantVueltas;
        }
        _listaResultados[i].setTiempoVueltas(tiempoPromedioVuelta);

        cout << "Tiempo total registrado: " << duracionEnMinutos << " min." << endl;
        cout << "Tiempo promedio por vuelta: " << tiempoPromedioVuelta << " min/vuelta." << endl;
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

void Carrera::ordenarResultadosPorTiempo() {
    for (int i = 0; i < _cantParticipantes - 1; i++) {
        for (int j = i + 1; j < _cantParticipantes; j++) {
            if (_listaResultados[j].getTiempoVueltas() < _listaResultados[i].getTiempoVueltas()) {
                Participantes aux = _listaResultados[i];
                _listaResultados[i] = _listaResultados[j];
                _listaResultados[j] = aux;
            }
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
Hora Carrera::getHoraInicio() const { return _horaInicio; }
Categorias Carrera::getCategoria() const { return _categoria; }
int Carrera::getCantParticipantes() const { return _cantParticipantes; }
const Participantes& Carrera::getParticipante(int index) const {return _listaResultados[index]; }



