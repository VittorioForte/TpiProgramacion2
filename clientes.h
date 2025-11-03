#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <cstdio>

class Clientes {
private:
    bool estado;
    int idCliente;
    char nombre[30];
    char apellido[30];
    char telefono[20];
    char dni[10];

public:
    Clientes();

    //GETTERS
    int getIdCliente() const;
    const char *getNombre() const;
    const char *getApellido() const;
    const char *getTelefono() const;
    const char *getDni() const;
    bool getEstado() const;

    //SETTERS
    void setIdCliente(int aId);
    void setNombre(const char *aNombre);
    void setApellido(const char *aApellido);
    void setTelefono(const char *aTelefono);
    void setDni(const char *aDni);
    void setEstado(bool aEstado);

    //METODOS ADICIONALES
    void cargar(int nuevoId);
    void mostrar() const;
    bool grabarEnDisco() const;
    bool leerDeDisco(int pos);
    bool modificarEnDisco(int pos) const;
};

void menuClientes();

#endif // CLIENTES_H_INCLUDED
