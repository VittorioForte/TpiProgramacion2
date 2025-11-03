#include "categorias.h"

#include <algorithm>
#include <limits>

using namespace std;

Categorias::Categorias()
    : estado(false), idCategoria(0), cantVueltas(0), nombreCat("") {}

Categorias::Categorias(int aIdCategoria, int aCantVueltas, bool aEstado, const string &aNombreCat)
    : estado(false), idCategoria(0), cantVueltas(0), nombreCat("") {
    setIdCategoria(aIdCategoria);
    setCantVueltas(aCantVueltas);
    setEstado(aEstado);
    setNombreCat(aNombreCat);
}

bool Categorias::getEstado() const { return estado; }

int Categorias::getIdCategoria() const { return idCategoria; }

int Categorias::getCantVueltas() const { return cantVueltas; }

const string &Categorias::getNombreCat() const { return nombreCat; }

void Categorias::setEstado(bool aEstado) { estado = aEstado; }

void Categorias::setIdCategoria(int aIdCategoria) { idCategoria = aIdCategoria; }

void Categorias::setNombreCat(const string &aNombreCat) {
    nombreCat = aNombreCat;

    if (aNombreCat == "PROFESIONAL") {
        cantVueltas = 20;
        idCategoria = 1;
        estado = true;
    } else if (aNombreCat == "AMATEUR") {
        cantVueltas = 15;
        idCategoria = 2;
        estado = true;
    } else if (aNombreCat == "INFANTIL") {
        cantVueltas = 10;
        idCategoria = 3;
        estado = true;
    } else {
        cout << "Categoria no Valida... " << endl;
        cantVueltas = 0;
        idCategoria = 0;
        estado = false;
    }
}

void Categorias::setCantVueltas(int aCantVueltas) { cantVueltas = aCantVueltas; }

void Categorias::cargar() {
    cout << "Ingrese nombre de categoria en mayuscula (PROFESIONAL / AMATEUR / INFANTIL): ";
    string nombre;
    cin >> nombre;
    setNombreCat(nombre);
}

void Categorias::mostrar() const {
    cout << "--------------------------------" << endl;
    cout << "ID Categoria: " << idCategoria << endl;
    cout << "Nombre: " << nombreCat << endl;
    cout << "Cantidad de vueltas: " << cantVueltas << endl;
    cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
}

vector<Categorias> crearCategoriasPredeterminadas() {
    vector<Categorias> categorias;
    categorias.emplace_back(1, 20, true, "PROFESIONAL");
    categorias.emplace_back(2, 15, true, "AMATEUR");
    categorias.emplace_back(3, 10, true, "INFANTIL");
    return categorias;
}

const Categorias *buscarCategoriaPorId(const vector<Categorias> &categorias, int idCategoria) {
    auto it = find_if(categorias.begin(), categorias.end(),
                           [idCategoria](const Categorias &categoria) { return categoria.getIdCategoria() == idCategoria; });
    if (it == categorias.end()) {
        return nullptr;
    }
    return &(*it);
}

void mostrarListadoCategorias(const vector<Categorias> &categorias) {
    cout << "======= CATEGORIAS DISPONIBLES =======" << endl;
    for (const Categorias &categoria : categorias) {
        categoria.mostrar();
    }
}
