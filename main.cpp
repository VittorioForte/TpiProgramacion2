#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <numeric>
#include <limits>
#include <iomanip>

using namespace std;

#include "categorias.h"
#include "clientes.h"
#include "contratacion.h"
#include "participantes.h"
#include "carrera.h"

// Declaraciones de menus globales
void menuCarreras();
void menuClientes();

// Utilidades compartidas
struct RankingEntry {
    int idCliente;
    double promedio;
};

Categorias crearCategoriaPorId(int idCategoria);
const char *nombreCategoria(int idCategoria);
int vueltasPorCategoria(int idCategoria);
int obtenerProximoIdCarrera();
int obtenerProximoIdContratacion();
bool cargarClientesActivos(vector<Clientes> &clientes);
bool cargarCarrerasActivas(vector<Carrera> &carreras);
bool cargarContratacionesActivas(vector<Contratacion> &contratos);
bool cargarParticipantesPorCarrera(const vector<Carrera> &carreras,
                                   vector<vector<Participantes>> &participantesPorCarrera);
map<int, Clientes> mapaClientesPorId();
bool buscarCarreraPorId(int idCarrera, Carrera &resultado);
bool fechaEnRango(const Fecha &valor, const Fecha &desde, const Fecha &hasta);
int claveMes(const Fecha &fecha);
void registrarNuevaCarrera();
void listarCarrerasGenerales();
void consultarCarrerasPorFecha();
void historialPorCliente();
void mostrarCantidadCarrerasPorCategoria();
void mostrarCategoriaMasUtilizada();
void menuCategorias();
void menuContrataciones();
void registrarContratacion();
void listarContrataciones();
void recaudacionGeneral();
void recaudacionPorCategoria();
void recaudacionMensual();
void menuInformes();
void rankingPorCategoria();
void podioGeneral();
void clientesFrecuentes();
void informeGeneralClientes();

int main() {
    int opcion = -1;

    do {
        system("cls");
        cout << "========= KARTODROMO =========\n";
        cout << "1) Gestion de clientes\n";
        cout << "2) Gestion de categorias\n";
        cout << "3) Registro y control de carreras\n";
        cout << "4) Control de pagos y recaudacion\n";
        cout << "5) Informes y rankings\n";
        cout << "6) Registrar carrera rapida\n";
        cout << "7) Informe integral de clientes\n";
        cout << "0) Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida." << endl;
            system("pause");
            continue;
        }

        switch (opcion) {
            case 1:
                menuClientes();
                break;
            case 2:
                menuCategorias();
                break;
            case 3:
                menuCarreras();
                break;
            case 4:
                menuContrataciones();
                break;
            case 5:
                menuInformes();
                break;
            case 6:
                registrarNuevaCarrera();
                break;
            case 7:
                informeGeneralClientes();
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                system("pause");
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }

    } while (opcion != 0);

    return 0;
}

// ===================== UTILIDADES GENERALES =====================

Categorias crearCategoriaPorId(int idCategoria) {
    Categorias categoria;
    switch (idCategoria) {
        case 1:
            categoria.setNombreCat("PROFESIONAL");
            break;
        case 2:
            categoria.setNombreCat("AMATEUR");
            break;
        case 3:
            categoria.setNombreCat("INFANTIL");
            break;
        default:
            categoria.setNombreCat("DESCONOCIDA");
            categoria.setEstado(false);
            break;
    }
    return categoria;
}

const char *nombreCategoria(int idCategoria) {
    switch (idCategoria) {
        case 1:
            return "PROFESIONAL";
        case 2:
            return "AMATEUR";
        case 3:
            return "INFANTIL";
        default:
            return "DESCONOCIDA";
    }
}

int vueltasPorCategoria(int idCategoria) {
    switch (idCategoria) {
        case 1:
            return 20;
        case 2:
            return 15;
        case 3:
            return 10;
        default:
            return 0;
    }
}

int obtenerProximoIdCarrera() {
    Carrera registro;
    int pos = 0;
    int maxId = 0;
    while (registro.leerDeDisco(pos++)) {
        if (registro.getEstado() && registro.getIdCarrera() > maxId) {
            maxId = registro.getIdCarrera();
        }
    }
    return maxId + 1;
}

