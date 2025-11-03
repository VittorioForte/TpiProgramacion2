#ifndef PARTICIPANTES_H_INCLUDED
#define PARTICIPANTES_H_INCLUDED

class Participantes {
private:
    bool estado;
    int idCliente;
    int tiempoVueltas;
    double horaFinal;

public:
    Participantes();

    //GETTERS
    int getIdCliente() const;
    double getHoraFinal() const;
    int getTiempoVueltas() const;
    bool getEstado() const;

    //SETTERS
    void setIdCliente(int aIdCliente);
    void setHoraFinal(double aHoraFinal);
    void setTiempoVueltas(int aTiempo);
    void setEstado(bool aEstado);

    //METODOS ADICIONALES
    void cargar(int numeroVueltas);
    void mostrar() const;
    double calcularPromedio(int cantidadVueltas, double horaInicio) const;
    bool grabarEnDisco() const;
    bool leerDeDisco(int pos);
    bool modificarEnDisco(int pos) const;
};

void menuParticipantes();

#endif // PARTICIPANTES_H_INCLUDED
