#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MenuCarreras.h"
#include "ArchivoCarreras.h"
#include "ArchivoClientes.h"
#include "ArchivoPagos.h"
#include "Carrera.h"
#include "Clientes.h"
#include "Pago.h"
#include "rlutil.h"

using namespace std;

void dibujarCuadroCarreras() {
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);

    rlutil::locate(1, 1);
    for(int i=0; i<80; i++) cout << " ";
    rlutil::locate(1, 1);  cout << "ID";
    rlutil::locate(4, 1);  cout << "ESTADO";
    rlutil::locate(16, 1); cout << "CATEGORIA";
    rlutil::locate(30, 1); cout << "VUELTAS";
    rlutil::locate(38, 1); cout << "PRECIO";
    rlutil::locate(50, 1); cout << "HORA";
    rlutil::locate(58, 1); cout << "NOMBRE RESPONSABLE";

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
}

void menuCarreras() {
    int opcion;
    ArchivoCarreras arch("carreras.dat");
    ArchivoClientes archClientes("clientes.dat");

    do {
        system("cls");
        cout << "======= MENU CARRERAS =======" << endl;
        cout << "1) Nueva carrera" << endl;
        cout << "2) Listar carreras" << endl;
        cout << "3) Buscar carrera por numero" << endl;
        cout << "4) Eliminar carrera" << endl;
        cout << "5) Finalizar carrera" << endl;
        cout << "0) Volver al menu principal" << endl;
        cout << "=============================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {

        case 1: {
            Carrera c;
            c.cargar();

            int opcCliente;
            int idAsignado = 0;

            cout << "El cliente responsable ya existe? (1=SI / 0=NO): ";
            cin >> opcCliente;

            if (opcCliente == 1) {
                int dniBusqueda;
                cout << "Ingrese DNI del cliente a buscar: ";
                cin >> dniBusqueda;

                int pos = archClientes.BuscarPorDNI(dniBusqueda);

                if (pos != -1) {
                    Cliente cli = archClientes.Leer(pos);
                    cout << "Cliente encontrado: " << cli.getNombre() << " " << cli.getApellido() << endl;
                    cout << "Asignando como responsable..." << endl;
                    idAsignado = cli.getIdCliente();
                } else {
                    cout << "Cliente no encontrado." << endl;
                    cout << "La carrera se guardara sin responsable." << endl;
                    idAsignado = 0;
                }
            }
            else {
                cout << "--- Carga de Nuevo Cliente Responsable ---" << endl;
                Cliente nuevoCliente;
                nuevoCliente.cargar();

                int nuevoIdCliente = archClientes.CantidadRegistros() + 1;
                nuevoCliente.setIdCliente(nuevoIdCliente);

                if (archClientes.Guardar(nuevoCliente)) {
                    cout << "Cliente nuevo guardado (ID: " << nuevoIdCliente << ")." << endl;
                    idAsignado = nuevoIdCliente;
                } else {
                    cout << "Error al guardar el nuevo cliente." << endl;
                    cout << "La carrera quedara sin responsable." << endl;
                    idAsignado = 0;
                }
            }

            c.setIdClienteResponsable(idAsignado);

            int nuevoID = arch.CantidadRegistros() + 1;
            c.setIdCarrera(nuevoID);

            if (arch.Guardar(c)) {
                cout << "Carrera guardada (ID: " << nuevoID << ")." << endl;
                if (idAsignado != 0) {
                    ArchivoPagos archivoPagos("pagos.dat");
                    Pago pago;
                    pago.setIdPago(archivoPagos.CantidadRegistros() + 1);
                    pago.setIdCarrera(c.getIdCarrera());
                    pago.setIdCliente(idAsignado);
                    pago.setMonto(c.getMonto());
                    pago.setPagado(false);
                    if (archivoPagos.Guardar(pago)) {
                        cout << "Pago pendiente generado para el responsable." << endl;
                    }
                    else {
                        cout << "No se pudo generar el registro de pago." << endl;
                    }
                }
            } else {
                cout << "Error al guardar la carrera." << endl;
            }
            break;
        }

        case 2: {
            int total = arch.CantidadRegistros();
            if (total == 0) { cout<<"No hay carreras"; break; }

            rlutil::cls();
            dibujarCuadroCarreras();

            int fila = 3;
            for (int i = 0; i < total; i++) {
                Carrera c = arch.Leer(i);
                if (c.getEstado()) {
                    c.mostrar(fila, archClientes);
                    rlutil::locate(1, fila + 2);
                    for(int k=0; k<80; k++) cout << "-";
                    fila += 3;
                }
            }
            rlutil::locate(1, fila + 2);
            break;
        }
        case 3: {
            int id;
            cout << "Ingrese el numero de carrera a buscar: ";
            cin >> id;
            rlutil::cls();
            int pos = arch.Buscar(id);
            if (pos == -1) {
                cout << "No existe una carrera con ese ID." << endl;
            } else {
                Carrera c = arch.Leer(pos);
                if (!c.getEstado()) {
                    cout << "No existe una carrera con ese ID o fue eliminada." << endl;
                } else {
                    dibujarCuadroCarreras();
                    c.mostrar(3, archClientes);
                    rlutil::locate(1, 6);
                }
            }
            break;
        }

        case 4: {
            int id;
            cout << "Ingrese el numero de carrera a eliminar: ";
            cin >> id;

            int pos = arch.Buscar(id);
            if (pos == -1) {
                cout << "No se encontro una carrera con ese numero." << endl;
                break;
            }

            Carrera c = arch.Leer(pos);

            if (!c.getEstado()) {
                cout << "Esa carrera ya esta eliminada." << endl;
                break;
            }

            dibujarCuadroCarreras();
            c.mostrar(3, archClientes);
            cout << endl << "Desea eliminarla? (1=SI / 0=NO): ";
            int opc;
            cin >> opc;

            if (opc == 1) {
                c.setEstado(false);

                if (arch.Guardar(c, pos)) {
                    cout << "Carrera eliminada correctamente." << endl;
                } else {
                    cout << "Error al eliminar la carrera." << endl;
                }
            } else {
                cout << "Operacion cancelada." << endl;
            }
            break;
        }
        case 5: {
            int id;
            cout << "Ingrese el ID de la carrera a finalizar: ";
            cin >> id;
            rlutil::cls();

            int pos = arch.Buscar(id);
            if (pos == -1) {
                cout << "Carrera no encontrada." << endl;
            } else {
                Carrera c = arch.Leer(pos);
                if (!c.getEstado()) {
                    cout << "No se puede finalizar una carrera eliminada." << endl;
                } else if (c.getEstadoCarrera() == 1) {
                    cout << "Esta carrera ya fue finalizada anteriormente." << endl;
                    dibujarCuadroCarreras();
                    c.mostrar(3, archClientes);
                } else {
                    c.cargarResultados();

                    if (arch.Guardar(c, pos)) {
                        cout << "Carrera finalizada y tiempos guardados." << endl;
                    } else {
                        cout << "Error al guardar los cambios." << endl;
                    }
                }
            }
            break;
        }
        case 0:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
        if (opcion != 0) {
            cout << endl;
            system("pause");
        }
    } while (opcion != 0);
}
