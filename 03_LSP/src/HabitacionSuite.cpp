#include "HabitacionSuite.h"

HabitacionSuite::HabitacionSuite(int numero)
    : Habitacion(numero, 4, 280.0) {}

std::string HabitacionSuite::getTipo() const {
    return "Suite";
}