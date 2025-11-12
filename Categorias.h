#pragma once

#include <iostream>
#include <string>
#include <cstring>

class Categorias {
private:
    bool _estado;
    int _idCategoria;
    int _cantVueltas;
    char _nombreCat[30];

public:
    Categorias();
    Categorias(int IdCategoria, int CantVueltas, bool Estado, std::string NombreCat);

    // Getters
    bool getEstado() const;
    int getIdCategoria() const;
    int getCantVueltas() const;
    const char* getNombreCat() const;

    // Setters
    void setEstado(bool Estado);
    void setIdCategoria(int IdCategoria);
    void setNombreCat(std::string NombreCat);
    void setCantVueltas(int CantVueltas);

    // Métodos adicionales
    void cargar();
    void mostrar() const;
};
