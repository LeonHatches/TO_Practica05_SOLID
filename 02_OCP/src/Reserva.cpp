#include "Reserva.h"
#include "PoliticaCancelacion.h"
#include <cmath>
#include <stdexcept>

Reserva::Reserva(std::time_t fechaCheckIn, double montoTotal,
                 const PoliticaCancelacion& politica)
    : fechaCheckIn(fechaCheckIn), montoTotal(montoTotal), politica(politica),
      cancelada(false), penalizacion(0.0) {
    if (!std::isfinite(montoTotal) || montoTotal < 0.0) {
        throw std::invalid_argument("El monto total debe ser finito y no negativo.");
    }
}

std::time_t Reserva::getFechaCheckIn() const {
    return fechaCheckIn;
}

double Reserva::getMontoTotal() const {
    return montoTotal;
}

bool Reserva::estaCancelada() const {
    return cancelada;
}

double Reserva::getPenalizacion() const {
    return penalizacion;
}

bool Reserva::cancelar(std::time_t fechaCancelacion) {
    // OCP: Reserva utiliza la interfaz, sin conocer las politicas concretas.
    if (cancelada || !politica.puedeCancelar(*this, fechaCancelacion)) {
        return false;
    }

    penalizacion = politica.calcularPenalizacion(*this);
    cancelada = true;
    return true;
}
