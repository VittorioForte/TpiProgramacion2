#ifndef PARTICIPANTES_H_INCLUDED
#define PARTICIPANTES_H_INCLUDED

class participantes {
private:
    bool estado;
    int idCliente, tiempoVueltas;
    double horaFinal;

public:

    //GETTERS
    int getIdCliente();
    int getHoraFinal();
    int getTiempoVueltas();
    bool getEstado();

    //SETTERS


    //METODOS ADICIONALES
};

void menuParticipantes();

#endif // PARTICIPANTES_H_INCLUDED
