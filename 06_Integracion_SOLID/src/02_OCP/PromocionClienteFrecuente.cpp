#include "PromocionClienteFrecuente.h"
#include <cmath>
#include <stdexcept>

PromocionClienteFrecuente::PromocionClienteFrecuente(
        double porcentajeDescuento, bool esClienteFrecuente)
    : porcentajeDescuento(porcentajeDescuento), esClienteFrecuente(esClienteFrecuente) {
    if (!std::isfinite(porcentajeDescuento) ||
        porcentajeDescuento < 0.0 || porcentajeDescuento > 100.0) {
        throw std::invalid_argument("El descuento debe estar entre 0 y 100.");
    }
}

double PromocionClienteFrecuente::aplicar(double subtotal) const {
    if (!std::isfinite(subtotal) || subtotal < 0.0) {
        throw std::invalid_argument("El subtotal debe ser finito y no negativo.");
    }
    if (!esClienteFrecuente) {
        return subtotal;
    }
    return subtotal * (1.0 - porcentajeDescuento / 100.0);
}
