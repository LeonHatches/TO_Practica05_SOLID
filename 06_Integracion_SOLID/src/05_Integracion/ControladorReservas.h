#pragma once

#include "../03_LSP/Cliente.h"
#include "../03_LSP/Habitacion.h"
#include "../04_ISP_DIP/ServicioLimpieza.h"
#include "../04_ISP_DIP/ServicioComida.h"
#include "../04_ISP_DIP/ServicioLavanderia.h"
#include "../04_ISP_DIP/IPersonalRecepcion.h"
#include "../04_ISP_DIP/NotificadorReserva.h"
#include <memory>
#include <vector>

// Ejercicio 06 - Integracion
// Responsable: Persona 3 - Integración final

class ControladorReservas {
private:
    // Persona 3: Habitaciones y clientes
    std::vector<std::unique_ptr<Habitacion>> habitaciones;
    std::vector<std::unique_ptr<Cliente>> clientes;
    // Dependencias no propietarias: deben vivir mas tiempo que el controlador.
    ServicioLimpieza* limpieza_ = nullptr;
    ServicioComida* comida_ = nullptr;
    ServicioLavanderia* lavanderia_ = nullptr;
    IPersonalRecepcion* recepcion_ = nullptr;
    NotificadorReserva* notificador_ = nullptr;

public:
    // TODO (Persona 1): Conectar disponibilidad y calculo de precios.
    // TODO (Persona 2): Conectar reservas, cancelaciones y promociones.
    // Conserva la construccion sin servicios para los otros modulos.
    ControladorReservas() = default;
    ControladorReservas(ServicioLimpieza& limpieza, ServicioComida& comida,
                        ServicioLavanderia& lavanderia, IPersonalRecepcion& recepcion,
                        NotificadorReserva& notificador);

    // Devuelven false si falta la dependencia o la solicitud no es valida.
    bool solicitarLimpieza(int numeroHabitacion);
    bool solicitarComida(int numeroHabitacion, const std::string& pedido);
    bool solicitarLavanderia(int numeroHabitacion);
    bool registrarEntrada(int idReserva);
    bool registrarSalida(int idReserva);
    // El modulo de reservas debe invocarlas solo tras una operacion exitosa.
    // No crean ni cancelan reservas; validan unicamente el identificador.
    bool notificarConfirmacion(int idReserva);
    bool notificarCancelacion(int idReserva);
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
