#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "MenuPagos.h"
#include "ArchivoPagos.h"
#include "ArchivoCarreras.h"
#include "ArchivoClientes.h"
#include "Carrera.h"
#include "Clientes.h"
#include "Pago.h"
#include "rlutil.h"

using namespace std;

void dibujarCuadroPagos() {
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);

    rlutil::locate(1, 1);
    for(int i=0; i<80; i++) cout << " ";

    rlutil::locate(1, 1);  cout << "ID";
    rlutil::locate(8, 1);  cout << "MONTO";
    rlutil::locate(20, 1); cout << "FECHA PAGO";
    rlutil::locate(35, 1); cout << "CARRERA";
    rlutil::locate(55, 1); cout << "CLIENTE";

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
}

void menuPagos() {
    int opcion;
    ArchivoPagos archPagos("pagos.dat");
    ArchivoCarreras archCarreras("carreras.dat");
    ArchivoClientes archClientes("clientes.dat");

    do {
        system("cls");
        cout << "======== MENU DE PAGOS ========" << endl;
        cout << "1) Lista de pagos" << endl;
        cout << "2) Historial por cliente" << endl;
        cout << "3) Filtro por categoria" << endl;
        cout << "0) Volver" << endl;
        cout << "===============================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {

        case 1: {
            int total = archPagos.CantidadRegistros();
            if (total == 0) {
                cout << "No hay pagos registrados." << endl;
            } else {
                dibujarCuadroPagos();
                int fila = 3;
                for (int i = 0; i < total; i++) {
                    Pago p = archPagos.Leer(i);
                    if (p.getEstado()) {
                        p.mostrar(fila, archCarreras, archClientes);
                        fila++;
                    }
                }
                rlutil::locate(1, fila + 2);
            }

            cout << endl;
            system("pause");
            break;
        }

        case 2: {
            int dniBuscado;
            cout << "Ingrese DNI del cliente a buscar: ";
            cin >> dniBuscado;
            rlutil::cls();

            int posCli = archClientes.BuscarPorDNI(dniBuscado);
            if (posCli == -1) {
                cout << "Cliente no encontrado con ese DNI." << endl;
            }
            else {
                Cliente cli = archClientes.Leer(posCli);
                int idClienteEncontrado = cli.getIdCliente();

                cout << "Historial de Pagos de: " << cli.getNombre() << " " << cli.getApellido() << endl;
                dibujarCuadroPagos();

                int total = archPagos.CantidadRegistros();
                int fila = 4;
                bool encontroPagos = false;

                for (int i = 0; i < total; i++) {
                    Pago p = archPagos.Leer(i);
                    if (p.getEstado() && p.getIdCliente() == idClienteEncontrado) {
                        p.mostrar(fila, archCarreras, archClientes);
                        fila++;
                        encontroPagos = true;
                    }
                }

                if (!encontroPagos) {
                    rlutil::locate(1, 4);
                    cout << "Este cliente no tiene pagos registrados." << endl;
                }
                rlutil::locate(1, fila + 2);
            }

            cout << endl;
            system("pause");
            break;
        }

        case 3: {
            string catBuscada;
            cout << "Ingrese Categoria (PROFESIONAL / AMATEUR / INFANTIL): ";
            cin >> catBuscada;
            rlutil::cls();

            dibujarCuadroPagos();
            int total = archPagos.CantidadRegistros();
            int fila = 3;
            bool encontroPagos = false;

            for (int i = 0; i < total; i++) {
                Pago p = archPagos.Leer(i);
                if (p.getEstado()) {
                    int posCarrera = archCarreras.Buscar(p.getIdCarrera());
                    if (posCarrera != -1) {
                        Carrera c = archCarreras.Leer(posCarrera);
                        string catActual = c.getCategoria().getNombreCat();

                        if (catActual == catBuscada) {
                            p.mostrar(fila, archCarreras, archClientes);
                            fila++;
                            encontroPagos = true;
                        }
                    }
                }
            }

            if (!encontroPagos) {
                rlutil::locate(1, 3);
                cout << "No hay pagos registrados para la categoria " << catBuscada << "." << endl;
            }
            rlutil::locate(1, fila + 2);

            cout << endl;
            system("pause");
            break;
        }

        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;

        default:
            cout << "Opcion invalida." << endl;
            cout << endl;
            system("pause");
            break;
        }

    } while (opcion != 0);
}
