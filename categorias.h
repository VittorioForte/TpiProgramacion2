#ifndef CATEGORIAS_H_INCLUDED
#define CATEGORIAS_H_INCLUDED

class Categorias {
private:
    bool estado;
    int idCategoria, cantVueltas;
    string nombreCat;

public:

    Categorias (int aIdCategoria, int aCantVueltas, bool aEstado, string aNombreCat){
        setIdCategoria(aIdCategoria);
        setCantVueltas(aCantVueltas);
        setEstado(aEstado);
        setNombreCat(aNombreCat);
    }

    //GETTERS



    //SETTERS

    void setEstado(bool aEstado){
        estado = aEstado;
    }

    void setIdCategoria(int aIdCategoria){
        idCategoria = aIdCategoria;
    }

    void setNombreCat(string aNombreCat){
        if(aNombreCat == "PROFESIONAL"){
            aCantVueltas = 20;
        }else if(aNombreCat == "AMATEUR"){
            aCantVueltas = 15;
        }else if(aNombreCat == "INFANTIL"){
            aCantVueltas = 10;
        }else {
            cout << "Categoria no Valida... " << endl;
            estado = false;
        };
    }

    void setCantVueltas(int aCantVueltas){
        cantVueltas = aCantVueltas;
    }


    //METODOS ADICIONALES

};


#endif // CATEGORIAS_H_INCLUDED
