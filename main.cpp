#include <filesystem>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "categorias.h"
#include "clientes.h"
#include "contratacion.h"
#include "participantes.h"
#include "carrera.h"

using namespace std;

int main() {
    const filesystem::path directorioDatos = "datos";
    try {
        filesystem::create_directories(directorioDatos);
    } catch (const filesystem::filesystem_error &e) {
        cerr << "No se pudo crear el directorio de datos: " << e.what() << endl;
    }

    const string archivoClientes = (directorioDatos / "clientes.dat").string();
    const string archivoCarreras = (directorioDatos / "carreras.dat").string();
    const string archivoContrataciones = (directorioDatos / "contrataciones.dat").string();

    vector<Clientes> clientes;
    vector<Carrera> carreras;
    vector<Contratacion> contrataciones;
    vector<Categorias> categorias = crearCategoriasPredeterminadas();

    cargarClientes(clientes, archivoClientes);
    cargarCarreras(carreras, archivoCarreras);
    cargarContrataciones(contrataciones, archivoContrataciones);

    int opcion;
    do {
        cout << "-----MENU PRINCIPAL-----\n";
        cout << "1) Carreras historicas\n";
        cout << "2) Nueva carrera\n";
        cout << "3) Clientes\n";
        cout << "4) Contrataciones\n";
        cout << "5) Podio de records\n";
        cout << "0) Salir\n";
        cout << "Seleccione una opcion: ";

        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                menuCarreras(carreras, categorias, clientes);
                break;
            case 2: {
                bool creada = registrarCarrera(carreras, categorias, clientes);
                if (!creada) {
                    cout << "No se pudo registrar la carrera." << endl;
                }
                break;
            }
            case 3:
                menuClientes(clientes);
                break;
            case 4:
                menuContrataciones(contrataciones, carreras, clientes);
                break;
            case 5:
                mostrarPodioRecords(carreras, categorias, clientes);
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion Invalida." << endl;
                break;
        }

        cout << endl;
    } while (opcion != 0);

    if (!guardarClientes(clientes, archivoClientes)) {
        cerr << "No se pudo guardar el archivo de clientes." << endl;
    }
    if (!guardarCarreras(carreras, archivoCarreras)) {
        cerr << "No se pudo guardar el archivo de carreras." << endl;
    }
    if (!guardarContrataciones(contrataciones, archivoContrataciones)) {
        cerr << "No se pudo guardar el archivo de contrataciones." << endl;
    }

    return 0;
}
