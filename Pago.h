#pragma once

class Pago {
private:
    int _idPago;
    int _idCarrera;
    int _idCliente;
    double _monto;
    bool _pagado;
    bool _estado;

public:
    Pago();

    void setIdPago(int idPago);
    void setIdCarrera(int idCarrera);
    void setIdCliente(int idCliente);
    void setMonto(double monto);
    void setPagado(bool pagado);
    void setEstado(bool estado);

    int getIdPago() const;
    int getIdCarrera() const;
    int getIdCliente() const;
    double getMonto() const;
    bool getPagado() const;
    bool getEstado() const;

    void mostrar() const;
};

