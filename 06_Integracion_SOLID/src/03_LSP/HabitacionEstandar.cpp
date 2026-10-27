#include "HabitacionEstandar.h"

HabitacionEstandar::HabitacionEstandar(int numero)
    : Habitacion(numero, 2, 120.0) {}

std::string HabitacionEstandar::getTipo() const {
    return "Estandar";
}