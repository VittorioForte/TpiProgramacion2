/*#include <iostream>
#include <vector>
#include "MenuListados.h"
#include "ArchivoCarreras.h"
#include "Carrera.h"

using namespace std;

void menuListados() {
    ArchivoCarreras archivoCarreras("carreras.dat");
    int opcion;

    do {
        system("cls");
        cout << "=======================================" << endl;
        cout << "===     MENU DE INFORMES DE CARRERA ===" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Cargar o Modificar Informes" << endl;
        cout << "2 - Visualizar Informes" << endl;
        cout << "0 - Volver al menu anterior" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
        case 1: {
            int totalRegistros = archivoCarreras.CantidadRegistros();
            if (totalRegistros == 0) {
                cout << "No hay carreras registradas para mostrar." << endl;
                system("pause");
                break;
            }

            vector<int> idsDisponibles;
            cout << endl << "=== LISTADO DE CARRERAS DISPONIBLES ===" << endl;
            for (int i = 0; i < totalRegistros; i++) {
                Carrera carrera = archivoCarreras.Leer(i);
                if (!carrera.getEstado()) continue;

                idsDisponibles.push_back(carrera.getIdCarrera());
                cout << "ID: " << carrera.getIdCarrera()
                     << " | Categoria: " << carrera.getCategoria().getNombreCat()
                     << " | Fecha: " << carrera.getFecha().toString() << endl;
            }

            if (idsDisponibles.empty()) {
                cout << "No hay carreras activas para informar." << endl;
                system("pause");
                break;
            }

            int idSeleccionado;
            cout << endl << "Ingrese el ID de la carrera para cargar resultados: ";
            cin >> idSeleccionado;

            int pos = archivoCarreras.Buscar(idSeleccionado);
            if (pos == -1) {
                cout << "No se encontro una carrera con el ID indicado." << endl;
                system("pause");
                break;
            }

            Carrera carreraSeleccionada = archivoCarreras.Leer(pos);
            if (!carreraSeleccionada.getEstado()) {
                cout << "La carrera seleccionada se encuentra eliminada." << endl;
                system("pause");
                break;
            }

            if (carreraSeleccionada.getEstadoCarrera() == 0) {
                cout << endl << "La carrera aun no tiene resultados cargados." << endl;
                carreraSeleccionada.cargarResultados();
                archivoCarreras.Guardar(carreraSeleccionada, pos);
            } else {
                int actualizar = 0;
                cout << endl << "La carrera ya cuenta con resultados." << endl;
                cout << "Desea actualizar los tiempos? (1=SI / 0=NO): ";
                cin >> actualizar;
                if (actualizar == 1) {
                    carreraSeleccionada.cargarResultados();
                    archivoCarreras.Guardar(carreraSeleccionada, pos);
                }
            }

            cout << endl << "Informe cargado/modificado correctamente." << endl;
            system("pause");
            break;
        }

        case 2: {
            int totalRegistros = archivoCarreras.CantidadRegistros();
            if (totalRegistros == 0) {
                cout << "No hay carreras registradas." << endl;
                system("pause");
                break;
            }

            cout << "=== LISTADO DE CARRERAS ===" << endl;
            for (int i = 0; i < totalRegistros; i++) {
                Carrera carrera = archivoCarreras.Leer(i);
                if (carrera.getEstado()) carrera.mostrar();
            }
            system("pause");
            break;
        }

        case 0:
            cout << "Volviendo al menu anterior..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);
}*/
