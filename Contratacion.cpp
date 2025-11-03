#include "contratacion.h"

#include "carrera.h"
#include "clientes.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <limits>
#include <utility>

using namespace std;

Contratacion::Contratacion()
    : estado(false), idContratacion(0), idCliente(0), idCarrera(0), monto(0.0), fechaPago() {}

Contratacion::Contratacion(int aIdContratacion, int aIdCliente, int aIdCarrera, double aMonto, const Fecha &aFecha,
                           bool aEstado)
    : estado(aEstado), idContratacion(aIdContratacion), idCliente(aIdCliente), idCarrera(aIdCarrera), monto(aMonto),
      fechaPago(aFecha) {}

bool Contratacion::getEstado() const { return estado; }

int Contratacion::getIdContratacion() const { return idContratacion; }

int Contratacion::getIdCliente() const { return idCliente; }

int Contratacion::getIdCarrera() const { return idCarrera; }

double Contratacion::getMonto() const { return monto; }

const Fecha &Contratacion::getFechaPago() const { return fechaPago; }

void Contratacion::setEstado(bool aEstado) { estado = aEstado; }

void Contratacion::setIdContratacion(int aIdContratacion) { idContratacion = aIdContratacion; }

void Contratacion::setIdCliente(int aIdCliente) { idCliente = aIdCliente; }

void Contratacion::setIdCarrera(int aIdCarrera) { idCarrera = aIdCarrera; }

void Contratacion::setMonto(double aMonto) { monto = aMonto; }

void Contratacion::setFechaPago(const Fecha &aFecha) { fechaPago = aFecha; }

void Contratacion::mostrar() const {
    cout << "--------------------------------" << endl;
    cout << "ID Contratacion: " << idContratacion << endl;
    cout << "ID Carrera: " << idCarrera << endl;
    cout << "ID Cliente: " << idCliente << endl;
    cout << "Monto abonado: $" << monto << endl;
    cout << "Fecha de pago: " << fechaPago.toString() << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
}

static const Carrera *buscarCarreraPorId(const vector<Carrera> &carreras, int idCarrera) {
    auto it = find_if(carreras.begin(), carreras.end(),
                           [idCarrera](const Carrera &carrera) { return carrera.getIdCarrera() == idCarrera; });
    if (it == carreras.end()) {
        return nullptr;
    }
    return &(*it);
}