int obtenerProximoIdContratacion() {
    Contratacion registro;
    int pos = 0;
    int maxId = 0;
    while (registro.leerDeDisco(pos++)) {
        if (registro.getEstado() && registro.getIdContratacion() > maxId) {
            maxId = registro.getIdContratacion();
        }
    }
    return maxId + 1;
}

bool cargarClientesActivos(vector<Clientes> &clientes) {
    clientes.clear();
    Clientes registro;
    int pos = 0;
    bool pudo = false;
    while (registro.leerDeDisco(pos++)) {
        pudo = true;
        if (registro.getEstado()) {
            clientes.push_back(registro);
        }
    }
    return pudo;
}

bool cargarCarrerasActivas(vector<Carrera> &carreras) {
    carreras.clear();
    Carrera registro;
    int pos = 0;
    bool pudo = false;
    while (registro.leerDeDisco(pos++)) {
        pudo = true;
        if (registro.getEstado()) {
            carreras.push_back(registro);
        }
    }
    return pudo;
}

bool cargarContratacionesActivas(vector<Contratacion> &contratos) {
    contratos.clear();
    Contratacion registro;
    int pos = 0;
    bool pudo = false;
    while (registro.leerDeDisco(pos++)) {
        pudo = true;
        if (registro.getEstado()) {
            contratos.push_back(registro);
        }
    }
    return pudo;
}

bool cargarParticipantesPorCarrera(const vector<Carrera> &carreras,
                                   vector<vector<Participantes>> &participantesPorCarrera) {
    participantesPorCarrera.clear();
    vector<Participantes> todos;
    Participantes registro;
    int pos = 0;
    while (registro.leerDeDisco(pos++)) {
        todos.push_back(registro);
    }

    size_t indice = 0;
    for (const auto &carrera : carreras) {
        vector<Participantes> grupo;
        for (int i = 0; i < carrera.getCantParticipantes() && indice < todos.size(); ++i) {
            grupo.push_back(todos[indice++]);
        }
        participantesPorCarrera.push_back(grupo);
    }

    return true;
}

map<int, Clientes> mapaClientesPorId() {
    vector<Clientes> clientes;
    cargarClientesActivos(clientes);
    map<int, Clientes> mapa;
    for (const auto &cli : clientes) {
        mapa[cli.getIdCliente()] = cli;
    }
    return mapa;
}

bool buscarCarreraPorId(int idCarrera, Carrera &resultado) {
    Carrera registro;
    int pos = 0;
    while (registro.leerDeDisco(pos++)) {
        if (registro.getEstado() && registro.getIdCarrera() == idCarrera) {
            resultado = registro;
            return true;
        }
    }
    return false;
}

bool fechaEnRango(const Fecha &valor, const Fecha &desde, const Fecha &hasta) {
    int claveValor = valor.getAnio() * 10000 + valor.getMes() * 100 + valor.getDia();
    int claveDesde = desde.getAnio() * 10000 + desde.getMes() * 100 + desde.getDia();
    int claveHasta = hasta.getAnio() * 10000 + hasta.getMes() * 100 + hasta.getDia();
    if (claveDesde > claveHasta) {
        swap(claveDesde, claveHasta);
    }
    return claveValor >= claveDesde && claveValor <= claveHasta;
}

int claveMes(const Fecha &fecha) {
    return fecha.getAnio() * 100 + fecha.getMes();
}

// ===================== MENU CATEGORIAS =====================

void listarCategoriasDisponibles() {
    system("cls");
    cout << "====== CATEGORIAS DISPONIBLES ======" << endl;
    for (int id = 1; id <= 3; ++id) {
        Categorias cat = crearCategoriaPorId(id);
        cat.mostrar();
    }
    system("pause");
}

void mostrarCantidadCarrerasPorCategoria() {
    system("cls");
    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    map<int, int> conteo;
    for (const auto &carrera : carreras) {
        conteo[carrera.getIdCategoria()]++;
    }

    cout << "Cantidad de carreras por categoria:" << endl;
    for (int id = 1; id <= 3; ++id) {
        cout << nombreCategoria(id) << ": " << conteo[id] << endl;
    }
    system("pause");
}

