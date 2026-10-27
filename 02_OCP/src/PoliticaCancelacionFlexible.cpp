#include "PoliticaCancelacionFlexible.h"
#include "Reserva.h"

bool PoliticaCancelacionFlexible::puedeCancelar(
        const Reserva& reserva, std::time_t fechaCancelacion) const {
    const double segundosRestantes =
        std::difftime(reserva.getFechaCheckIn(), fechaCancelacion);
    return segundosRestantes >= 24 * 60 * 60;
}

double PoliticaCancelacionFlexible::calcularPenalizacion(const Reserva&) const {
    return 0.0;
}
