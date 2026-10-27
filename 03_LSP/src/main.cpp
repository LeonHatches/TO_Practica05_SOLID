#include "../../06_Integracion_SOLID/src/03_LSP/HabitacionEstandar.h"
#include "../../06_Integracion_SOLID/src/03_LSP/HabitacionSuite.h"
#include "../../06_Integracion_SOLID/src/03_LSP/HabitacionPremium.h"
#include <iostream>

void mostrarHabitacion(const Habitacion& habitacion) {
    std::cout << "Habitacion " << habitacion.getNumero()
              << " | Tipo: " << habitacion.getTipo()
              << " | Capacidad: " << habitacion.getCapacidad()
              << " | Tarifa: S/ " << habitacion.getTarifaPorNoche()
              << " | Admite 3 huespedes: "
              << (habitacion.admiteHuespedes(3) ? "Si" : "No")
              << '\n';
}

int main() {
    HabitacionEstandar estandar(101);
    HabitacionSuite suite(201);
    HabitacionPremium premium(301);

    const Habitacion* habitaciones[] = {
        &estandar, &suite, &premium
    };

    for (const Habitacion* habitacion : habitaciones) {
        mostrarHabitacion(*habitacion);
    }
}