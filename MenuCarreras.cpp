#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include "MenuCarreras.h"
#include "ArchivoCarreras.h"
#include "ArchivoClientes.h"
#include "ArchivoPagos.h"
#include "Carrera.h"
#include "Clientes.h"
#include "Pago.h"

using namespace std;

void menuCarreras() {
    int opcion;
    ArchivoCarreras arch("carreras.dat");
    ArchivoClientes archClientes("clientes.dat");
    ArchivoPagos archPagos("pagos.dat");

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
                Pago pago;
                pago.setIdPago(archPagos.CantidadRegistros() + 1);
                pago.setIdCarrera(nuevoID);
                pago.setIdCliente(idAsignado);
                pago.setMonto(c.getMonto());
                pago.setPagado(false);
                pago.setEstado(true);
                if (archPagos.Guardar(pago)) {
                    cout << "Pago generado en estado pendiente." << endl;
                } else {
                    cout << "Error al generar el registro de pago." << endl;
                }
            } else {
                cout << "Error al guardar la carrera." << endl;
            }
            break;
        }

        case 2: {
            int total = arch.CantidadRegistros();
            if (total == 0) {
                cout << "No hay carreras registradas." << endl;
                break;
            }

            for (int i = 0; i < total; i++) {
                Carrera c = arch.Leer(i);
                if (!c.getEstado()) continue;
                c.mostrar();
                int posPago = archPagos.BuscarPorCarrera(c.getIdCarrera());
                if (posPago != -1) {
                    Pago pago = archPagos.Leer(posPago);
                    cout << "Monto pendiente: $" << fixed << setprecision(2) << pago.getMonto() << endl;
                    cout << "Situacion: " << (pago.getPagado() ? "PAGADO" : "PENDIENTE") << endl;
                } else {
                    cout << "No hay informacion de pago registrada." << endl;
                }
                cout << "----------------------------------" << endl;
                cout << "Datos responsable del pago:" << endl;
                int idResp = c.getIdClienteResponsable();
                if (idResp == 0) {
                    cout << "Sin responsable asignado." << endl;
                } else {
                    int posCli = archClientes.BuscarPorID(idResp);
                    if (posCli != -1) {
                        Cliente cli = archClientes.Leer(posCli);
                        cli.mostrar();
                    } else {
                        cout << "Error: ID de cliente no encontrado en el archivo." << endl;
                    }
                }
                cout << "==================================" << endl << endl;
            }
            break;
        }

        case 3: {
            int id;
            cout << "Ingrese el numero de carrera a buscar: ";
            cin >> id;

            int pos = arch.Buscar(id);
            if (pos == -1) {
                cout << "No existe una carrera con ese ID." << endl;
                break;
            }

            Carrera c = arch.Leer(pos);

            if (!c.getEstado()) {
                cout << "No existe una carrera con ese ID o fue eliminada." << endl;
                break;
            }

            c.mostrar();
            int posPago = archPagos.BuscarPorCarrera(c.getIdCarrera());
            if (posPago != -1) {
                Pago pago = archPagos.Leer(posPago);
                cout << "Monto de la carrera: $" << fixed << setprecision(2) << pago.getMonto() << endl;
                cout << "Estado del pago: " << (pago.getPagado() ? "PAGADO" : "PENDIENTE") << endl;
            } else {
                cout << "No hay informacion de pago registrada." << endl;
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

            cout << "Carrera encontrada:" << endl;
            c.mostrar();
            cout << endl << "Desea eliminarla? (1=SI / 0=NO): ";
            int opc;
            cin >> opc;

            if (opc == 1) {
                c.setEstado(false);

                if (arch.Guardar(c, pos)) {
                    cout << "Carrera eliminada correctamente." << endl;
                    int posPago = archPagos.BuscarPorCarrera(c.getIdCarrera());
                    if (posPago != -1) {
                        Pago pago = archPagos.Leer(posPago);
                        pago.setEstado(false);
                        archPagos.Guardar(pago, posPago);
                    }
                } else {
                    cout << "Error al eliminar la carrera." << endl;
                }
            } else {
                cout << "Operacion cancelada." << endl;
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
