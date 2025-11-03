#ifndef CATEGORIAS_H_INCLUDED
#define CATEGORIAS_H_INCLUDED
#include <string>
#include <iostream>

using namespace std;

class Categorias {
private:
    bool estado;
    int idCategoria; //1 SI ES PROFESIONAL / 2 SI ES AMATEUR / 3 SI ES INFANTIL
    int cantVueltas; //20 = PROFESIONAL / 15 = AMATEUR / 10 = INFANTIL
    string nombreCat; //PROFESIONAL - 1 - 20 VUELTAS / AMATEUR - 2 - 15 VUELTAS / INFANTIL - 3 - 10 VUELTAS

public:

    Categorias() {
        estado = false;
        idCategoria = 0;
        cantVueltas = 0;
        nombreCat = "";
    }

    Categorias (int aIdCategoria, int aCantVueltas, bool aEstado, string aNombreCat){
        setIdCategoria(aIdCategoria);
        setCantVueltas(aCantVueltas);
        setEstado(aEstado);
        setNombreCat(aNombreCat);
    }

    //GETTERS

    bool getEstado() const { return estado; }
    int getIdCategoria() const { return idCategoria; }
    int getCantVueltas() const { return cantVueltas; }
    string getNombreCat() const { return nombreCat; }

    //SETTERS

    void setEstado(bool aEstado){
        estado = aEstado;
    }

    void setIdCategoria(int aIdCategoria){
        idCategoria = aIdCategoria;
    }

    void setNombreCat(string aNombreCat){
        nombreCat = aNombreCat;


        if(aNombreCat == "PROFESIONAL"){
            cantVueltas = 20;
            idCategoria = 1;
            estado = true;
        }else if(aNombreCat == "AMATEUR"){
            cantVueltas = 15;
            idCategoria = 2;
            estado = true;
        }else if(aNombreCat == "INFANTIL"){
            cantVueltas = 10;
            idCategoria = 3;
            estado = true;
        }else {
            cout << "Categoria no Valida... " << endl;
            cantVueltas = 0;
            idCategoria = 0;
            estado = false;
        };
    }

    void setCantVueltas(int aCantVueltas){
        cantVueltas = aCantVueltas;
    }


    //METODOS ADICIONALES
    void cargar(){
        cout << "Ingrese nombre de categoria en mayuscula (PROFESIONAL / AMATEUR / INFANTIL): ";
        cin >> nombreCat;
        setNombreCat(nombreCat);
    }

    void mostrar() const {
        cout << "--------------------------------" << endl;
        cout << "ID Categoria: " << idCategoria << endl;
        cout << "Nombre: " << nombreCat << endl;
        cout << "Cantidad de vueltas: " << cantVueltas << endl;
        cout << "Estado: " << (estado ? "Activo" : "Inactivo") << endl;
    }
};


#endif // CATEGORIAS_H_INCLUDED
