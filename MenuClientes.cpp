#include <iostream>
#include <cstdlib>
#include "Clientes.h"
#include "ArchivoClientes.h"
#include "ArchivoPagos.h"
#include "archivoCarreras.h"
#include "Pago.h"
#include "rlutil.h"
#include "Carrera.h"
using namespace std;

namespace {
    void mostrarHistorialPagosCliente(const Cliente& cliente) {
        ArchivoPagos archivoPagos("pagos.dat");
        ArchivoCarreras archivoCarreras("carreras.dat");

        cout << "Historial de pagos:" << endl;
        int totalPagos = archivoPagos.CantidadRegistros();
        bool hayPagos = false;
        for (int i = 0; i < totalPagos; i++) {
            Pago pago = archivoPagos.Leer(i);
            if (pago.getIdCliente() == cliente.getIdCliente()) {
                hayPagos = true;
                cout << "- Carrera ID: " << pago.getIdCarrera();
                int posCarrera = archivoCarreras.Buscar(pago.getIdCarrera());
                if (posCarrera != -1) {
                    Carrera carrera = archivoCarreras.Leer(posCarrera);
                    cout << " | Categoria: " << carrera.getCategoria().getNombreCat();
                    cout << " | Fecha: " << carrera.getFecha().toString();
                }
                else {
                    cout << " | Categoria: No disponible";
                }
                cout << " | Monto: $" << pago.getMonto();
                cout << " | Estado: " << (pago.getPagado() ? "PAGADO" : "PENDIENTE");
                if (pago.getPagado()) {
                    Fecha fechaPago = pago.getFechaPago();
                    if (fechaPago.getDia() != 0 || fechaPago.getMes() != 0 || fechaPago.getAnio() != 0) {
                        cout << " | Fecha de pago: " << fechaPago.toString();
                    }
                }
                cout << endl;
            }
        }
        if (!hayPagos) {
            cout << "Sin pagos registrados." << endl;
        }
    }
}

void dibujarCuadroClientes() {
    rlutil::setBackgroundColor(rlutil::BLUE);
    rlutil::setColor(rlutil::WHITE);

    rlutil::locate(1, 1);
    for(int i=0; i<80; i++) cout << " ";

    rlutil::locate(1, 1);  cout << "ID";
    rlutil::locate(8, 1);  cout << "DNI";
    rlutil::locate(20, 1); cout << "NOMBRE";
    rlutil::locate(40, 1); cout << "APELLIDO";
    rlutil::locate(60, 1); cout << "TELEFONO";

    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
}

void menuClientes() {
    int opcion;
    ArchivoClientes archClientes("clientes.dat");

    do {
        system("cls");
        cout << "===== MENU DE CLIENTES =====" << endl;
        cout << "1. Registrar nuevo cliente" << endl;
        cout << "2. Listar todos los clientes" << endl;
        cout << "3. Buscar cliente por DNI" << endl;
        cout << "4. Modificar cliente" << endl;
        cout << "5. Eliminar cliente" << endl;
        cout << "0. Volver al menu principal" << endl<< endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opcion;

        system("cls");

        switch (opcion) {
            case 1: {
                Cliente c;
                c.cargar();
                int nuevoId = archClientes.CantidadRegistros() + 1;
                c.setIdCliente(nuevoId);
                if (archClientes.Guardar(c))
                    cout << "Cliente guardado correctamente.";
                else
                    cout << "Error al guardar el cliente.";
                break;
            }
            case 2: {
                int cant = archClientes.CantidadRegistros();

                dibujarCuadroClientes();

                int fila = 3;
                for (int i = 0; i < cant; i++) {
                    Cliente c = archClientes.Leer(i);
                    if (c.getEstado()) {
                        c.mostrar(fila);
                        fila++;
                    }
                }
                rlutil::locate(1, fila + 2);
                break;
            }
            case 3: {
                int dni;
                cout << "Ingrese DNI a buscar: ";
                cin >> dni;
                rlutil::cls();

                int pos = archClientes.BuscarPorDNI(dni);
                if (pos == -1) {
                    cout << "Cliente no encontrado." << endl;
                }
                else {
                    dibujarCuadroClientes();

                    Cliente c = archClientes.Leer(pos);
                    c.mostrar(3);

                    rlutil::locate(1, 5);
                    cout << "Cliente encontrado." << endl;
                }
                break;
            }
            case 4: {
                int dni;
                cout << "Ingrese DNI del cliente a modificar: ";
                cin >> dni;
                rlutil::cls();

                int pos = archClientes.BuscarPorDNI(dni);
                if (pos == -1) {
                    cout << "Cliente no encontrado." << endl;
                } else {
                    Cliente c = archClientes.Leer(pos);

                    cout << "DATOS ACTUALES:" << endl;
                    dibujarCuadroClientes();
                    c.mostrar(3);

                    cout << endl << endl << "INGRESE NUEVOS DATOS:" << endl;
                    c.cargar();

                    if (archClientes.Guardar(c, pos)) {
                        cout << "Cliente modificado." << endl;
                    } else {
                        cout << "Error al modificar." << endl;
                    }
                }
                break;
            }
            case 5: {
                int dni;
                cout << "Ingrese DNI del cliente a eliminar: ";
                cin >> dni;
                int pos = archClientes.BuscarPorDNI(dni);
                if (pos == -1) cout << "Cliente no encontrado.";
                else {
                    Cliente c = archClientes.Leer(pos);
                    c.setEstado(false);
                    archClientes.Guardar(c, pos);
                    cout << "Cliente eliminado correctamente.";
                }
                break;
            }
            case 0: break;
            default: cout << "Opcion invalida."; break;
        }

        if (opcion != 0) {
            cout << endl;
            system("pause");
        }

    } while (opcion != 0);
}
