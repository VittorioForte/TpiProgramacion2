#include <iostream>
#include "clientes.h"


using namespace std;

class clientes {
private:
    bool estado;
    int idCliente;
    char nombre[30], apellido[30], telefono[20], dni[10];

public:

    //GETTERS
    int getIdCliente();
    char* getNombre();
    char* getApellido();
    char* getTelefono();
    char*getDni();
    bool getEstado();

    //SETTERS


    //METODOS ADICIONALES
};

void menuClientes() {
    cout << "Menu de clientes\n";
}

