#ifndef HABITACION_H
#define HABITACION_H

#include <string>

class Habitacion {
protected:
    int numero;
    int capacidad;
    double tarifaPorNoche;

public:
    Habitacion(int numero, int capacidad, double tarifa);

    virtual ~Habitacion() = default;

    int getNumero() const;
    int getCapacidad() const;
    double getTarifaPorNoche() const;

    virtual std::string getTipo() const = 0;

    bool admiteHuespedes(int cantidad) const;
};

#endif