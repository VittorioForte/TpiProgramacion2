#ifndef CATEGORIAS_H_INCLUDED
#define CATEGORIAS_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Categorias {
private:
    bool estado;
    int idCategoria;  // 1 SI ES PROFESIONAL / 2 SI ES AMATEUR / 3 SI ES INFANTIL
    int cantVueltas;  // 20 = PROFESIONAL / 15 = AMATEUR / 10 = INFANTIL
    string nombreCat;  // PROFESIONAL - 1 - 20 VUELTAS / AMATEUR - 2 - 15 VUELTAS / INFANTIL - 3 - 10 VUELTAS

public:
    Categorias();
    Categorias(int aIdCategoria, int aCantVueltas, bool aEstado, const string &aNombreCat);

    // GETTERS
    bool getEstado() const;
    int getIdCategoria() const;
    int getCantVueltas() const;
    const string &getNombreCat() const;

    // SETTERS
    void setEstado(bool aEstado);
    void setIdCategoria(int aIdCategoria);
    void setNombreCat(const string &aNombreCat);
    void setCantVueltas(int aCantVueltas);

    // METODOS ADICIONALES
    void cargar();
    void mostrar() const;
};

vector<Categorias> crearCategoriasPredeterminadas();
const Categorias *buscarCategoriaPorId(const vector<Categorias> &categorias, int idCategoria);
void mostrarListadoCategorias(const vector<Categorias> &categorias);

#endif // CATEGORIAS_H_INCLUDED
