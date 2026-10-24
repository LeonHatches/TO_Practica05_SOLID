#include "CalculadoraPrecioHabitacion.h"
#include "FechaReserva.h"
#include <cmath>
#include <stdexcept>

CalculadoraPrecioHabitacion::Cotizacion CalculadoraPrecioHabitacion::calcular(
        double tarifaPorNoche, const std::string& entrada,
        const std::string& salida, Temporada temporada,
        const EstrategiaPromocion& promocion) const {
    if (!std::isfinite(tarifaPorNoche) || tarifaPorNoche < 0)
        throw std::invalid_argument("Tarifa por noche invalida");
    const int cantidad = fechas::noches(entrada, salida);
    double factor = 1.0;
    switch (temporada) {
        case Temporada::Baja: factor = 0.90; break;
        case Temporada::Regular: factor = 1.00; break;
        case Temporada::Alta: factor = 1.25; break;
        default: throw std::invalid_argument("Temporada invalida");
    }
    const double subtotal = cantidad * tarifaPorNoche * factor;
    const double total = promocion ? promocion(subtotal) : subtotal;
    if (!std::isfinite(total) || total < 0)
        throw std::invalid_argument("La promocion devolvio un precio invalido");
    return {cantidad, tarifaPorNoche, factor, subtotal, total};
}
