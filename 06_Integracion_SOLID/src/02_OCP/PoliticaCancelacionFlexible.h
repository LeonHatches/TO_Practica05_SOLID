#pragma once

#include "PoliticaCancelacion.h"

class PoliticaCancelacionFlexible : public PoliticaCancelacion {
public:
    bool puedeCancelar(const Reserva& reserva,
                       std::time_t fechaCancelacion) const override;
    double calcularPenalizacion(const Reserva& reserva) const override;
};
