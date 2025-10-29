#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

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

void menuClientes();

#endif // CLIENTES_H_INCLUDED
