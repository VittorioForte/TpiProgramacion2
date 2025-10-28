#include <iostream>
#include <cstdlib>
using namespace std;

//Include .h files

#include "categorias.h"
#include "clientes.h"
#include "contratacion.h"
#include "participantes.h"
#include "carrera.h"



int main()
{
	int opcion;

	//Menu principal


	//testing testing
	do {
		system("cls");
		cout << "-----MENU PRINCIPAL-----\n";
		cout << "1) Carreras Historicas\n";
		cout << "2) Participantes\n";
		cout << "3) Clientes\n";
		cout << "4) Contrataciones\n";
		cout << "5) PODIO DE RECORDS\n";
		cout << "0) Salir\n";
		cout << "Seleccione una opcion: \n";

		cin >> opcion;

		switch (opcion){
			case 1:
				menuCarreras();
				break;
			case 2:
				//menuParticipantes();
				break;
			case 3:
				menuClientes();
				break;
			case 4:
				//menuContratacion();
				break;
			case 5:
				//menuRecords();
				break;
			case 0:
				cout << "Saliendo del programa...\n";
				break;

			default:
			    cout << "Opcion Invalida.\n";
				break;
		}

		system("pause");

	} while (opcion != 0);

	return 0;
}
