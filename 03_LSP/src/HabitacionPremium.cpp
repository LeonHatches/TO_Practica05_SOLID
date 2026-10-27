#include "HabitacionPremium.h"

HabitacionPremium::HabitacionPremium(int numero)
    : Habitacion(numero, 3, 420.0) {}

std::string HabitacionPremium::getTipo() const {
    return "Premium";
}