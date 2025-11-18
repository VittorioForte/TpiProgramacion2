#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "MenuListados.h"
#include "ArchivoCarreras.h"
#include "Carrera.h"
#include "ArchivoPagos.h"
#include "Pago.h"

using namespace std;

struct ResultadoHistorico {
    string nombre;
    double tiempoPromedio;
    double tiempoTotal;
    int idCarrera;
    Fecha fecha;
};

void mostrarTopHistoricoPorCategoria(ArchivoCarreras& archivoCarreras, int idCategoria, const char* nombreCategoria);
void mostrarTopProfesional(ArchivoCarreras& archivoCarreras);
void mostrarTopAmateur(ArchivoCarreras& archivoCarreras);
void mostrarTopInfantil(ArchivoCarreras& archivoCarreras);
void mostrarTotalRecaudado(ArchivoPagos& archivoPagos);



void menuListados() {
    ArchivoCarreras archivoCarreras("carreras.dat");
    ArchivoPagos archivoPagos("pagos.dat");
    int opcion;

    do {
        system("cls");
        cout << "=======================================" << endl;
        cout << "===     MENU DE INFORMES DE CARRERA ===" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Podio historico" << endl;
        cout << "2 - Dinero total recaudado" << endl;
        cout << "0 - Volver al menu anterior" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
        case 1:
            system("cls");

            mostrarTopProfesional(archivoCarreras);

            cout << "" << endl << endl;

            mostrarTopAmateur(archivoCarreras);

            cout << "" << endl << endl;

            mostrarTopInfantil(archivoCarreras);

            system("pause");
            break;

        case 2:
            system("cls");
            mostrarTotalRecaudado(archivoPagos);
            system("pause");
            break;
        case 0:
            cout << "Volviendo al menu anterior..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);
}



// PODIO //
//FUNCION PARA LA RECAUDACION DE INFO PARA LOS TOPS
// ACA ARMA EL TOP 3 PARA CADA CATEGORIA, SI EN VEZ DE QUE TE

void mostrarTopHistoricoPorCategoria(ArchivoCarreras& archivoCarreras, int idCategoria, const char* nombreCategoria) {
    int total = archivoCarreras.CantidadRegistros();
    if (total == 0) {
        cout << "No hay carreras registradas." << endl;
        return;
    }

    vector<ResultadoHistorico> resultados;

    for (int i = 0; i < total; ++i) {
        Carrera c = archivoCarreras.Leer(i);

        if (!c.getEstado()) continue;
        if (c.getEstadoCarrera() == 0) continue;

        if (c.getCategoria().getIdCategoria() != idCategoria) continue;

        int cant = c.getCantParticipantes();
        for (int j = 0; j < cant; ++j) {
            const Participantes& p = c.getParticipante(j);

            ResultadoHistorico r;
            r.nombre = p.getNombre();

            r.tiempoPromedio = p.getTiempoVueltas();

            r.tiempoTotal = p.getHoraFinal();

            r.idCarrera = c.getIdCarrera();
            r.fecha = c.getFecha();

            resultados.push_back(r);
        }
    }

    if (resultados.empty()) {
        cout << "No hay resultados historicos para la categoria " << nombreCategoria << "." << endl;
        return;
    }

    sort(resultados.begin(), resultados.end(),
         [](const ResultadoHistorico& a, const ResultadoHistorico& b) {
             return a.tiempoPromedio < b.tiempoPromedio;
         });

    int limite = (resultados.size() < 3) ? resultados.size() : 3;

    cout << "=== TOP 3 HISTORICO DE " << nombreCategoria << " ===" << endl << endl;
    for (int i = 0; i < limite; ++i) {
        const ResultadoHistorico& r = resultados[i];
        cout << i + 1 << ") " << r.nombre << " - "
             << " tiempo/vuelta: " << r.tiempoPromedio << " - "
             << " mins/totales: " << r.tiempoTotal << " - "
             << " (Carrera ID: " << r.idCarrera
             << " - " << r.fecha.toString() << ")" << endl;
    }
    cout << endl;
}

void mostrarTopProfesional(ArchivoCarreras& archivoCarreras) {
    mostrarTopHistoricoPorCategoria(archivoCarreras, 1, "PROFESIONAL");
}

void mostrarTopAmateur(ArchivoCarreras& archivoCarreras) {
    mostrarTopHistoricoPorCategoria(archivoCarreras, 2, "AMATEUR");
}

void mostrarTopInfantil(ArchivoCarreras& archivoCarreras) {
    mostrarTopHistoricoPorCategoria(archivoCarreras, 3, "INFANTIL");
}



// TOTAL RECAUDADO
void mostrarTotalRecaudado(ArchivoPagos& archivoPagos) {
    int totalRegs = archivoPagos.CantidadRegistros();
    if (totalRegs == 0) {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    long long totalRecaudado = 0;

    for (int i = 0; i < totalRegs; i++) {
        Pago p = archivoPagos.Leer(i);

        if (!p.getEstado()) continue;


        totalRecaudado += p.getMonto();
    }

    cout << "======================================" << endl;
    cout << " Dinero TOTAL recaudado: $" << totalRecaudado << endl;
    cout << "======================================" << endl << endl;
}