void mostrarCategoriaMasUtilizada() {
    system("cls");
    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    map<int, int> conteo;
    for (const auto &carrera : carreras) {
        conteo[carrera.getIdCategoria()]++;
    }

    int mejorCategoria = 0;
    int maxCantidad = -1;
    for (const auto &par : conteo) {
        if (par.second > maxCantidad) {
            maxCantidad = par.second;
            mejorCategoria = par.first;
        }
    }

    if (maxCantidad <= 0) {
        cout << "No hay carreras activas." << endl;
    } else {
        cout << "La categoria mas utilizada es: " << nombreCategoria(mejorCategoria)
             << " con " << maxCantidad << " carreras." << endl;
    }
    system("pause");
}

void menuCategorias() {
    int opcion = -1;
    do {
        system("cls");
        cout << "======= MENU CATEGORIAS =======" << endl;
        cout << "1) Listado de categorias" << endl;
        cout << "2) Cantidad de carreras por categoria" << endl;
        cout << "3) Categoria mas utilizada" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida." << endl;
            system("pause");
            continue;
        }

        switch (opcion) {
            case 1:
                listarCategoriasDisponibles();
                break;
            case 2:
                mostrarCantidadCarrerasPorCategoria();
                break;
            case 3:
                mostrarCategoriaMasUtilizada();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}

// ===================== MENU CARRERAS =====================

void registrarNuevaCarrera() {
    system("cls");
    cout << "======= REGISTRAR NUEVA CARRERA =======" << endl;

    Carrera nueva;
    nueva.setEstado(true);
    nueva.setIdCarrera(obtenerProximoIdCarrera());

    int idCategoria;
    do {
        cout << "Seleccione categoria (1 Profesional / 2 Amateur / 3 Infantil): ";
        cin >> idCategoria;
        if (cin.fail() || idCategoria < 1 || idCategoria > 3) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Categoria invalida." << endl;
            idCategoria = 0;
        }
    } while (idCategoria < 1 || idCategoria > 3);

    nueva.setIdCategoria(idCategoria);

    int cantidadParticipantes = 0;
    do {
        cout << "Cantidad de participantes: ";
        cin >> cantidadParticipantes;
        if (cin.fail() || cantidadParticipantes <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Debe ingresar un valor positivo." << endl;
            cantidadParticipantes = 0;
        }
    } while (cantidadParticipantes <= 0);
    nueva.setCantParticipantes(cantidadParticipantes);

    double horaInicio = 0.0;
    cout << "Hora de inicio (en formato decimal, por ejemplo 15.30): ";
    cin >> horaInicio;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        horaInicio = 0.0;
    }
    nueva.setHoraInicio(horaInicio);

    cout << "Ingrese la fecha de la carrera:" << endl;
    Fecha fecha;
    fecha.cargar();
    nueva.setFecha(fecha);

    if (!nueva.grabarEnDisco()) {
        cout << "No se pudo guardar la carrera." << endl;
        system("pause");
        return;
    }

    cout << "Carga de participantes:" << endl;
    int vueltas = vueltasPorCategoria(idCategoria);
    bool errorParticipantes = false;
    for (int i = 0; i < cantidadParticipantes; ++i) {
        cout << "Participante " << (i + 1) << endl;
        Participantes participante;
        participante.cargar(vueltas);
        if (!participante.grabarEnDisco()) {
            errorParticipantes = true;
            cout << "No se pudo guardar el participante." << endl;
            break;
        }
    }

    if (!errorParticipantes) {
        cout << "Carrera registrada correctamente." << endl;
    }
    system("pause");
}

