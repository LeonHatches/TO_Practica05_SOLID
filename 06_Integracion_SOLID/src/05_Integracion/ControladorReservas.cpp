#include "ControladorReservas.h"
#include <utility>

// Ejercicio 06 - Integracion
// Responsable: Persona 3 - Integración final

// TODO (Persona 1): Conectar disponibilidad y calculo de precios.
// TODO (Persona 2): Conectar reservas, cancelaciones y promociones.
// TODO (Persona 4): Conectar servicios y notificaciones.
// TODO (Todos): Comprobar el funcionamiento conjunto y los cinco principios SOLID.

// Persona 3: Registrar habitaciones
bool ControladorReservas::registrarHabitacion(
    std::unique_ptr<Habitacion> habitacion) {

    if (!habitacion || buscarHabitacion(habitacion->getNumero()) != nullptr) {
        return false;
    }

    habitaciones.push_back(std::move(habitacion));
    return true;
}

// Persona 3: Registrar clientes
bool ControladorReservas::registrarCliente(
    std::unique_ptr<Cliente> cliente) {

    if (!cliente || buscarCliente(cliente->getId()) != nullptr) {
        return false;
    }

    clientes.push_back(std::move(cliente));
    return true;
}

// Persona 3: Buscar habitacion por numero
const Habitacion* ControladorReservas::buscarHabitacion(int numero) const {
    for (const auto& habitacion : habitaciones) {
        if (habitacion->getNumero() == numero) {
            return habitacion.get();
        }
    }

    return nullptr;
}

// Persona 3: Buscar cliente por identificador
Cliente* ControladorReservas::buscarCliente(int id) {
    for (const auto& cliente : clientes) {
        if (cliente->getId() == id) {
            return cliente.get();
        }
    }

    return nullptr;
}

// Persona 3: Buscar habitaciones segun su capacidad
std::vector<const Habitacion*> ControladorReservas::buscarPorCapacidad(
    int huespedes) const {

    std::vector<const Habitacion*> resultado;

    for (const auto& habitacion : habitaciones) {
        if (habitacion->admiteHuespedes(huespedes)) {
            resultado.push_back(habitacion.get());
        }
    }

    return resultado;
}

// TODO (Persona 3): Coordinar estos metodos con Reserva,
// disponibilidad, precios, promociones y notificaciones
// cuando los demas modulos esten terminados.