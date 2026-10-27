#pragma once

#include <ctime>
#include <string>

class PoliticaCancelacion;

class Reserva {
private:
    int id;
    int idCliente;
    int numeroHabitacion;
    std::time_t fechaCheckIn;
    std::time_t fechaCheckOut;
    double montoTotal;
    const PoliticaCancelacion& politica;
    bool cancelada;
    double penalizacion;

public:
    Reserva(int id, int idCliente, int numeroHabitacion,
            std::time_t fechaCheckIn, std::time_t fechaCheckOut,
            double montoTotal, const PoliticaCancelacion& politica);

    int getId() const;
    int getIdCliente() const;
    int getNumeroHabitacion() const;
    std::time_t getFechaCheckIn() const;
    std::time_t getFechaCheckOut() const;
    // Fechas AAAA-MM-DD para disponibilidad y calculo de precios.
    std::string getFechaEntrada() const;
    std::string getFechaSalida() const;
    double getMontoTotal() const;
    bool estaCancelada() const;
    double getPenalizacion() const;

    bool cancelar(std::time_t fechaCancelacion);
};