void listarCarrerasGenerales() {
    system("cls");
    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    vector<vector<Participantes>> participantesPorCarrera;
    cargarParticipantesPorCarrera(carreras, participantesPorCarrera);
    map<int, Clientes> clientes = mapaClientesPorId();

    streamsize precisionAnterior = cout.precision();
    ios::fmtflags formatoAnterior = cout.flags();
    cout << fixed << setprecision(2);
    for (size_t i = 0; i < carreras.size(); ++i) {
        const Carrera &carrera = carreras[i];
        cout << "======================================" << endl;
        cout << "Carrera ID: " << carrera.getIdCarrera() << endl;
        cout << "Categoria: " << nombreCategoria(carrera.getIdCategoria()) << endl;
        cout << "Participantes: " << carrera.getCantParticipantes() << endl;
        cout << "Hora inicio: " << carrera.getHoraInicio() << endl;
        cout << "Fecha: ";
        carrera.getFecha().mostrar();

        cout << left << setw(15) << "ID Cliente" << setw(25) << "Nombre"
             << setw(15) << "Hora Final" << setw(20) << "Promedio x vuelta" << endl;

        const vector<Participantes> vacio;
        const vector<Participantes> &lista = (i < participantesPorCarrera.size()) ? participantesPorCarrera[i] : vacio;
        for (const auto &participante : lista) {
            if (!participante.getEstado()) {
                continue;
            }
            string nombreCompleto = "Desconocido";
            auto it = clientes.find(participante.getIdCliente());
            if (it != clientes.end()) {
                nombreCompleto = string(it->second.getNombre()) + " " + it->second.getApellido();
            }
            double promedio = participante.calcularPromedio(vueltasPorCategoria(carrera.getIdCategoria()),
                                                             carrera.getHoraInicio());
            cout << left << setw(15) << participante.getIdCliente()
                 << setw(25) << nombreCompleto
                 << setw(15) << participante.getHoraFinal()
                 << setw(20) << promedio << endl;
        }
    }
    cout.flags(formatoAnterior);
    cout.precision(precisionAnterior);

    system("pause");
}

void consultarCarrerasPorFecha() {
    system("cls");
    cout << "======= BUSCAR CARRERAS POR FECHA =======" << endl;
    cout << "Ingrese fecha DESDE" << endl;
    Fecha desde;
    desde.cargar();
    cout << "Ingrese fecha HASTA" << endl;
    Fecha hasta;
    hasta.cargar();

    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    bool encontrado = false;
    for (const auto &carrera : carreras) {
        if (fechaEnRango(carrera.getFecha(), desde, hasta)) {
            encontrado = true;
            cout << "Carrera ID: " << carrera.getIdCarrera() << " - Categoria: "
                 << nombreCategoria(carrera.getIdCategoria()) << " - Fecha: ";
            carrera.getFecha().mostrar();
        }
    }

    if (!encontrado) {
        cout << "No se encontraron carreras en el rango indicado." << endl;
    }
    system("pause");
}

void historialPorCliente() {
    system("cls");
    cout << "======= HISTORIAL DE CLIENTE =======" << endl;
    cout << "Ingrese DNI del cliente: ";
    string dniBuscado;
    cin >> dniBuscado;

    vector<Clientes> clientes;
    if (!cargarClientesActivos(clientes) || clientes.empty()) {
        cout << "No hay clientes cargados." << endl;
        system("pause");
        return;
    }

    Clientes clienteEncontrado;
    bool hallado = false;
    for (const auto &cli : clientes) {
        if (dniBuscado == cli.getDni()) {
            clienteEncontrado = cli;
            hallado = true;
            break;
        }
    }

    if (!hallado) {
        cout << "No se encontro un cliente con ese DNI." << endl;
        system("pause");
        return;
    }

    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    vector<vector<Participantes>> participantesPorCarrera;
    cargarParticipantesPorCarrera(carreras, participantesPorCarrera);

    cout << "Historial para " << clienteEncontrado.getNombre() << ' ' << clienteEncontrado.getApellido() << endl;
    bool tieneHistorial = false;
    const vector<Participantes> vacio;
    for (size_t i = 0; i < carreras.size(); ++i) {
        const Carrera &carrera = carreras[i];
        const vector<Participantes> &lista = (i < participantesPorCarrera.size()) ? participantesPorCarrera[i] : vacio;
        for (const auto &participante : lista) {
            if (participante.getEstado() && participante.getIdCliente() == clienteEncontrado.getIdCliente()) {
                tieneHistorial = true;
                cout << "Carrera ID: " << carrera.getIdCarrera() << endl;
                cout << "Categoria: " << nombreCategoria(carrera.getIdCategoria()) << endl;
                cout << "Fecha: ";
                carrera.getFecha().mostrar();
                double promedio = participante.calcularPromedio(vueltasPorCategoria(carrera.getIdCategoria()),
                                                                 carrera.getHoraInicio());
                cout << "Promedio por vuelta: " << promedio << endl;
                cout << "-----------------------------" << endl;
            }
        }
    }

    if (!tieneHistorial) {
        cout << "El cliente no registra participaciones." << endl;
    }

    vector<Contratacion> contrataciones;
    if (cargarContratacionesActivas(contrataciones)) {
        double totalPagado = 0.0;
        for (const auto &contrato : contrataciones) {
            if (contrato.getIdCliente() == clienteEncontrado.getIdCliente()) {
                totalPagado += contrato.getMonto();
            }
        }
        cout << "Total abonado por el cliente: $" << totalPagado << endl;
    }

    system("pause");
}

