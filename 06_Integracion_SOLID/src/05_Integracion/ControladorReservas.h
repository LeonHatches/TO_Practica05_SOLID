#pragma once

#include "../03_LSP/Cliente.h"
#include "../03_LSP/Habitacion.h"
#include <memory>
#include <vector>

// Ejercicio 06 - Integracion
// Responsable: Persona 3 - Integración final

class ControladorReservas {
private:
    // Persona 3: Habitaciones y clientes
    std::vector<std::unique_ptr<Habitacion>> habitaciones;
    std::vector<std::unique_ptr<Cliente>> clientes;

public:
    // TODO (Persona 1): Conectar disponibilidad y calculo de precios.
    // TODO (Persona 2): Conectar reservas, cancelaciones y promociones.
    // TODO (Persona 4): Conectar servicios y notificaciones.
    // TODO (Todos): Comprobar el funcionamiento conjunto y los cinco principios SOLID.

    // Persona 3: Registro de habitaciones y clientes
    bool registrarHabitacion(std::unique_ptr<Habitacion> habitacion);
    bool registrarCliente(std::unique_ptr<Cliente> cliente);

    // Persona 3: Consultas
    const Habitacion* buscarHabitacion(int numero) const;
    Cliente* buscarCliente(int id);

    std::vector<const Habitacion*> buscarPorCapacidad(int huespedes) const;

    // TODO (Persona 3): Completar la coordinacion con los demas modulos.
};