#include "carrera.h"

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <utility>

using namespace std;

Carrera::Carrera()
    : estado(false), idCarrera(0), idCategoria(0), cantParticipantes(0), idClientePago(0), horaInicio(0.0), fecha(),
      participantes() {}

bool Carrera::getEstado() const { return estado; }

int Carrera::getIdCarrera() const { return idCarrera; }

int Carrera::getIdCategoria() const { return idCategoria; }

int Carrera::getCantParticipantes() const { return cantParticipantes; }

int Carrera::getIdClientePago() const { return idClientePago; }

double Carrera::getHoraInicio() const { return horaInicio; }

const Fecha &Carrera::getFecha() const { return fecha; }

const vector<Participantes> &Carrera::getParticipantes() const { return participantes; }

void Carrera::setEstado(bool aEstado) { estado = aEstado; }

void Carrera::setIdCarrera(int aIdCarrera) { idCarrera = aIdCarrera; }

void Carrera::setIdCategoria(int aIdCategoria) { idCategoria = aIdCategoria; }

void Carrera::setCantParticipantes(int aCantParticipantes) { cantParticipantes = aCantParticipantes; }

void Carrera::setIdClientePago(int aIdClientePago) { idClientePago = aIdClientePago; }

void Carrera::setHoraInicio(double aHoraInicio) { horaInicio = aHoraInicio; }

void Carrera::setFecha(const Fecha &aFecha) { fecha = aFecha; }

void Carrera::setParticipantes(const vector<Participantes> &aParticipantes) { participantes = aParticipantes; }

void Carrera::agregarParticipante(const Participantes &participante) { participantes.push_back(participante); }

double Carrera::promedioParticipante(size_t indiceParticipante, int cantidadVueltas) const {
    if (indiceParticipante >= participantes.size()) {
        return 0.0;
    }
    return participantes[indiceParticipante].calcularPromedio(cantidadVueltas);
}

void Carrera::mostrarResumen(const Categorias &categoria, const Clientes *clientePago) const {
    cout << "--------------------------------" << endl;
    cout << "Carrera #" << idCarrera << " - Categoria: " << categoria.getNombreCat() << endl;
    cout << "Fecha: " << fecha.toString() << endl;
    cout << "Hora de inicio: " << fixed << setprecision(2) << horaInicio << " hs" << endl;
    if (clientePago != nullptr) {
        cout << "Responsable de pago: " << clientePago->getNombre() << " " << clientePago->getApellido()
                  << " (ID " << clientePago->getIdCliente() << ")" << endl;
    }
    cout << "Participantes registrados: " << participantes.size() << endl;
    for (size_t i = 0; i < participantes.size(); ++i) {
        const Participantes &participante = participantes[i];
        cout << "  Participante " << (i + 1) << " - ID Cliente: " << participante.getIdCliente() << endl;
        cout << "    Tiempo total: " << participante.getTiempoTotal() << " segundos" << endl;
        cout << "    Promedio por vuelta: "
                  << participante.calcularPromedio(categoria.getCantVueltas()) << " segundos" << endl;
    }
}

static const Carrera *buscarCarreraPorId(const vector<Carrera> &carreras, int idCarrera) {
    auto it = find_if(carreras.begin(), carreras.end(),
                           [idCarrera](const Carrera &carrera) { return carrera.getIdCarrera() == idCarrera; });
    if (it == carreras.end()) {
        return nullptr;
    }
    return &(*it);
}

