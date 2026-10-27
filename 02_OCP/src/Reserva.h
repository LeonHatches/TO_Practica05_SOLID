#pragma once

#include <ctime>

class PoliticaCancelacion;

class Reserva {
private:
    std::time_t fechaCheckIn;
    double montoTotal;
    const PoliticaCancelacion& politica;
    bool cancelada;
    double penalizacion;

public:
    Reserva(std::time_t fechaCheckIn, double montoTotal,
            const PoliticaCancelacion& politica);

    std::time_t getFechaCheckIn() const;
    double getMontoTotal() const;
    bool estaCancelada() const;
    double getPenalizacion() const;

    bool cancelar(std::time_t fechaCancelacion);
};
