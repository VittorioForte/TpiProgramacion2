#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

class Clientes {
private:
    bool estado;
    int idCliente;
    string nombre;
    string apellido;
    string telefono;
    string dni;

public:
    Clientes();
    Clientes(int aIdCliente, const string &aNombre, const string &aApellido,
             const string &aTelefono, const string &aDni, bool aEstado = true);

    // GETTERS
    int getIdCliente() const;
    const string &getNombre() const;
    const string &getApellido() const;
    const string &getTelefono() const;
    const string &getDni() const;
    bool getEstado() const;

    // SETTERS
    void setIdCliente(int aIdCliente);
    void setNombre(const string &aNombre);
    void setApellido(const string &aApellido);
    void setTelefono(const string &aTelefono);
    void setDni(const string &aDni);
    void setEstado(bool aEstado);

    // METODOS ADICIONALES
    void cargar(int nuevoId);
    void mostrar() const;
};

void menuClientes(vector<Clientes> &clientes);
const Clientes *buscarClientePorId(const vector<Clientes> &clientes, int idCliente);
const Clientes *buscarClientePorDni(const vector<Clientes> &clientes, const string &dni);

bool guardarClientes(const vector<Clientes> &clientes, const string &rutaArchivo);
bool cargarClientes(vector<Clientes> &clientes, const string &rutaArchivo);

#endif // CLIENTES_H_INCLUDED