void informeGeneralClientes() {
    system("cls");
    cout << "======= INFORME INTEGRAL DE CLIENTES =======" << endl;

    vector<Clientes> clientes;
    if (!cargarClientesActivos(clientes) || clientes.empty()) {
        cout << "No hay clientes cargados." << endl;
        system("pause");
        return;
    }

    vector<Carrera> carreras;
    cargarCarrerasActivas(carreras);

    vector<vector<Participantes>> participantesPorCarrera;
    if (!carreras.empty()) {
        cargarParticipantesPorCarrera(carreras, participantesPorCarrera);
    }

    vector<Contratacion> contratos;
    cargarContratacionesActivas(contratos);

    streamsize precisionAnterior = cout.precision();
    ios::fmtflags formatoAnterior = cout.flags();
    cout << fixed << setprecision(2);
    const vector<Participantes> vacioParticipantes;

    for (const auto &cliente : clientes) {
        cout << "======================================" << endl;
        cout << "Cliente ID: " << cliente.getIdCliente() << " - " << cliente.getNombre() << ' '
             << cliente.getApellido() << endl;
        cout << "Telefono: " << cliente.getTelefono() << " | DNI: " << cliente.getDni() << endl;

        bool participacionesMostradas = false;
        for (size_t i = 0; i < carreras.size(); ++i) {
            const Carrera &carrera = carreras[i];
            const vector<Participantes> &lista = (i < participantesPorCarrera.size()) ? participantesPorCarrera[i] : vacioParticipantes;
            for (const auto &participante : lista) {
                if (!participante.getEstado() || participante.getIdCliente() != cliente.getIdCliente()) {
                    continue;
                }

                if (!participacionesMostradas) {
                    cout << "Participaciones:" << endl;
                    participacionesMostradas = true;
                }

                cout << "  Carrera " << carrera.getIdCarrera() << " - " << nombreCategoria(carrera.getIdCategoria()) << endl;
                cout << "    Fecha: ";
                carrera.getFecha().mostrar();
                double promedio = participante.calcularPromedio(vueltasPorCategoria(carrera.getIdCategoria()), carrera.getHoraInicio());
                cout << "    Hora final: " << participante.getHoraFinal()
                     << " | Promedio por vuelta: " << promedio << endl;
                cout << "    Cantidad de participantes: " << carrera.getCantParticipantes() << endl;
            }
        }

        if (!participacionesMostradas) {
            cout << "Participaciones: No registra carreras." << endl;
        }

        bool pagosMostrados = false;
        double totalPagado = 0.0;
        for (const auto &contrato : contratos) {
            if (contrato.getIdCliente() != cliente.getIdCliente()) {
                continue;
            }

            if (!pagosMostrados) {
                cout << "Pagos registrados:" << endl;
                pagosMostrados = true;
            }

            cout << "  Contratacion " << contrato.getIdContratacion()
                 << " - Carrera " << contrato.getIdCarrera()
                 << " - Monto $" << contrato.getMonto() << endl;
            cout << "    Fecha de pago: ";
            contrato.getFechaPago().mostrar();
            totalPagado += contrato.getMonto();
        }

        if (pagosMostrados) {
            cout << "  Total abonado: $" << totalPagado << endl;
        } else {
            cout << "Pagos registrados: No se registran pagos." << endl;
        }
    }

    if (!clientes.empty()) {
        cout << "======================================" << endl;
    }

    cout.flags(formatoAnterior);
    cout.precision(precisionAnterior);

    system("pause");
}