bool registrarCarrera(vector<Carrera> &carreras, const vector<Categorias> &categorias,
                      const vector<Clientes> &clientes) {
    if (categorias.empty()) {
        cout << "No hay categorias configuradas." << endl;
        return false;
    }

    Carrera nueva;
    nueva.setIdCarrera(static_cast<int>(carreras.size()) + 1);

    mostrarListadoCategorias(categorias);
    cout << "Ingrese el ID de la categoria: ";
    int idCategoria;
    cin >> idCategoria;
    const Categorias *categoria = buscarCategoriaPorId(categorias, idCategoria);
    if (categoria == nullptr) {
        cout << "Categoria inexistente." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    nueva.setIdCategoria(categoria->getIdCategoria());

    cout << "Ingrese la hora de inicio (formato HH.MM): ";
    double horaInicio;
    cin >> horaInicio;
    nueva.setHoraInicio(horaInicio);

    Fecha fecha;
    fecha.cargar();
    nueva.setFecha(fecha);

    cout << "Ingrese la cantidad de participantes: ";
    int cantidad;
    cin >> cantidad;
    if (cantidad <= 0) {
        cout << "La carrera debe tener al menos un participante." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    nueva.setCantParticipantes(cantidad);

    cout << "Ingrese el ID del cliente responsable del pago: ";
    int idClientePago;
    cin >> idClientePago;
    nueva.setIdClientePago(idClientePago);

    for (int i = 0; i < cantidad; ++i) {
        Participantes participante;
        participante.cargar(i + 1);
        nueva.agregarParticipante(participante);
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    nueva.setEstado(true);
    carreras.push_back(nueva);
    cout << "Carrera registrada correctamente." << endl;
    return true;
}

void menuCarreras(vector<Carrera> &carreras, const vector<Categorias> &categorias,
                  const vector<Clientes> &clientes) {
    int opcion = -1;
    do {
        cout << "======= MENU CARRERAS =======" << endl;
        cout << "1) Listar carreras" << endl;
        cout << "2) Buscar carrera por numero" << endl;
        cout << "3) Listar carreras por participante" << endl;
        cout << "4) Registrar nueva carrera" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                if (carreras.empty()) {
                    cout << "No hay carreras registradas." << endl;
                    break;
                }
                for (const Carrera &carrera : carreras) {
                    const Categorias *categoria = buscarCategoriaPorId(categorias, carrera.getIdCategoria());
                    const Clientes *cliente = buscarClientePorId(clientes, carrera.getIdClientePago());
                    if (categoria != nullptr) {
                        carrera.mostrarResumen(*categoria, cliente);
                    }
                }
                break;
            }
            case 2: {
                cout << "Ingrese ID de carrera: ";
                int idCarrera;
                cin >> idCarrera;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                const Carrera *carrera = buscarCarreraPorId(carreras, idCarrera);
                if (carrera == nullptr) {
                    cout << "No se encontro la carrera." << endl;
                } else {
                    const Categorias *categoria = buscarCategoriaPorId(categorias, carrera->getIdCategoria());
                    const Clientes *cliente = buscarClientePorId(clientes, carrera->getIdClientePago());
                    if (categoria != nullptr) {
                        carrera->mostrarResumen(*categoria, cliente);
                    }
                }
                break;
            }
            case 3: {
                cout << "Ingrese ID de participante: ";
                int idCliente;
                cin >> idCliente;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                bool encontrado = false;
                for (const Carrera &carrera : carreras) {
                    const Categorias *categoria = buscarCategoriaPorId(categorias, carrera.getIdCategoria());
                    if (categoria == nullptr) {
                        continue;
                    }
                    for (const Participantes &participante : carrera.getParticipantes()) {
                        if (participante.getIdCliente() == idCliente) {
                            const Clientes *cliente = buscarClientePorId(clientes, carrera.getIdClientePago());
                            carrera.mostrarResumen(*categoria, cliente);
                            encontrado = true;
                            break;
                        }
                    }
                }
                if (!encontrado) {
                    cout << "El participante no registra carreras." << endl;
                }
                break;
            }
            case 4: {
                registrarCarrera(carreras, categorias, clientes);
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

void mostrarPodioRecords(const vector<Carrera> &carreras, const vector<Categorias> &categorias,
                         const vector<Clientes> &clientes) {
    if (carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        return;
    }

    struct Record {
        double promedio;
        int idCliente;
        int idCarrera;
    };

    map<int, Record> mejoresPorCategoria;

    for (const Carrera &carrera : carreras) {
        const Categorias *categoria = buscarCategoriaPorId(categorias, carrera.getIdCategoria());
        if (categoria == nullptr) {
            continue;
        }

        int vueltas = categoria->getCantVueltas();
        for (size_t i = 0; i < carrera.getParticipantes().size(); ++i) {
            const Participantes &participante = carrera.getParticipantes()[i];
            double promedio = participante.calcularPromedio(vueltas);
            if (promedio <= 0.0) {
                continue;
            }

            auto it = mejoresPorCategoria.find(categoria->getIdCategoria());
            if (it == mejoresPorCategoria.end() || promedio < it->second.promedio) {
                mejoresPorCategoria[categoria->getIdCategoria()] = {promedio, participante.getIdCliente(),
                                                                      carrera.getIdCarrera()};
            }
        }
    }

    if (mejoresPorCategoria.empty()) {
        cout << "No hay registros suficientes para generar el podio." << endl;
        return;
    }

    cout << "======= PODIO DE RECORDS =======" << endl;
    for (const auto &par : mejoresPorCategoria) {
        const Categorias *categoria = buscarCategoriaPorId(categorias, par.first);
        if (categoria == nullptr) {
            continue;
        }
        const Record &record = par.second;
        const Clientes *cliente = buscarClientePorId(clientes, record.idCliente);
        cout << categoria->getNombreCat() << " - Carrera #" << record.idCarrera << endl;
        if (cliente != nullptr) {
            cout << "  Piloto: " << cliente->getNombre() << " " << cliente->getApellido() << " (ID "
                      << cliente->getIdCliente() << ")" << endl;
        } else {
            cout << "  ID Piloto: " << record.idCliente << endl;
        }
        cout << "  Promedio por vuelta: " << record.promedio << " segundos" << endl;
    }
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

bool guardarCarreras(const vector<Carrera> &carreras, const string &rutaArchivo) {
    ofstream out(rutaArchivo, ios::binary | ios::trunc);
    if (!out) {
        return false;
    }

    size_t cantidad = carreras.size();
    out.write(reinterpret_cast<const char *>(&cantidad), sizeof(cantidad));

    for (const Carrera &carrera : carreras) {
        int idCarrera = carrera.getIdCarrera();
        int idCategoria = carrera.getIdCategoria();
        int cantParticipantes = carrera.getCantParticipantes();
        int idClientePago = carrera.getIdClientePago();
        double horaInicio = carrera.getHoraInicio();
        char estado = carrera.getEstado() ? 1 : 0;

        out.write(reinterpret_cast<const char *>(&idCarrera), sizeof(idCarrera));
        out.write(reinterpret_cast<const char *>(&idCategoria), sizeof(idCategoria));
        out.write(reinterpret_cast<const char *>(&cantParticipantes), sizeof(cantParticipantes));
        out.write(reinterpret_cast<const char *>(&idClientePago), sizeof(idClientePago));
        out.write(reinterpret_cast<const char *>(&horaInicio), sizeof(horaInicio));
        out.write(reinterpret_cast<const char *>(&estado), sizeof(estado));
        escribirFecha(out, carrera.getFecha());

        const vector<Participantes> &participantes = carrera.getParticipantes();
        size_t cantidadParticipantes = participantes.size();
        out.write(reinterpret_cast<const char *>(&cantidadParticipantes), sizeof(cantidadParticipantes));
        for (const Participantes &participante : participantes) {
            int idCliente = participante.getIdCliente();
            double horaFinal = participante.getHoraFinal();
            double tiempoTotal = participante.getTiempoTotal();
            char estadoParticipante = participante.getEstado() ? 1 : 0;

            out.write(reinterpret_cast<const char *>(&idCliente), sizeof(idCliente));
            out.write(reinterpret_cast<const char *>(&horaFinal), sizeof(horaFinal));
            out.write(reinterpret_cast<const char *>(&tiempoTotal), sizeof(tiempoTotal));
            out.write(reinterpret_cast<const char *>(&estadoParticipante), sizeof(estadoParticipante));
        }
    }

    return out.good();
}

bool cargarCarreras(vector<Carrera> &carreras, const string &rutaArchivo) {
    carreras.clear();

    ifstream in(rutaArchivo, ios::binary);
    if (!in) {
        return true;
    }

    size_t cantidad = 0;
    in.read(reinterpret_cast<char *>(&cantidad), sizeof(cantidad));
    if (!in) {
        return false;
    }

    vector<Carrera> cargadas;
    cargadas.reserve(cantidad);

    for (size_t i = 0; i < cantidad; ++i) {
        int idCarrera = 0;
        int idCategoria = 0;
        int cantParticipantes = 0;
        int idClientePago = 0;
        double horaInicio = 0.0;
        char estado = 0;
        Fecha fecha;

        in.read(reinterpret_cast<char *>(&idCarrera), sizeof(idCarrera));
        in.read(reinterpret_cast<char *>(&idCategoria), sizeof(idCategoria));
        in.read(reinterpret_cast<char *>(&cantParticipantes), sizeof(cantParticipantes));
        in.read(reinterpret_cast<char *>(&idClientePago), sizeof(idClientePago));
        in.read(reinterpret_cast<char *>(&horaInicio), sizeof(horaInicio));
        in.read(reinterpret_cast<char *>(&estado), sizeof(estado));
        if (!in || !leerFecha(in, fecha)) {
            return false;
        }

        size_t cantidadParticipantes = 0;
        in.read(reinterpret_cast<char *>(&cantidadParticipantes), sizeof(cantidadParticipantes));
        if (!in) {
            return false;
        }

        vector<Participantes> participantes;
        participantes.reserve(cantidadParticipantes);
        for (size_t j = 0; j < cantidadParticipantes; ++j) {
            int idCliente = 0;
            double horaFinal = 0.0;
            double tiempoTotal = 0.0;
            char estadoParticipante = 0;

            in.read(reinterpret_cast<char *>(&idCliente), sizeof(idCliente));
            in.read(reinterpret_cast<char *>(&horaFinal), sizeof(horaFinal));
            in.read(reinterpret_cast<char *>(&tiempoTotal), sizeof(tiempoTotal));
            in.read(reinterpret_cast<char *>(&estadoParticipante), sizeof(estadoParticipante));
            if (!in) {
                return false;
            }

            Participantes participante;
            participante.setIdCliente(idCliente);
            participante.setHoraFinal(horaFinal);
            participante.setTiempoTotal(tiempoTotal);
            participante.setEstado(estadoParticipante != 0);
            participantes.push_back(participante);
        }

        Carrera carrera;
        carrera.setIdCarrera(idCarrera);
        carrera.setIdCategoria(idCategoria);
        carrera.setCantParticipantes(cantParticipantes);
        carrera.setIdClientePago(idClientePago);
        carrera.setHoraInicio(horaInicio);
        carrera.setEstado(estado != 0);
        carrera.setFecha(fecha);
        carrera.setParticipantes(participantes);

        if (carrera.getCantParticipantes() != static_cast<int>(carrera.getParticipantes().size())) {
            carrera.setCantParticipantes(static_cast<int>(carrera.getParticipantes().size()));
        }

        cargadas.push_back(move(carrera));
    }

    carreras = move(cargadas);
    return true;
}
