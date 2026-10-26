#include "NotificadorReserva.h"
#include <stdexcept>
#include <string>

NotificadorReserva::NotificadorReserva(CanalNotificacion& canal) : canal_(canal) {}

void NotificadorReserva::notificarConfirmacion(int idReserva) {
    if (idReserva <= 0) throw std::invalid_argument("Identificador de reserva invalido.");
    canal_.enviarNotificacion("Reserva " + std::to_string(idReserva) + " confirmada.");
}

void NotificadorReserva::notificarCancelacion(int idReserva) {
    if (idReserva <= 0) throw std::invalid_argument("Identificador de reserva invalido.");
    canal_.enviarNotificacion("Reserva " + std::to_string(idReserva) + " cancelada.");
}