void menuCarreras() {
    int opcion = -1;
    do {
        system("cls");
        cout << "======= MENU CARRERAS =======" << endl;
        cout << "1) Registrar nueva carrera" << endl;
        cout << "2) Listado general de carreras" << endl;
        cout << "3) Consultar carreras por fecha" << endl;
        cout << "4) Historial de un cliente" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida." << endl;
            system("pause");
            continue;
        }

        switch (opcion) {
            case 1:
                registrarNuevaCarrera();
                break;
            case 2:
                listarCarrerasGenerales();
                break;
            case 3:
                consultarCarrerasPorFecha();
                break;
            case 4:
                historialPorCliente();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}

// ===================== MENU CONTRATACIONES =====================

void registrarContratacion() {
    system("cls");
    cout << "======= REGISTRAR CONTRATACION =======" << endl;

    Contratacion nueva;
    nueva.setEstado(true);
    nueva.setIdContratacion(obtenerProximoIdContratacion());

    cout << "ID del cliente: ";
    int idCliente;
    cin >> idCliente;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        idCliente = 0;
    }
    nueva.setIdCliente(idCliente);

    cout << "ID de la carrera: ";
    int idCarrera;
    cin >> idCarrera;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        idCarrera = 0;
    }
    nueva.setIdCarrera(idCarrera);

    cout << "Monto abonado: ";
    float monto;
    cin >> monto;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        monto = 0.0f;
    }
    nueva.setMonto(monto);

    cout << "Fecha de pago" << endl;
    Fecha fecha;
    fecha.cargar();
    nueva.setFechaPago(fecha);

    if (nueva.grabarEnDisco()) {
        cout << "Contratacion registrada." << endl;
    } else {
        cout << "No se pudo guardar la contratacion." << endl;
    }
    system("pause");
}

void listarContrataciones() {
    system("cls");
    vector<Contratacion> contrataciones;
    if (!cargarContratacionesActivas(contrataciones) || contrataciones.empty()) {
        cout << "No hay contrataciones registradas." << endl;
        system("pause");
        return;
    }

    map<int, Clientes> clientes = mapaClientesPorId();
    cout << fixed << setprecision(2);
    for (const auto &contrato : contrataciones) {
        cout << "Contratacion ID: " << contrato.getIdContratacion() << endl;
        auto it = clientes.find(contrato.getIdCliente());
        if (it != clientes.end()) {
            cout << "Cliente: " << it->second.getNombre() << ' ' << it->second.getApellido() << endl;
        } else {
            cout << "Cliente ID: " << contrato.getIdCliente() << endl;
        }
        cout << "Carrera ID: " << contrato.getIdCarrera() << endl;
        cout << "Monto abonado: $" << contrato.getMonto() << endl;
        cout << "Fecha de pago: ";
        contrato.getFechaPago().mostrar();
        cout << "-----------------------------" << endl;
    }
    system("pause");
}

void recaudacionGeneral() {
    system("cls");
    vector<Contratacion> contrataciones;
    if (!cargarContratacionesActivas(contrataciones) || contrataciones.empty()) {
        cout << "No hay contrataciones registradas." << endl;
        system("pause");
        return;
    }

    double total = 0.0;
    for (const auto &contrato : contrataciones) {
        total += contrato.getMonto();
    }

    cout << fixed << setprecision(2);
    cout << "Recaudacion total: $" << total << endl;
    system("pause");
}

