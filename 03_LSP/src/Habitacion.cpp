#include "Habitacion.h"
#include <stdexcept>

Habitacion::Habitacion(int numero, int capacidad, double tarifa)
    : numero(numero), capacidad(capacidad), tarifaPorNoche(tarifa) {

    if (numero <= 0 || capacidad <= 0 || tarifa <= 0) {
        throw std::invalid_argument("Datos de habitacion invalidos.");
    }
}

int Habitacion::getNumero() const {
    return numero;
}

int Habitacion::getCapacidad() const {
    return capacidad;
}

double Habitacion::getTarifaPorNoche() const {
    return tarifaPorNoche;
}

bool Habitacion::admiteHuespedes(int cantidad) const {
    return cantidad > 0 && cantidad <= capacidad;
}