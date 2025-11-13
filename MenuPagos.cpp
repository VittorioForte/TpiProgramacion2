#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "MenuPagos.h"
#include "ArchivoPagos.h"
#include "ArchivoCarreras.h"
#include "ArchivoClientes.h"
#include "Pago.h"
#include "Carrera.h"
#include "Clientes.h"

using namespace std;

static void mostrarDetallePago(const Pago& pago, ArchivoCarreras& archCarreras, ArchivoClientes& archClientes) {
    cout << fixed << setprecision(2);
    cout << "ID Pago: " << pago.getIdPago() << endl;
    cout << "ID Carrera: " << pago.getIdCarrera() << endl;
    cout << "ID Cliente: " << pago.getIdCliente() << endl;
    cout << "Monto: $" << pago.getMonto() << endl;
    cout << "Estado: " << (pago.getPagado() ? "PAGADO" : "PENDIENTE") << endl;

    int posCarrera = archCarreras.Buscar(pago.getIdCarrera());
    if (posCarrera != -1) {
        Carrera carrera = archCarreras.Leer(posCarrera);
        if (carrera.getEstado()) {
            cout << "Categoria: " << carrera.getCategoria().getNombreCat();
            cout << " | Fecha: " << carrera.getFecha().toString();
            cout << " | Hora: " << carrera.getHoraInicio() << endl;
        }
    }

    if (pago.getIdCliente() != 0) {
        int posCliente = archClientes.BuscarPorID(pago.getIdCliente());
        if (posCliente != -1) {
            Cliente cli = archClientes.Leer(posCliente);
            if (cli.getEstado()) {
                cout << "Responsable: " << cli.getNombre() << " " << cli.getApellido() << endl;
            }
        }
    }
    cout << "--------------------------------------" << endl;
}

void menuPagos() {
    ArchivoPagos archPagos("pagos.dat");
    ArchivoCarreras archCarreras("carreras.dat");
    ArchivoClientes archClientes("clientes.dat");
    int opcion;

    do {
        system("cls");
        cout << "=========== MENU DE PAGOS ===========" << endl;
        cout << "1) Listar pagos pendientes" << endl;
        cout << "2) Registrar pago" << endl;
        cout << "3) Listar historial de pagos" << endl;
        cout << "0) Volver" << endl;
        cout << "=====================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
        case 1: {
            int total = archPagos.CantidadRegistros();
            if (total == 0) {
                cout << "No hay pagos registrados." << endl;
                break;
            }
            bool hayPendientes = false;
            for (int i = 0; i < total; i++) {
                Pago pago = archPagos.Leer(i);
                if (!pago.getEstado() || pago.getPagado()) continue;
                if (!hayPendientes) {
                    cout << "=== PAGOS PENDIENTES ===" << endl;
                    hayPendientes = true;
                }
                mostrarDetallePago(pago, archCarreras, archClientes);
            }
            if (!hayPendientes) {
                cout << "No hay pagos pendientes." << endl;
            }
            break;
        }
        case 2: {
            int idCarrera;
            cout << "Ingrese ID de la carrera a cobrar: ";
            cin >> idCarrera;

            int posCarrera = archCarreras.Buscar(idCarrera);
            if (posCarrera == -1) {
                cout << "No se encontro una carrera con ese ID." << endl;
                break;
            }

            Carrera carrera = archCarreras.Leer(posCarrera);
            if (!carrera.getEstado()) {
                cout << "La carrera indicada se encuentra eliminada." << endl;
                break;
            }

            int posPago = archPagos.BuscarPorCarrera(idCarrera);
            Pago pago;
            if (posPago != -1) {
                pago = archPagos.Leer(posPago);
            } else {
                pago.setIdPago(archPagos.CantidadRegistros() + 1);
                pago.setIdCarrera(idCarrera);
                pago.setIdCliente(carrera.getIdClienteResponsable());
                pago.setMonto(carrera.getMonto());
                pago.setPagado(false);
                pago.setEstado(true);
            }

            if (pago.getPagado()) {
                cout << "La carrera ya se encuentra abonada." << endl;
                break;
            }

            cout << fixed << setprecision(2);
            cout << "Monto a abonar: $" << carrera.getMonto() << endl;
            cout << "Confirmar cobro? (1=SI / 0=NO): ";
            int confirmar;
            cin >> confirmar;
            if (confirmar != 1) {
                cout << "Operacion cancelada." << endl;
                break;
            }

            carrera.setPagado(true);
            if (!archCarreras.Guardar(carrera, posCarrera)) {
                cout << "Error al actualizar la carrera." << endl;
                break;
            }

            pago.setPagado(true);
            pago.setMonto(carrera.getMonto());
            pago.setIdCliente(carrera.getIdClienteResponsable());

            bool okPago;
            if (posPago != -1) {
                okPago = archPagos.Guardar(pago, posPago);
            } else {
                okPago = archPagos.Guardar(pago);
            }

            if (okPago) {
                cout << "Pago registrado correctamente." << endl;
            } else {
                cout << "Error al registrar el pago." << endl;
            }
            break;
        }
        case 3: {
            int total = archPagos.CantidadRegistros();
            if (total == 0) {
                cout << "No hay pagos registrados." << endl;
                break;
            }
            cout << "=== HISTORIAL DE PAGOS ===" << endl;
            for (int i = 0; i < total; i++) {
                Pago pago = archPagos.Leer(i);
                if (!pago.getEstado()) continue;
                mostrarDetallePago(pago, archCarreras, archClientes);
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

