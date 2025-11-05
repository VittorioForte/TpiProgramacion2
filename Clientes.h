#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

class Cliente {
private:
    int idCliente;
    char nombre[30];
    char apellido[30];
    char telefono[20];
    int dni;
    bool estado;

public:
    void cargar();
    void mostrar() const;

    int getIdCliente() const { return idCliente; }
    int getDni() const { return dni; }
    const char* getNombre() const { return nombre; }
    const char* getApellido() const { return apellido; }
    bool getEstado() const { return estado; }

    void setEstado(bool e) { estado = e; }
    void setIdCliente(int id) { idCliente = id; }
};

#endif
