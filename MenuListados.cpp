#include <iostream>
#include <vector>
#include "MenuListados.h"
#include "ArchivoCarreras.h"
#include "Carrera.h"

using namespace std;

void menuListados() {
    ArchivoCarreras archivoCarreras("carreras.dat");
    int totalRegistros = archivoCarreras.CantidadRegistros();

    if (totalRegistros == 0) {
        cout << "No hay carreras registradas para mostrar." << endl;
        return;
    }

    vector<int> idsDisponibles;

    cout << "=== LISTADO DE CARRERAS DISPONIBLES ===" << endl;
    for (int i = 0; i < totalRegistros; i++) {
        Carrera carrera = archivoCarreras.Leer(i);
        if (!carrera.getEstado()) {
            continue;
        }

        idsDisponibles.push_back(carrera.getIdCarrera());
        cout << "ID: " << carrera.getIdCarrera() << " | Categoria: "
             << carrera.getCategoria().getNombreCat() << " | Fecha: "
             << carrera.getFecha().toString() << endl;
    }

    if (idsDisponibles.empty()) {
        cout << "No hay carreras activas para informar." << endl;
        return;
    }

    int idSeleccionado;
    cout << endl << "Ingrese el ID de la carrera para cargar resultados: ";
    cin >> idSeleccionado;

    int posicion = archivoCarreras.Buscar(idSeleccionado);
    if (posicion == -1) {
        cout << "No se encontro una carrera con el ID indicado." << endl;
        return;
    }

    Carrera carreraSeleccionada = archivoCarreras.Leer(posicion);
    if (!carreraSeleccionada.getEstado()) {
        cout << "La carrera seleccionada se encuentra eliminada." << endl;
        return;
    }

    if (carreraSeleccionada.getEstadoCarrera() == 0) {
        cout << endl << "La carrera aun no tiene resultados cargados." << endl;
        carreraSeleccionada.cargarResultados();
        archivoCarreras.Guardar(carreraSeleccionada, posicion);
    } else {
        int opcionActualizar = 0;
        cout << endl << "La carrera ya cuenta con resultados registrados." << endl;
        cout << "Desea actualizar los tiempos ingresados? (1=SI / 0=NO): ";
        cin >> opcionActualizar;
        if (opcionActualizar == 1) {
            carreraSeleccionada.cargarResultados();
            archivoCarreras.Guardar(carreraSeleccionada, posicion);
        }
    }

    cout << endl << "=== INFORME DE LA CARRERA ===" << endl;
    carreraSeleccionada.mostrar();
}
