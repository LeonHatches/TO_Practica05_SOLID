#include "PromocionTemporadaAlta.h"
#include <cmath>
#include <stdexcept>

PromocionTemporadaAlta::PromocionTemporadaAlta(
        double porcentajeDescuento, bool esTemporadaAlta)
    : porcentajeDescuento(porcentajeDescuento), esTemporadaAlta(esTemporadaAlta) {
    if (!std::isfinite(porcentajeDescuento) ||
        porcentajeDescuento < 0.0 || porcentajeDescuento > 100.0) {
        throw std::invalid_argument("El descuento debe estar entre 0 y 100.");
    }
}

double PromocionTemporadaAlta::aplicar(double subtotal) const {
    if (!std::isfinite(subtotal) || subtotal < 0.0) {
        throw std::invalid_argument("El subtotal debe ser finito y no negativo.");
    }
    if (!esTemporadaAlta) {
        return subtotal;
    }
    return subtotal * (1.0 - porcentajeDescuento / 100.0);
}
