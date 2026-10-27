#include "PoliticaCancelacionModerada.h"
#include "Reserva.h"

bool PoliticaCancelacionModerada::puedeCancelar(
        const Reserva& reserva, std::time_t fechaCancelacion) const {
    const double segundosRestantes =
        std::difftime(reserva.getFechaCheckIn(), fechaCancelacion);
    return segundosRestantes >= 72 * 60 * 60;
}

double PoliticaCancelacionModerada::calcularPenalizacion(
        const Reserva& reserva) const {
    return reserva.getMontoTotal() * 0.5;
}
