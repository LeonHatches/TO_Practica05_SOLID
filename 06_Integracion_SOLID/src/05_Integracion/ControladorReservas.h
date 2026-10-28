#pragma once

#include "../01_SRP/CalculadoraPrecioHabitacion.h"
#include "../01_SRP/GestorDisponibilidadHabitacion.h"
#include "../02_OCP/Reserva.h"
#include "../03_LSP/Cliente.h"
#include "../03_LSP/Habitacion.h"
#include "../04_ISP_DIP/ServicioLimpieza.h"
#include "../04_ISP_DIP/ServicioComida.h"
#include "../04_ISP_DIP/ServicioLavanderia.h"
#include "../04_ISP_DIP/IPersonalRecepcion.h"
#include "../04_ISP_DIP/NotificadorReserva.h"
#include <ctime>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

class PoliticaCancelacion;
class Promocion;

class ControladorReservas {
public:
    struct InformeIngresos {
        double reservasConfirmadas = 0.0; // reservas activas con entrada en el periodo
        double penalizaciones = 0.0;       // cancelaciones realizadas en el periodo
        double total() const { return reservasConfirmadas + penalizaciones; }
    };

    ControladorReservas() = default;
    ControladorReservas(ServicioLimpieza& limpieza, ServicioComida& comida,
                        ServicioLavanderia& lavanderia, IPersonalRecepcion& recepcion,
                        NotificadorReserva& notificador);

    bool registrarHabitacion(std::unique_ptr<Habitacion> habitacion);
    bool registrarCliente(std::unique_ptr<Cliente> cliente);
    const Habitacion* buscarHabitacion(int numero) const;
    Cliente* buscarCliente(int id);
    const Cliente* buscarCliente(int id) const;
    std::vector<const Habitacion*> buscarPorCapacidad(int huespedes) const;

    // Solo devuelve habitaciones compatibles que no tienen reservas superpuestas.
    std::vector<const Habitacion*> consultarDisponibles(
        int huespedes, const std::string& entrada, const std::string& salida) const;
    bool estaDisponible(int numeroHabitacion, const std::string& entrada,
                        const std::string& salida) const;

    // Las politicas se comparten y conservan su vida mientras exista la reserva.
    // La promocion se utiliza solo durante la cotizacion, no se almacena.
    // Lanza invalid_argument o logic_error si no se puede crear la reserva.
    int crearReserva(int idCliente, int numeroHabitacion, int huespedes,
                     const std::string& entrada, const std::string& salida,
                     std::shared_ptr<const PoliticaCancelacion> politica,
                     CalculadoraPrecioHabitacion::Temporada temporada =
                         CalculadoraPrecioHabitacion::Temporada::Regular,
                     const Promocion* promocion = nullptr);
    bool cancelarReserva(int idReserva, std::time_t fechaCancelacion);
    bool cancelarReserva(int idReserva, const std::string& fechaCancelacion);
    const Reserva* buscarReserva(int idReserva) const;
    std::vector<const Reserva*> historialCliente(int idCliente) const;

    // El intervalo se interpreta [entrada, salida): salida no incluida.
    std::map<std::string, int> ocupacionPorTipo(
        const std::string& entrada, const std::string& salida) const;
    InformeIngresos ingresosPorPeriodo(
        const std::string& entrada, const std::string& salida) const;

    bool solicitarLimpieza(int numeroHabitacion);
    bool solicitarComida(int numeroHabitacion, const std::string& pedido);
    bool solicitarLavanderia(int numeroHabitacion);
    bool registrarEntrada(int idReserva);
    bool registrarSalida(int idReserva);
    bool notificarConfirmacion(int idReserva);
    bool notificarCancelacion(int idReserva);

private:
    struct RegistroReserva {
        // La politica debe mantenerse viva durante toda la vida de Reserva.
        std::shared_ptr<const PoliticaCancelacion> politica;
        std::unique_ptr<Reserva> reserva;
        int idOcupacion = 0;
        std::time_t fechaCancelacion = 0;
    };

    std::vector<std::unique_ptr<Habitacion>> habitaciones;
    std::vector<std::unique_ptr<Cliente>> clientes;
    std::vector<RegistroReserva> reservas_;
    GestorDisponibilidadHabitacion gestorDisponibilidad_;
    CalculadoraPrecioHabitacion calculadora_;
    int siguienteReservaId_ = 1;
    std::unordered_set<int> entradasRegistradas_;
    std::unordered_set<int> salidasRegistradas_;

    // Dependencias no propietarias: deben vivir mas tiempo que el controlador.
    ServicioLimpieza* limpieza_ = nullptr;
    ServicioComida* comida_ = nullptr;
    ServicioLavanderia* lavanderia_ = nullptr;
    IPersonalRecepcion* recepcion_ = nullptr;
    NotificadorReserva* notificador_ = nullptr;
};
