#pragma once

#include <ctime>

class Reserva;

class PoliticaCancelacion {
public:
    virtual ~PoliticaCancelacion() = default;

    virtual bool puedeCancelar(const Reserva& reserva,
                               std::time_t fechaCancelacion) const = 0;
    virtual double calcularPenalizacion(const Reserva& reserva) const = 0;
};
