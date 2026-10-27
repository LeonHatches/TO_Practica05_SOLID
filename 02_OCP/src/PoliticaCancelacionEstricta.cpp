#include "PoliticaCancelacionEstricta.h"

bool PoliticaCancelacionEstricta::puedeCancelar(
        const Reserva&, std::time_t) const {
    return false;
}

double PoliticaCancelacionEstricta::calcularPenalizacion(const Reserva&) const {
    // La cancelacion se rechaza, por lo que no se aplica una penalizacion.
    return 0.0;
}
