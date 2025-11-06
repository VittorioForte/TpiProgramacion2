#ifndef PARTICIPANTES_H_INCLUDED
#define PARTICIPANTES_H_INCLUDED

class Participantes {
private:
    bool estado;
    int idCliente;
    int idCarrera;
    double horaFinal;
    int tiempoVueltas;

public:
    bool getEstado() const { return estado; }
    int getIdCliente() const { return idCliente; }
    int getIdCarrera() const { return idCarrera; }
    double getHoraFinal() const { return horaFinal; }
    int getTiempoVueltas() const { return tiempoVueltas; }

    void setEstado(bool e) { estado = e; }
    void setIdCliente(int id) { idCliente = id; }
    void setIdCarrera(int id) { idCarrera = id; }
    void setHoraFinal(double h) { horaFinal = h; }
    void setTiempoVueltas(int t) { tiempoVueltas = t; }

    bool escribirDisco(int pos);
    bool leerDisco(int pos);
};

#endif // PARTICIPANTES_H_INCLUDED
