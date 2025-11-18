#include <iostream>
#include <cstdlib>
#include <windows.h>
#include "MenuClientes.h"
#include "Clientes.h"
#include "MenuCarreras.h"
#include "Carrera.h"
#include "Participantes.h"
#include "MenuListados.h"
#include "MenuPagos.h"


using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    int opcion;

    do {
        system("cls");
        cout << "===================================="<<endl;
        cout << " SISTEMA DE GESTION DE KARTODROMO"<<endl;
        cout << "===================================="<<endl<<endl;
        cout << "   1. Clientes" <<endl;
        cout << "   2. Carreras" <<endl;
        cout << "   3. Pagos" <<endl;
        cout << "   4. Listados e Informes" <<endl;
        cout << "   0. Salir" <<endl<<endl;
        cout << "================================"<<endl;
        cout << "   Seleccione una opcion: ";

        cin >> opcion;

        system("cls");

        switch (opcion) {
            case 1: menuClientes(); break;
            case 2: menuCarreras() ; break;
            case 3: menuPagos(); break;
            case 4: menuListados(); break;
            case 0: cout << "Saliendo del sistema..."; break;
            default: cout << "Opcion invalida."; break;
        }

        system("pause");
    } while (opcion != 0);

    return 0;
}
