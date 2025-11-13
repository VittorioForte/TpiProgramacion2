#include <iostream>
#include <cstdlib>
#include "MenuPagos.h"
#include "ArchivoPagos.h"
#include "archivoCarreras.h"
#include "ArchivoClientes.h"
#include "Carrera.h"
#include "Clientes.h"

using namespace std;

namespace {
    void mostrarDetallePago(const Pago& pago, ArchivoCarreras& archivoCarreras, ArchivoClientes& archivoClientes) {
        cout << "----------------------------------" << endl;
        cout << "ID Pago: " << pago.getIdPago() << endl;
        cout << "ID Carrera: " << pago.getIdCarrera() << endl;
        cout << "Monto: $" << pago.getMonto() << endl;
        cout << "Estado: " << (pago.getPagado() ? "PAGADO" : "PENDIENTE") << endl;

        int posCarrera = archivoCarreras.Buscar(pago.getIdCarrera());
        if (posCarrera != -1) {
            Carrera carrera = archivoCarreras.Leer(posCarrera);
            cout << "Categoria: " << carrera.getCategoria().getNombreCat() << endl;
            cout << "Fecha de carrera: " << carrera.getFecha().toString() << endl;
        }
        else {
            cout << "Categoria: No disponible" << endl;
        }

        int posCliente = archivoClientes.BuscarPorID(pago.getIdCliente());
        if (posCliente != -1) {
            Cliente cliente = archivoClientes.Leer(posCliente);
            cout << "Cliente responsable: " << cliente.getNombre() << " " << cliente.getApellido() << endl;
        }
        else {
            cout << "Cliente responsable: No disponible" << endl;
        }

        if (pago.getPagado()) {
            Fecha fechaPago = pago.getFechaPago();
            if (fechaPago.getDia() != 0 || fechaPago.getMes() != 0 || fechaPago.getAnio() != 0) {
                cout << "Fecha de pago: " << fechaPago.toString() << endl;
            }
        }
    }
}

void menuPagos() {
    ArchivoPagos archivoPagos("pagos.dat");
    ArchivoCarreras archivoCarreras("carreras.dat");
    ArchivoClientes archivoClientes("clientes.dat");
    int opcion;

    do {
        system("cls");
        cout << "======== MENU DE PAGOS ========" << endl;
        cout << "1) Pagos pendientes" << endl;
        cout << "2) Registrar pago" << endl;
        cout << "3) Historial por cliente" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {
        case 1: {
            int total = archivoPagos.CantidadRegistros();
            bool hayPendientes = false;
            for (int i = 0; i < total; i++) {
                Pago pago = archivoPagos.Leer(i);
                if (!pago.getPagado()) {
                    if (!hayPendientes) {
                        cout << "=== PAGOS PENDIENTES ===" << endl;
                    }
                    hayPendientes = true;
                    mostrarDetallePago(pago, archivoCarreras, archivoClientes);
                }
            }
            if (!hayPendientes) {
                cout << "No hay pagos pendientes." << endl;
            }
            break;
        }
        case 2: {
            int idCarrera;
            cout << "Ingrese ID de la carrera a registrar pago: ";
            cin >> idCarrera;

            int posPago = archivoPagos.BuscarPorCarrera(idCarrera);
            if (posPago == -1) {
                cout << "No se encontro un pago asociado a la carrera." << endl;
                break;
            }

            Pago pago = archivoPagos.Leer(posPago);
            if (pago.getPagado()) {
                cout << "La carrera ya se encuentra abonada." << endl;
                break;
            }

            mostrarDetallePago(pago, archivoCarreras, archivoClientes);

            int confirmar;
            cout << endl << "Confirmar registro del pago? (1=SI / 0=NO): ";
            cin >> confirmar;
            if (confirmar != 1) {
                cout << "Operacion cancelada." << endl;
                break;
            }

            cout << "Ingrese la fecha del pago:" << endl;
            Fecha fechaPago;
            fechaPago.Cargar();

            pago.setPagado(true);
            pago.setFechaPago(fechaPago);

            if (archivoPagos.Guardar(pago, posPago)) {
                int posCarrera = archivoCarreras.Buscar(idCarrera);
                if (posCarrera != -1) {
                    Carrera carrera = archivoCarreras.Leer(posCarrera);
                    carrera.setPagoRealizado(true);
                    archivoCarreras.Guardar(carrera, posCarrera);
                }
                cout << "Pago registrado correctamente." << endl;
            }
            else {
                cout << "Error al registrar el pago." << endl;
            }
            break;
        }
        case 3: {
            int idCliente;
            cout << "Ingrese ID de cliente: ";
            cin >> idCliente;

            int total = archivoPagos.CantidadRegistros();
            bool encontrado = false;
            for (int i = 0; i < total; i++) {
                Pago pago = archivoPagos.Leer(i);
                if (pago.getIdCliente() == idCliente) {
                    if (!encontrado) {
                        cout << "=== HISTORIAL DE PAGOS ===" << endl;
                    }
                    encontrado = true;
                    mostrarDetallePago(pago, archivoCarreras, archivoClientes);
                }
            }
            if (!encontrado) {
                cout << "El cliente no registra pagos." << endl;
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
