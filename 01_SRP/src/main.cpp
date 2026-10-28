#include "../../06_Integracion_SOLID/src/01_SRP/GestorDisponibilidadHabitacion.h"
#include "../../06_Integracion_SOLID/src/01_SRP/CalculadoraPrecioHabitacion.h"
#include <iomanip>
#include <iostream>

int main() {
    GestorDisponibilidadHabitacion gestor;
    CalculadoraPrecioHabitacion calculadora;

    const int ocupacion =
        gestor.reservar(101, "2026-12-10", "2026-12-13");

    std::cout << "Reserva registrada: "
              << ocupacion << '\n';

    std::cout << "Habitacion 101 ocupada: "
              << (gestor.estaDisponible(
                  101, "2026-12-11", "2026-12-12") ? "No" : "Si")
              << '\n';

    auto precio = calculadora.calcular(
        120.0,
        "2026-12-10",
        "2026-12-13",
        CalculadoraPrecioHabitacion::Temporada::Regular
    );

    std::cout << std::fixed << std::setprecision(2)
              << "Precio por " << precio.noches
              << " noches: S/ " << precio.total << '\n';

    gestor.cancelar(ocupacion);

    std::cout << "Habitacion 101 disponible tras cancelar: "
              << (gestor.estaDisponible(
                  101, "2026-12-11", "2026-12-12") ? "Si" : "No")
              << '\n';

    return 0;
}