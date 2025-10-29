#include <iostream>
#include <cstdlib>
#include "carrera.h"

using namespace std;

class carrera{
private:
    bool estado;
    int idCarrera, idCategoria, cantParticipantes;
    double horaInicio;
    //Fecha: fecha

public:

    //GETTERS


    //SETTERS


    //METODOS ADICIONALES
};


void menuCarreras(){

    int opcion;
    do {
        system("cls");
        cout << "=======MENU CARRERAS=======\n";
        cout << "1) Nueva carrera\n";
        cout << "2) Listar carreras \n";
        cout << "3) Buscar carrera por numero\n";
        cout << "4) listar carrera por participante\n";
        cout << "0) Volver para atras\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;


        switch (opcion) {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 0: cout << "Volviendo al Menu Principal...\n"; break;

        }

    } while (opcion != 0);


}