void menuContrataciones(vector<Contratacion> &contrataciones, const vector<Carrera> &carreras,
                        const vector<Clientes> &clientes) {
    int opcion = -1;
    do {
        cout << "======= MENU CONTRATACIONES =======" << endl;
        cout << "1) Registrar pago" << endl;
        cout << "2) Listar contrataciones" << endl;
        cout << "3) Recaudacion total" << endl;
        cout << "4) Recaudacion por cliente" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                if (carreras.empty()) {
                    cout << "No hay carreras registradas para asociar un pago." << endl;
                    break;
                }

                Contratacion nueva;
                nueva.setIdContratacion(static_cast<int>(contrataciones.size()) + 1);

                cout << "Ingrese ID de la carrera abonada: ";
                int idCarrera;
                cin >> idCarrera;

                const Carrera *carrera = buscarCarreraPorId(carreras, idCarrera);
                if (carrera == nullptr) {
                    cout << "No existe una carrera con ese ID." << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                nueva.setIdCarrera(idCarrera);
                nueva.setIdCliente(carrera->getIdClientePago());

                cout << "Ingrese monto abonado: $";
                double monto;
                cin >> monto;
                nueva.setMonto(monto);

                Fecha fechaPago;
                fechaPago.cargar();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                nueva.setFechaPago(fechaPago);
                nueva.setEstado(true);

                contrataciones.push_back(nueva);
                cout << "Contratacion registrada correctamente." << endl;
                break;
            }
            case 2: {
                if (contrataciones.empty()) {
                    cout << "No hay contrataciones registradas." << endl;
                    break;
                }

                for (const Contratacion &contratacion : contrataciones) {
                    contratacion.mostrar();
                    const Clientes *cliente = buscarClientePorId(clientes, contratacion.getIdCliente());
                    if (cliente != nullptr) {
                        cout << "Cliente: " << cliente->getNombre() << " " << cliente->getApellido() << endl;
                    }
                }
                break;
            }
            case 3: {
                cout << "Recaudacion total: $" << calcularRecaudacionTotal(contrataciones) << endl;
                break;
            }
            case 4: {
                cout << "Ingrese ID de cliente: ";
                int idCliente;
                cin >> idCliente;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Recaudacion del cliente " << idCliente << ": $"
                          << calcularRecaudacionPorCliente(contrataciones, idCliente) << endl;
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

double calcularRecaudacionTotal(const vector<Contratacion> &contrataciones) {
    double total = 0.0;
    for (const Contratacion &contratacion : contrataciones) {
        total += contratacion.getMonto();
    }
    return total;
}

double calcularRecaudacionPorCliente(const vector<Contratacion> &contrataciones, int idCliente) {
    double total = 0.0;
    for (const Contratacion &contratacion : contrataciones) {
        if (contratacion.getIdCliente() == idCliente) {
            total += contratacion.getMonto();
        }
    }
    return total;
}

static void escribirFecha(ofstream &out, const Fecha &fecha) {
    int dia = fecha.getDia();
    int mes = fecha.getMes();
    int anio = fecha.getAnio();
    out.write(reinterpret_cast<const char *>(&dia), sizeof(dia));
    out.write(reinterpret_cast<const char *>(&mes), sizeof(mes));
    out.write(reinterpret_cast<const char *>(&anio), sizeof(anio));
}

static bool leerFecha(ifstream &in, Fecha &fecha) {
    int dia = 0;
    int mes = 0;
    int anio = 0;
    in.read(reinterpret_cast<char *>(&dia), sizeof(dia));
    in.read(reinterpret_cast<char *>(&mes), sizeof(mes));
    in.read(reinterpret_cast<char *>(&anio), sizeof(anio));
    if (!in) {
        return false;
    }
    fecha.setDia(dia);
    fecha.setMes(mes);
    fecha.setAnio(anio);
    return true;
}

bool guardarContrataciones(const vector<Contratacion> &contrataciones, const string &rutaArchivo) {
    ofstream out(rutaArchivo, ios::binary | ios::trunc);
    if (!out) {
        return false;
    }

    size_t cantidad = contrataciones.size();
    out.write(reinterpret_cast<const char *>(&cantidad), sizeof(cantidad));

    for (const Contratacion &contratacion : contrataciones) {
        int idContratacion = contratacion.getIdContratacion();
        int idCliente = contratacion.getIdCliente();
        int idCarrera = contratacion.getIdCarrera();
        double monto = contratacion.getMonto();
        char estado = contratacion.getEstado() ? 1 : 0;

        out.write(reinterpret_cast<const char *>(&idContratacion), sizeof(idContratacion));
        out.write(reinterpret_cast<const char *>(&idCliente), sizeof(idCliente));
        out.write(reinterpret_cast<const char *>(&idCarrera), sizeof(idCarrera));
        out.write(reinterpret_cast<const char *>(&monto), sizeof(monto));
        out.write(reinterpret_cast<const char *>(&estado), sizeof(estado));
        escribirFecha(out, contratacion.getFechaPago());
    }

    return out.good();
}

bool cargarContrataciones(vector<Contratacion> &contrataciones, const string &rutaArchivo) {
    contrataciones.clear();

    ifstream in(rutaArchivo, ios::binary);
    if (!in) {
        return true;
    }

    size_t cantidad = 0;
    in.read(reinterpret_cast<char *>(&cantidad), sizeof(cantidad));
    if (!in) {
        return false;
    }

    vector<Contratacion> cargadas;
    cargadas.reserve(cantidad);

    for (size_t i = 0; i < cantidad; ++i) {
        int idContratacion = 0;
        int idCliente = 0;
        int idCarrera = 0;
        double monto = 0.0;
        char estado = 0;
        Fecha fechaPago;

        in.read(reinterpret_cast<char *>(&idContratacion), sizeof(idContratacion));
        in.read(reinterpret_cast<char *>(&idCliente), sizeof(idCliente));
        in.read(reinterpret_cast<char *>(&idCarrera), sizeof(idCarrera));
        in.read(reinterpret_cast<char *>(&monto), sizeof(monto));
        in.read(reinterpret_cast<char *>(&estado), sizeof(estado));
        if (!in || !leerFecha(in, fechaPago)) {
            return false;
        }

        Contratacion registro;
        registro.setIdContratacion(idContratacion);
        registro.setIdCliente(idCliente);
        registro.setIdCarrera(idCarrera);
        registro.setMonto(monto);
        registro.setEstado(estado != 0);
        registro.setFechaPago(fechaPago);

        cargadas.push_back(registro);
    }

    contrataciones = move(cargadas);
    return true;
}
