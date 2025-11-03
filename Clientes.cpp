#include "clientes.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <utility>

using namespace std;

Clientes::Clientes()
    : estado(false), idCliente(0) {}

Clientes::Clientes(int aIdCliente, const string &aNombre, const string &aApellido,
                   const string &aTelefono, const string &aDni, bool aEstado)
    : estado(aEstado), idCliente(aIdCliente), nombre(aNombre), apellido(aApellido), telefono(aTelefono), dni(aDni) {}

int Clientes::getIdCliente() const { return idCliente; }

const string &Clientes::getNombre() const { return nombre; }

const string &Clientes::getApellido() const { return apellido; }

const string &Clientes::getTelefono() const { return telefono; }

const string &Clientes::getDni() const { return dni; }

bool Clientes::getEstado() const { return estado; }

void Clientes::setIdCliente(int aIdCliente) { idCliente = aIdCliente; }

void Clientes::setNombre(const string &aNombre) { nombre = aNombre; }

void Clientes::setApellido(const string &aApellido) { apellido = aApellido; }

void Clientes::setTelefono(const string &aTelefono) { telefono = aTelefono; }

void Clientes::setDni(const string &aDni) { dni = aDni; }

void Clientes::setEstado(bool aEstado) { estado = aEstado; }

void Clientes::cargar(int nuevoId) {
    idCliente = nuevoId;
    estado = true;

    cout << "Ingrese nombre del cliente: ";
    getline(cin, nombre);

    cout << "Ingrese apellido del cliente: ";
    getline(cin, apellido);

    cout << "Ingrese numero de telefono: ";
    getline(cin, telefono);

    cout << "Ingrese DNI: ";
    getline(cin, dni);
}

void Clientes::mostrar() const {
    cout << "--------------------------------" << endl;
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Apellido: " << apellido << endl;
    cout << "Telefono: " << telefono << endl;
    cout << "DNI: " << dni << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
}

static void mostrarListadoClientes(const vector<Clientes> &clientes) {
    if (clientes.empty()) {
        cout << "No hay clientes registrados." << endl;
        return;
    }

    cout << "======= CLIENTES REGISTRADOS =======" << endl;
    for (const Clientes &cliente : clientes) {
        cliente.mostrar();
    }
}

const Clientes *buscarClientePorId(const vector<Clientes> &clientes, int idCliente) {
    auto it = find_if(clientes.begin(), clientes.end(),
                           [idCliente](const Clientes &cliente) { return cliente.getIdCliente() == idCliente; });
    if (it == clientes.end()) {
        return nullptr;
    }
    return &(*it);
}

const Clientes *buscarClientePorDni(const vector<Clientes> &clientes, const string &dni) {
    auto it = find_if(clientes.begin(), clientes.end(),
                           [&dni](const Clientes &cliente) { return cliente.getDni() == dni; });
    if (it == clientes.end()) {
        return nullptr;
    }
    return &(*it);
}

void menuClientes(vector<Clientes> &clientes) {
    int opcion = -1;
    do {
        cout << "======= MENU CLIENTES =======" << endl;
        cout << "1) Registrar cliente" << endl;
        cout << "2) Listar clientes" << endl;
        cout << "3) Buscar cliente por DNI" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                Clientes nuevoCliente;
                nuevoCliente.cargar(static_cast<int>(clientes.size()) + 1);
                clientes.push_back(nuevoCliente);
                cout << "Cliente registrado con exito." << endl;
                break;
            }
            case 2: {
                mostrarListadoClientes(clientes);
                break;
            }
            case 3: {
                string dni;
                cout << "Ingrese DNI a buscar: ";
                getline(cin, dni);
                const Clientes *cliente = buscarClientePorDni(clientes, dni);
                if (cliente == nullptr) {
                    cout << "No se encontro un cliente con ese DNI." << endl;
                } else {
                    cliente->mostrar();
                }
                break;
            }
            case 0:
                cout << "Volviendo al menu principal..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
                break;
        }
    } while (opcion != 0);
}

static void escribirString(ofstream &out, const string &valor) {
    size_t longitud = valor.size();
    out.write(reinterpret_cast<const char *>(&longitud), sizeof(longitud));
    if (longitud > 0) {
        out.write(valor.data(), static_cast<streamsize>(longitud));
    }
}

static bool leerString(ifstream &in, string &valor) {
    size_t longitud = 0;
    in.read(reinterpret_cast<char *>(&longitud), sizeof(longitud));
    if (!in) {
        return false;
    }
    string temporal;
    temporal.resize(longitud);
    if (longitud > 0) {
        in.read(temporal.data(), static_cast<streamsize>(longitud));
        if (!in) {
            return false;
        }
    }
    valor = move(temporal);
    return true;
}

bool guardarClientes(const vector<Clientes> &clientes, const string &rutaArchivo) {
    ofstream out(rutaArchivo, ios::binary | ios::trunc);
    if (!out) {
        return false;
    }

    size_t cantidad = clientes.size();
    out.write(reinterpret_cast<const char *>(&cantidad), sizeof(cantidad));

    for (const Clientes &cliente : clientes) {
        int id = cliente.getIdCliente();
        out.write(reinterpret_cast<const char *>(&id), sizeof(id));

        char estado = cliente.getEstado() ? 1 : 0;
        out.write(reinterpret_cast<const char *>(&estado), sizeof(estado));

        escribirString(out, cliente.getNombre());
        escribirString(out, cliente.getApellido());
        escribirString(out, cliente.getTelefono());
        escribirString(out, cliente.getDni());
    }

    return out.good();
}

bool cargarClientes(vector<Clientes> &clientes, const string &rutaArchivo) {
    clientes.clear();

    ifstream in(rutaArchivo, ios::binary);
    if (!in) {
        return true;
    }

    size_t cantidad = 0;
    in.read(reinterpret_cast<char *>(&cantidad), sizeof(cantidad));
    if (!in) {
        return false;
    }

    vector<Clientes> cargados;
    cargados.reserve(cantidad);

    for (size_t i = 0; i < cantidad; ++i) {
        int id = 0;
        char estado = 0;
        string nombre;
        string apellido;
        string telefono;
        string dni;

        in.read(reinterpret_cast<char *>(&id), sizeof(id));
        in.read(reinterpret_cast<char *>(&estado), sizeof(estado));
        if (!in || !leerString(in, nombre) || !leerString(in, apellido) || !leerString(in, telefono) ||
            !leerString(in, dni)) {
            return false;
        }

        Clientes cliente;
        cliente.setIdCliente(id);
        cliente.setEstado(estado != 0);
        cliente.setNombre(nombre);
        cliente.setApellido(apellido);
        cliente.setTelefono(telefono);
        cliente.setDni(dni);

        cargados.push_back(cliente);
    }

    clientes = move(cargados);
    return true;
}
