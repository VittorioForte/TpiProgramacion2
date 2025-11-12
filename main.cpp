#include <iostream>
#include <cstdlib>
#include "MenuClientes.h"
#include "Clientes.h"
#include "MenuCarreras.h"
#include "Carrera.h"
#include "Participantes.h"

using namespace std;

int main() {
    int opcion;

    do {
        system("cls");
        cout << "====================================\n";
        cout << " SISTEMA DE GESTION DE KARTODROMO\n";
        cout << "====================================\n\n";
        cout << "1. Clientes" <<endl;
        cout << "2. Carreras" <<endl;
        cout << "3. Pagos" <<endl;
        cout << "4. Listados e Informes" <<endl;
        cout << "0. Salir" <<endl<<endl;
        cout << "Seleccione una opcion: " <<endl;
        cin >> opcion;

        system("cls");

        switch (opcion) {
            case 1: menuClientes(); break;
            case 2: menuCarreras() ; break;
            case 3: cout << "menuPagos"; break;
            case 4: cout << "menuListados"; break;
            case 0: cout << "Saliendo del sistema..."; break;
            default: cout << "Opcion invalida."; break;
        }

        system("pause");
    } while (opcion != 0);

    return 0;
}
