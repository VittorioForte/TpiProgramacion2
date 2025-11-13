#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "Clientes.h"
#include "ArchivoClientes.h"
#include "ArchivoPagos.h"
#include "ArchivoCarreras.h"
#include "Pago.h"
#include "Carrera.h"
using namespace std;

static void mostrarHistorialPagosCliente(int idCliente) {
    ArchivoPagos archPagos("pagos.dat");
    ArchivoCarreras archCarreras("carreras.dat");

    int total = archPagos.CantidadRegistros();
    bool encontro = false;

    for (int i = 0; i < total; i++) {
        Pago pago = archPagos.Leer(i);
        if (!pago.getEstado()) continue;
        if (pago.getIdCliente() != idCliente) continue;

        if (!encontro) {
            cout << endl << "Historial de pagos:" << endl;
            encontro = true;
        }

        cout << fixed << setprecision(2);
        cout << "- ID Pago: " << pago.getIdPago();
        cout << " | ID Carrera: " << pago.getIdCarrera();
        cout << " | Monto: $" << pago.getMonto();
        cout << " | Estado: " << (pago.getPagado() ? "PAGADO" : "PENDIENTE") << endl;

        int posCarrera = archCarreras.Buscar(pago.getIdCarrera());
        if (posCarrera != -1) {
            Carrera carrera = archCarreras.Leer(posCarrera);
            if (carrera.getEstado()) {
                cout << "  Categoria: " << carrera.getCategoria().getNombreCat();
                cout << " | Fecha: " << carrera.getFecha().toString();
                cout << " | Hora: " << carrera.getHoraInicio() << endl;
            }
        }
    }

    if (!encontro) {
        cout << endl << "Historial de pagos: Sin registros." << endl;
    }
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
                for (int i = 0; i < cant; i++) {
                    Cliente c = archClientes.Leer(i);
                    if (c.getEstado()) {
                        c.mostrar();
                        mostrarHistorialPagosCliente(c.getIdCliente());
                    }
                }
                break;
            }
            case 3: {
                int dni;
                cout << "Ingrese DNI a buscar: ";
                cin >> dni;
                int pos = archClientes.BuscarPorDNI(dni);
                if (pos == -1) cout << "Cliente no encontrado.";
                else {
                    Cliente c = archClientes.Leer(pos);
                    c.mostrar();
                    mostrarHistorialPagosCliente(c.getIdCliente());
                }
                break;
            }
            case 4: {
                int dni;
                cout << "Ingrese DNI del cliente a modificar: ";
                cin >> dni;
                int pos = archClientes.BuscarPorDNI(dni);
                if (pos == -1) cout << "Cliente no encontrado.";
                else {
                    Cliente c = archClientes.Leer(pos);
                    cout << "Datos actuales:\n";
                    c.mostrar();
                    mostrarHistorialPagosCliente(c.getIdCliente());
                    cout << "Ingrese nuevos datos:";
                    c.cargar();
                    c.setIdCliente(pos + 1);
                    if (archClientes.Guardar(c, pos))
                        cout << "Cliente modificado correctamente.";
                    else
                        cout << "Error al modificar cliente.";
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
