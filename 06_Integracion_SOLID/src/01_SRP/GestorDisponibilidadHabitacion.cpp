#include "GestorDisponibilidadHabitacion.h"
#include "FechaReserva.h"
#include <algorithm>
#include <stdexcept>

bool GestorDisponibilidadHabitacion::estaDisponible(int habitacionId,
        const std::string& entrada, const std::string& salida) const {
    if (habitacionId <= 0) throw std::invalid_argument("ID de habitacion invalido");
    fechas::noches(entrada, salida);
    const int inicio = fechas::ordinal(entrada), fin = fechas::ordinal(salida);
    for (const auto& reserva : ocupaciones_) {
        if (reserva.habitacionId == habitacionId &&
            inicio < fechas::ordinal(reserva.salida) &&
            fechas::ordinal(reserva.entrada) < fin) return false;
    }
    return true;
}

int GestorDisponibilidadHabitacion::reservar(int habitacionId,
        const std::string& entrada, const std::string& salida) {
    if (!estaDisponible(habitacionId, entrada, salida))
        throw std::logic_error("La habitacion no esta disponible en esas fechas");
    const int id = siguienteId_++;
    ocupaciones_.push_back({id, habitacionId, entrada, salida});
    return id;
}

bool GestorDisponibilidadHabitacion::cancelar(int identificador) {
    const auto it = std::find_if(ocupaciones_.begin(), ocupaciones_.end(),
        [identificador](const Ocupacion& r) { return r.identificador == identificador; });
    if (it == ocupaciones_.end()) return false;
    ocupaciones_.erase(it);
    return true;
}

const std::vector<GestorDisponibilidadHabitacion::Ocupacion>&
GestorDisponibilidadHabitacion::obtenerOcupaciones() const { return ocupaciones_; }
