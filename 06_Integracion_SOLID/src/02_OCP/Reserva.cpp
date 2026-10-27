#include "Reserva.h"
#include "PoliticaCancelacion.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {
std::string fechaComoTexto(std::time_t fecha) {
    const std::tm* calendario = std::localtime(&fecha);
    if (calendario == nullptr) {
        throw std::invalid_argument("Fecha fuera de rango.");
    }
    std::ostringstream texto;
    texto << std::put_time(calendario, "%Y-%m-%d");
    return texto.str();
}
}

Reserva::Reserva(int id, int idCliente, int numeroHabitacion,
                 std::time_t fechaCheckIn, std::time_t fechaCheckOut,
                 double montoTotal, const PoliticaCancelacion& politica)
    : id(id), idCliente(idCliente), numeroHabitacion(numeroHabitacion),
      fechaCheckIn(fechaCheckIn), fechaCheckOut(fechaCheckOut),
      montoTotal(montoTotal), politica(politica), cancelada(false), penalizacion(0.0) {
    if (id <= 0 || idCliente <= 0 || numeroHabitacion <= 0) {
        throw std::invalid_argument("Los identificadores deben ser positivos.");
    }
    if (std::difftime(fechaCheckOut, fechaCheckIn) <= 0) {
        throw std::invalid_argument("El check-out debe ser posterior al check-in.");
    }
    if (!std::isfinite(montoTotal) || montoTotal < 0.0) {
        throw std::invalid_argument("El monto total debe ser finito y no negativo.");
    }
}

int Reserva::getId() const {
    return id;
}

int Reserva::getIdCliente() const {
    return idCliente;
}

int Reserva::getNumeroHabitacion() const {
    return numeroHabitacion;
}

std::time_t Reserva::getFechaCheckIn() const {
    return fechaCheckIn;
}

std::time_t Reserva::getFechaCheckOut() const {
    return fechaCheckOut;
}

std::string Reserva::getFechaEntrada() const {
    return fechaComoTexto(fechaCheckIn);
}

std::string Reserva::getFechaSalida() const {
    return fechaComoTexto(fechaCheckOut);
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
    // OCP: la decision y el importe dependen de la politica seleccionada.
    if (cancelada || !politica.puedeCancelar(*this, fechaCancelacion)) {
        return false;
    }
    penalizacion = politica.calcularPenalizacion(*this);
    cancelada = true;
    return true;
}
