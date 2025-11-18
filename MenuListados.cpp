#include <iostream>
#include <cstring>
#include <cstdlib>
#include "MenuListados.h"
#include "ArchivoCarreras.h"
#include "Carrera.h"
#include "ArchivoPagos.h"
#include "Pago.h"

using namespace std;

class RegistroTiempo {
private:
    char _nombre[50];
    double _tiempoVuelta;
    char _fecha[20];
    int _idCarrera;

public:
    RegistroTiempo() {
        strcpy(_nombre, "");
        strcpy(_fecha, "");
        _tiempoVuelta = 0;
        _idCarrera = 0;
    }

    void setDatos(const char* n, double t, const char* f, int id) {
        strcpy(_nombre, n);
        strcpy(_fecha, f);
        _tiempoVuelta = t;
        _idCarrera = id;
    }

    double getTiempoVuelta() const { return _tiempoVuelta; }
    const char* getNombre() const { return _nombre; }
    const char* getFecha() const { return _fecha; }
    int getIdCarrera() const { return _idCarrera; }
};

void ordenarPorTiempo(RegistroTiempo lista[], int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (lista[j].getTiempoVuelta() > lista[j + 1].getTiempoVuelta()) {
                RegistroTiempo aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
}

void listarPodioCategoria(ArchivoCarreras& arch, int idCat, const char* nombreCat) {
    int totalCarreras = arch.CantidadRegistros();

    if (totalCarreras == 0) {
        cout << "No hay carreras registradas." << endl;
        return;
    }

    int capacidadMaxima = totalCarreras * 10;

    RegistroTiempo *lista = new RegistroTiempo[capacidadMaxima];
    if (lista == nullptr) {
        cout << "Error: No hay memoria suficiente." << endl;
        return;
    }

    int cantidad = 0;

    for (int i = 0; i < totalCarreras; i++) {
        Carrera c = arch.Leer(i);

        if (!c.getEstado()) continue;
        if (c.getEstadoCarrera() == 0) continue;
        if (c.getCategoria().getIdCategoria() != idCat) continue;

        int cupos = c.getCantParticipantes();
        for (int j = 0; j < cupos; j++) {
            if (cantidad >= capacidadMaxima) break;

            const Participantes& p = c.getParticipante(j);
            string fechaStr = c.getFecha().toString();

            lista[cantidad].setDatos(
                p.getNombre(),
                p.getTiempoVueltas(),
                fechaStr.c_str(),
                c.getIdCarrera()
            );

            cantidad++;
        }
    }

    cout << "---------------------------------------" << endl;
    cout << " CATEGORIA " << nombreCat << endl;
    cout << "---------------------------------------" << endl;

    if (cantidad == 0) {
        cout << "No hay tiempos registrados para esta categoria." << endl;
    }
    else {
        ordenarPorTiempo(lista, cantidad);

        int top = (cantidad < 3) ? cantidad : 3;

        for (int i = 0; i < top; i++) {
            cout << i + 1 << ") " << lista[i].getNombre()
                 << " (" << lista[i].getTiempoVuelta() << " min/vuelta)" << endl;
            cout << "    [Fecha: " << lista[i].getFecha() << " - ID Carrera: " << lista[i].getIdCarrera() << "]" << endl;
        }
    }
    cout << endl;
    delete[] lista;
}

void mostrarRecaudacionMensual(ArchivoPagos& archPagos) {
    int totalPagos = archPagos.CantidadRegistros();

    int recaudacion[13] = {0};
    int totalGeneral = 0;

    bool huboVentas = false;

    for (int i = 0; i < totalPagos; i++) {
        Pago p = archPagos.Leer(i);

        if (p.getEstado()) {
            int mes = p.getFechaPago().getMes();
            int monto = (int)p.getMonto();

            if (mes >= 1 && mes <= 12) {
                recaudacion[mes] += monto;

                totalGeneral += monto;

                huboVentas = true;
            }
        }
    }

    cout << "=== RECAUDACION POR MES ===" << endl << endl;

    if (!huboVentas) {
        cout << "No hay pagos registrados." << endl;
        return;
    }

    const char* nombresMeses[] = {"", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

    for (int i = 1; i <= 12; i++) {
        if (recaudacion[i] > 0) {
            cout << "Mes " << i << " (" << nombresMeses[i] << "): \t$ " << recaudacion[i] << endl;
        }
    }

    cout << endl;
    cout << "---------------------------------------" << endl;
    cout << " TOTAL ANUAL ACUMULADO: \t$ " << totalGeneral << endl;
    cout << "---------------------------------------" << endl;
}

void menuListados() {
    ArchivoCarreras archivoCarreras("carreras.dat");
    ArchivoPagos archivoPagos("pagos.dat");
    int opcion;

    do {
        system("cls");
        cout << "=======================================" << endl;
        cout << "===      MENU DE INFORMES           ===" << endl;
        cout << "=======================================" << endl;
        cout << "1 - Podio historico (Mejores tiempos por vuelta)" << endl;
        cout << "2 - Recaudacion total por mes" << endl;
        cout << "0 - Volver al menu anterior" << endl;
        cout << "---------------------------------------" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
        case 1:
            system("cls");
            cout << "=== PODIOS HISTORICOS POR TIEMPO DE VUELTA ===" << endl << endl;

            listarPodioCategoria(archivoCarreras, 1, "PROFESIONAL");
            listarPodioCategoria(archivoCarreras, 2, "AMATEUR");
            listarPodioCategoria(archivoCarreras, 3, "INFANTIL");

            cout << endl;
            system("pause");
            break;

        case 2:
            system("cls");
            mostrarRecaudacionMensual(archivoPagos);
            cout << endl;
            system("pause");
            break;

        case 0:
            break;

        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);
}
