#include <iostream>
#include <cstdlib>
#include "MenuCarreras.h"
#include "archivoCarreras.h"
#include "Carrera.h"
#include "Clientes.h"
#include "Participantes.h"

using namespace std;

void menuCarreras() {
    int opcion;
    ArchivoCarreras arch("carreras.dat");

    do {
        system("cls");
        cout << "======= MENU CARRERAS =======\n";
        cout << "1) Nueva carrera\n";
        cout << "2) Listar carreras con participantes\n";
        cout << "3) Buscar carrera por numero\n";
        cout << "4) Eliminar carrera\n";
        cout << "0) Volver al menu principal\n";
        cout << "=============================\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion) {

        case 1: {
            Carrera c;
            c.cargar();
            int nuevoID = arch.CantidadRegistros() + 1;
            c.setIdCarrera(nuevoID);

            if (!arch.Guardar(c)) {
                cout << "Error al guardar la carrera.\n";
                break;
            }

            cout << "Carrera guardada correctamente.\n";

            int numPart;
            cout << "\nCantidad de participantes: ";
            cin >> numPart;

            for (int i = 0; i < numPart; i++) {
                int dniBuscado;
                cout << "Ingrese DNI del participante #" << (i + 1) << ": ";
                cin >> dniBuscado;

                FILE *fc = fopen("clientes.dat", "rb");
                if (fc == NULL) {
                    cout << "No se pudo abrir el archivo de clientes.\n";
                    continue;
                }

                Cliente cli;
                bool encontradoCli = false;
                int idCli = -1;

                while (fread(&cli, sizeof(Cliente), 1, fc)) {
                    if (cli.getEstado() && cli.getDni() == dniBuscado) {
                        encontradoCli = true;
                        idCli = cli.getIdCliente();
                        break;
                    }
                }
                fclose(fc);

                if (encontradoCli) {
                    Participantes p;
                    p.setIdCarrera(nuevoID);
                    p.setIdCliente(idCli);
                    p.setHoraFinal(0.0);
                    p.setTiempoVueltas(0);
                    p.setEstado(true);
                    p.escribirDisco(-1);

                    cout << "Participante agregado: "
                         << cli.getNombre() << " "
                         << cli.getApellido()
                         << " (DNI: " << cli.getDni() << ")\n";
                } else {
                    cout << "No se encontró cliente con DNI " << dniBuscado << ".\n";
                }
            }
            break;
        }

        case 2: {
            int total = arch.CantidadRegistros();
            if (total == 0) {
                cout << "No hay carreras registradas.\n";
                break;
            }

            for (int i = 0; i < total; i++) {
                Carrera c = arch.Leer(i);
                if (!c.getEstado()) continue;

                c.mostrar();
                cout << "Participantes:\n";

                FILE *fp = fopen("participantes.dat", "rb");
                if (fp == NULL) {
                    cout << "   No hay participantes registrados.\n";
                    continue;
                }

                Participantes part;
                bool tienePart = false;

                while (fread(&part, sizeof(Participantes), 1, fp)) {
                    if (part.getEstado() && part.getIdCarrera() == c.getIdCarrera()) {
                        tienePart = true;

                        FILE *fc = fopen("clientes.dat", "rb");
                        if (fc != NULL) {
                            Cliente cli;
                            while (fread(&cli, sizeof(Cliente), 1, fc)) {
                                if (cli.getEstado() && cli.getIdCliente() == part.getIdCliente()) {
                                    cout << "   - " << cli.getNombre() << " "
                                         << cli.getApellido()
                                         << " | DNI: " << cli.getDni() << endl;
                                    break;
                                }
                            }
                            fclose(fc);
                        }
                    }
                }
                fclose(fp);
                if (!tienePart) cout << "   No hay participantes registrados.\n";
                cout << "-----------------------------------------\n";
            }
            break;
        }

        case 3: {
            int id;
            cout << "Ingrese el numero de carrera a buscar: ";
            cin >> id;

            Carrera c = arch.Leer(id - 1);
            if (!c.getEstado()) {
                cout << "No existe una carrera con ese ID o fue eliminada.\n";
                break;
            }

            c.mostrar();
            cout << "Participantes:\n";

            FILE *fp = fopen("participantes.dat", "rb");
            if (fp == NULL) {
                cout << "   No hay participantes registrados.\n";
                break;
            }

            Participantes part;
            bool tienePart = false;

            while (fread(&part, sizeof(Participantes), 1, fp)) {
                if (part.getEstado() && part.getIdCarrera() == id) {
                    tienePart = true;

                    FILE *fc = fopen("clientes.dat", "rb");
                    if (fc != NULL) {
                        Cliente cli;
                        while (fread(&cli, sizeof(Cliente), 1, fc)) {
                            if (cli.getEstado() && cli.getIdCliente() == part.getIdCliente()) {
                                cout << "   - " << cli.getNombre() << " "
                                     << cli.getApellido()
                                     << " | DNI: " << cli.getDni() << endl;
                                break;
                            }
                        }
                        fclose(fc);
                    }
                }
            }
            fclose(fp);
            if (!tienePart) cout << "   No hay participantes registrados.\n";
            break;
        }

        case 4: {
            int id;
            cout << "Ingrese el numero de carrera a eliminar: ";
            cin >> id;

            FILE *p = fopen("carreras.dat", "rb+");
            if (p == NULL) {
                cout << "No se pudo abrir el archivo de carreras.\n";
                break;
            }

            Carrera c;
            fseek(p, (id - 1) * sizeof(Carrera), SEEK_SET);
            if (fread(&c, sizeof(Carrera), 1, p) != 1) {
                cout << "No se encontró una carrera con ese número.\n";
                fclose(p);
                break;
            }

            if (!c.getEstado()) {
                cout << "Esa carrera ya esta eliminada.\n";
                fclose(p);
                break;
            }

            c.setEstado(false);
            fseek(p, (id - 1) * sizeof(Carrera), SEEK_SET);
            fwrite(&c, sizeof(Carrera), 1, p);
            fclose(p);

            cout << "Carrera eliminada correctamente.\n";
            break;

        }

        case 0:
            cout << "Volviendo al menu principal...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
            break;
        }

        if (opcion != 0) {
            cout << endl;
            system("pause");
        }

    } while (opcion != 0);
}