void recaudacionPorCategoria() {
    system("cls");
    vector<Contratacion> contrataciones;
    vector<Carrera> carreras;
    if (!cargarContratacionesActivas(contrataciones) || contrataciones.empty()) {
        cout << "No hay contrataciones registradas." << endl;
        system("pause");
        return;
    }
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    map<int, double> recaudacion;
    for (const auto &contrato : contrataciones) {
        Carrera carrera;
        if (buscarCarreraPorId(contrato.getIdCarrera(), carrera)) {
            recaudacion[carrera.getIdCategoria()] += contrato.getMonto();
        }
    }

    cout << fixed << setprecision(2);
    for (int id = 1; id <= 3; ++id) {
        cout << nombreCategoria(id) << ": $" << recaudacion[id] << endl;
    }
    system("pause");
}

void recaudacionMensual() {
    system("cls");
    vector<Contratacion> contrataciones;
    if (!cargarContratacionesActivas(contrataciones) || contrataciones.empty()) {
        cout << "No hay contrataciones registradas." << endl;
        system("pause");
        return;
    }

    map<int, double> recaudacionPorMes;
    for (const auto &contrato : contrataciones) {
        recaudacionPorMes[claveMes(contrato.getFechaPago())] += contrato.getMonto();
    }

    cout << fixed << setprecision(2);
    for (const auto &par : recaudacionPorMes) {
        int mes = par.first % 100;
        int anio = par.first / 100;
        cout << "Mes " << setw(2) << setfill('0') << mes << '/' << anio << setfill(' ') << ": $" << par.second << endl;
    }
    system("pause");
}

void menuContrataciones() {
    int opcion = -1;
    do {
        system("cls");
        cout << "======= MENU PAGOS Y RECAUDACION =======" << endl;
        cout << "1) Registrar pago" << endl;
        cout << "2) Listar pagos" << endl;
        cout << "3) Recaudacion total" << endl;
        cout << "4) Recaudacion por categoria" << endl;
        cout << "5) Recaudacion mensual" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida." << endl;
            system("pause");
            continue;
        }

        switch (opcion) {
            case 1:
                registrarContratacion();
                break;
            case 2:
                listarContrataciones();
                break;
            case 3:
                recaudacionGeneral();
                break;
            case 4:
                recaudacionPorCategoria();
                break;
            case 5:
                recaudacionMensual();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}

// ===================== MENU INFORMES =====================

void rankingPorCategoria() {
    system("cls");
    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    vector<vector<Participantes>> participantesPorCarrera;
    cargarParticipantesPorCarrera(carreras, participantesPorCarrera);
    map<int, Clientes> clientes = mapaClientesPorId();

    map<int, vector<RankingEntry>> ranking;
    for (size_t i = 0; i < carreras.size(); ++i) {
        const Carrera &carrera = carreras[i];
        int vueltas = vueltasPorCategoria(carrera.getIdCategoria());
        const auto &lista = (i < participantesPorCarrera.size()) ? participantesPorCarrera[i] : vector<Participantes>();
        for (const auto &participante : lista) {
            if (!participante.getEstado()) {
                continue;
            }
            RankingEntry entry;
            entry.idCliente = participante.getIdCliente();
            entry.promedio = participante.calcularPromedio(vueltas, carrera.getHoraInicio());
            if (entry.promedio > 0.0) {
                ranking[carrera.getIdCategoria()].push_back(entry);
            }
        }
    }

    cout << fixed << setprecision(2);
    for (int id = 1; id <= 3; ++id) {
        auto &lista = ranking[id];
        sort(lista.begin(), lista.end(), [](const RankingEntry &a, const RankingEntry &b) {
            return a.promedio < b.promedio;
        });

        cout << "===== Ranking categoria " << nombreCategoria(id) << " =====" << endl;
        if (lista.empty()) {
            cout << "Sin participantes." << endl;
            continue;
        }
        int posicion = 1;
        for (const auto &entry : lista) {
            auto it = clientes.find(entry.idCliente);
            string nombre = "Desconocido";
            if (it != clientes.end()) {
                nombre = string(it->second.getNombre()) + " " + it->second.getApellido();
            }
            cout << posicion++ << ") " << nombre << " - Promedio: " << entry.promedio << endl;
        }
    }
    system("pause");
}

void podioGeneral() {
    system("cls");
    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    vector<vector<Participantes>> participantesPorCarrera;
    cargarParticipantesPorCarrera(carreras, participantesPorCarrera);
    map<int, Clientes> clientes = mapaClientesPorId();

    map<int, vector<RankingEntry>> ranking;
    for (size_t i = 0; i < carreras.size(); ++i) {
        const Carrera &carrera = carreras[i];
        int vueltas = vueltasPorCategoria(carrera.getIdCategoria());
        const auto &lista = (i < participantesPorCarrera.size()) ? participantesPorCarrera[i] : vector<Participantes>();
        for (const auto &participante : lista) {
            if (!participante.getEstado()) {
                continue;
            }
            RankingEntry entry;
            entry.idCliente = participante.getIdCliente();
            entry.promedio = participante.calcularPromedio(vueltas, carrera.getHoraInicio());
            if (entry.promedio > 0.0) {
                ranking[carrera.getIdCategoria()].push_back(entry);
            }
        }
    }

    cout << fixed << setprecision(2);
    for (int id = 1; id <= 3; ++id) {
        auto &lista = ranking[id];
        sort(lista.begin(), lista.end(), [](const RankingEntry &a, const RankingEntry &b) {
            return a.promedio < b.promedio;
        });

        cout << "===== Podio categoria " << nombreCategoria(id) << " =====" << endl;
        if (lista.empty()) {
            cout << "Sin participantes." << endl;
            continue;
        }
        int limite = min<size_t>(3, lista.size());
        for (int i = 0; i < limite; ++i) {
            const auto &entry = lista[i];
            auto it = clientes.find(entry.idCliente);
            string nombre = "Desconocido";
            if (it != clientes.end()) {
                nombre = string(it->second.getNombre()) + " " + it->second.getApellido();
            }
            cout << (i + 1) << ") " << nombre << " - Promedio: " << entry.promedio << endl;
        }
    }
    system("pause");
}

void clientesFrecuentes() {
    system("cls");
    vector<Carrera> carreras;
    if (!cargarCarrerasActivas(carreras) || carreras.empty()) {
        cout << "No hay carreras registradas." << endl;
        system("pause");
        return;
    }

    vector<vector<Participantes>> participantesPorCarrera;
    cargarParticipantesPorCarrera(carreras, participantesPorCarrera);

    set<int> mesesTotales;
    for (const auto &carrera : carreras) {
        mesesTotales.insert(claveMes(carrera.getFecha()));
    }

    map<int, set<int>> mesesPorCliente;
    for (size_t i = 0; i < carreras.size(); ++i) {
        int clave = claveMes(carreras[i].getFecha());
        const auto &lista = (i < participantesPorCarrera.size()) ? participantesPorCarrera[i] : vector<Participantes>();
        for (const auto &participante : lista) {
            if (participante.getEstado()) {
                mesesPorCliente[participante.getIdCliente()].insert(clave);
            }
        }
    }

    map<int, Clientes> clientes = mapaClientesPorId();
    bool hayFrecuentes = false;
    cout << "======= CLIENTES FRECUENTES =======" << endl;
    for (const auto &par : mesesPorCliente) {
        if (!mesesTotales.empty() && par.second.size() == mesesTotales.size()) {
            hayFrecuentes = true;
            auto it = clientes.find(par.first);
            if (it != clientes.end()) {
                cout << it->second.getNombre() << ' ' << it->second.getApellido() << endl;
            } else {
                cout << "Cliente ID " << par.first << endl;
            }
        }
    }

    if (!hayFrecuentes) {
        cout << "No hay clientes que cumplan con la condicion." << endl;
    }
    system("pause");
}

void menuInformes() {
    int opcion = -1;
    do {
        system("cls");
        cout << "======= MENU INFORMES =======" << endl;
        cout << "1) Ranking por categoria" << endl;
        cout << "2) Podio general de pilotos" << endl;
        cout << "3) Clientes frecuentes" << endl;
        cout << "0) Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida." << endl;
            system("pause");
            continue;
        }

        switch (opcion) {
            case 1:
                rankingPorCategoria();
                break;
            case 2:
                podioGeneral();
                break;
            case 3:
                clientesFrecuentes();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
                system("pause");
                break;
        }
    } while (opcion != 0);
}
