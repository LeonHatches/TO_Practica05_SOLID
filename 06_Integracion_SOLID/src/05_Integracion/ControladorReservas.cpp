#include "ControladorReservas.h"
#include "../02_OCP/PoliticaCancelacion.h"
#include "../02_OCP/Promocion.h"
#include "../01_SRP/FechaReserva.h"
#include <algorithm>
#include <stdexcept>
#include <utility>

// Conversion de fecha usada por Reserva y sus politicas de cancelacion.
namespace {
std::time_t fechaLocal(const std::string& fecha, int hora = 12) {
    fechas::ordinal(fecha);  // valida AAAA-MM-DD y calendario real
    if (hora < 0 || hora > 23) throw std::invalid_argument("Hora invalida");
    std::tm datos{};
    datos.tm_year = std::stoi(fecha.substr(0, 4)) - 1900;
    datos.tm_mon = std::stoi(fecha.substr(5, 2)) - 1;
    datos.tm_mday = std::stoi(fecha.substr(8, 2));
    datos.tm_hour = hora;
    datos.tm_isdst = -1;
    const std::time_t valor = std::mktime(&datos);
    if (valor == static_cast<std::time_t>(-1))
        throw std::invalid_argument("Fecha fuera de rango");
    return valor;
}
}

// registro, busqueda, LSP y coordinacion.
bool ControladorReservas::registrarHabitacion(std::unique_ptr<Habitacion> habitacion) {
    if (!habitacion || buscarHabitacion(habitacion->getNumero())) return false;
    habitaciones.push_back(std::move(habitacion));
    return true;
}

bool ControladorReservas::registrarCliente(std::unique_ptr<Cliente> cliente) {
    if (!cliente || buscarCliente(cliente->getId())) return false;
    clientes.push_back(std::move(cliente));
    return true;
}

const Habitacion* ControladorReservas::buscarHabitacion(int numero) const {
    for (const auto& habitacion : habitaciones)
        if (habitacion->getNumero() == numero) return habitacion.get();
    return nullptr;
}

Cliente* ControladorReservas::buscarCliente(int id) {
    for (auto& cliente : clientes)
        if (cliente->getId() == id) return cliente.get();
    return nullptr;
}

const Cliente* ControladorReservas::buscarCliente(int id) const {
    for (const auto& cliente : clientes)
        if (cliente->getId() == id) return cliente.get();
    return nullptr;
}

std::vector<const Habitacion*> ControladorReservas::buscarPorCapacidad(int huespedes) const {
    std::vector<const Habitacion*> resultado;
    for (const auto& habitacion : habitaciones)
        if (habitacion->admiteHuespedes(huespedes)) resultado.push_back(habitacion.get());
    return resultado;
}

// gestor de ocupaciones y cotizador; el controlador solo los coordina.
bool ControladorReservas::estaDisponible(int numeroHabitacion,
        const std::string& entrada, const std::string& salida) const {
    if (!buscarHabitacion(numeroHabitacion)) return false;
    return gestorDisponibilidad_.estaDisponible(numeroHabitacion, entrada, salida);
}

std::vector<const Habitacion*> ControladorReservas::consultarDisponibles(
        int huespedes, const std::string& entrada, const std::string& salida) const {
    fechas::noches(entrada, salida);
    std::vector<const Habitacion*> resultado;
    for (const auto& habitacion : habitaciones) {
        if (habitacion->admiteHuespedes(huespedes) &&
            gestorDisponibilidad_.estaDisponible(habitacion->getNumero(), entrada, salida)) {
            resultado.push_back(habitacion.get());
        }
    }
    return resultado;
}

// politica y promocion se usan a traves de sus abstracciones.
int ControladorReservas::crearReserva(int idCliente, int numeroHabitacion,
        int huespedes, const std::string& entrada, const std::string& salida,
        std::shared_ptr<const PoliticaCancelacion> politica,
        CalculadoraPrecioHabitacion::Temporada temporada, const Promocion* promocion) {
    Cliente* cliente = buscarCliente(idCliente);
    const Habitacion* habitacion = buscarHabitacion(numeroHabitacion);
    if (!cliente) throw std::invalid_argument("Cliente no registrado");
    if (!habitacion) throw std::invalid_argument("Habitacion no registrada");
    if (!habitacion->admiteHuespedes(huespedes))
        throw std::invalid_argument("La cantidad de huespedes supera la capacidad");
    if (!politica) throw std::invalid_argument("Se requiere una politica de cancelacion");
    if (!gestorDisponibilidad_.estaDisponible(numeroHabitacion, entrada, salida))
        throw std::logic_error("Habitacion ocupada para esas fechas");

    CalculadoraPrecioHabitacion::EstrategiaPromocion descuento;
    if (promocion)
        descuento = [promocion](double subtotal) { return promocion->aplicar(subtotal); };
    const auto cotizacion = calculadora_.calcular(
        habitacion->getTarifaPorNoche(), entrada, salida, temporada, descuento);
    const int idReserva = siguienteReservaId_;
    // Habitualmente entrada 14:00 y salida 11:00; siempre fechas locales.
    auto nueva = std::make_unique<Reserva>(
        idReserva, idCliente, numeroHabitacion,
        fechaLocal(entrada, 14), fechaLocal(salida, 11),
        cotizacion.total, *politica);

    // Se prepara la memoria antes de marcar la habitacion ocupada.
    reservas_.reserve(reservas_.size() + 1);
    const int idOcupacion = gestorDisponibilidad_.reservar(numeroHabitacion, entrada, salida);
    reservas_.push_back({std::move(politica), std::move(nueva), idOcupacion, 0});
    ++siguienteReservaId_;
    cliente->agregarReserva(idReserva);
    // El envio se realiza unicamente despues de confirmar el registro.
    if (notificador_) notificador_->notificarConfirmacion(idReserva);
    return idReserva;
}

const Reserva* ControladorReservas::buscarReserva(int idReserva) const {
    for (const auto& registro : reservas_)
        if (registro.reserva->getId() == idReserva) return registro.reserva.get();
    return nullptr;
}

bool ControladorReservas::cancelarReserva(int idReserva, std::time_t fechaCancelacion) {
    for (auto& registro : reservas_) {
        if (registro.reserva->getId() != idReserva) continue;
        if (entradasRegistradas_.count(idReserva) || registro.reserva->estaCancelada())
            return false;
        if (!registro.reserva->cancelar(fechaCancelacion)) return false;
        registro.fechaCancelacion = fechaCancelacion;
        gestorDisponibilidad_.cancelar(registro.idOcupacion);
        if (notificador_) notificador_->notificarCancelacion(idReserva);
        return true;
    }
    return false;
}

bool ControladorReservas::cancelarReserva(int idReserva, const std::string& fechaCancelacion) {
    return cancelarReserva(idReserva, fechaLocal(fechaCancelacion));
}

std::vector<const Reserva*> ControladorReservas::historialCliente(int idCliente) const {
    std::vector<const Reserva*> resultado;
    const Cliente* cliente = buscarCliente(idCliente);
    if (!cliente) return resultado;
    for (int id : cliente->getReservas()) {
        if (const Reserva* reserva = buscarReserva(id)) resultado.push_back(reserva);
    }
    return resultado;
}

std::map<std::string, int> ControladorReservas::ocupacionPorTipo(
        const std::string& entrada, const std::string& salida) const {
    const int inicio = fechas::ordinal(entrada);
    const int fin = fechas::ordinal(salida);
    if (fin <= inicio) throw std::invalid_argument("Periodo invalido");
    std::map<std::string, int> informe;
    for (const auto& habitacion : habitaciones)
        informe[habitacion->getTipo()] = 0;
    for (const auto& r : reservas_) {
        if (r.reserva->estaCancelada()) continue;
        if (inicio < fechas::ordinal(r.reserva->getFechaSalida()) &&
            fechas::ordinal(r.reserva->getFechaEntrada()) < fin) {
            const Habitacion* habitacion = buscarHabitacion(r.reserva->getNumeroHabitacion());
            if (habitacion) ++informe[habitacion->getTipo()];
        }
    }
    return informe;
}

ControladorReservas::InformeIngresos ControladorReservas::ingresosPorPeriodo(
        const std::string& entrada, const std::string& salida) const {
    const int inicio = fechas::ordinal(entrada), fin = fechas::ordinal(salida);
    if (fin <= inicio) throw std::invalid_argument("Periodo invalido");
    InformeIngresos informe;
    for (const auto& registro : reservas_) {
        const Reserva& r = *registro.reserva;
        if (!r.estaCancelada()) {
            const int fechaEntrada = fechas::ordinal(r.getFechaEntrada());
            if (fechaEntrada >= inicio && fechaEntrada < fin)
                informe.reservasConfirmadas += r.getMontoTotal();
        } else if (registro.fechaCancelacion != 0) {
            const std::tm* fecha = std::localtime(&registro.fechaCancelacion);
            if (fecha) {
                char fechaTexto[11]{};
                if (std::strftime(fechaTexto, sizeof(fechaTexto), "%Y-%m-%d", fecha)) {
                    const int fechaOrd = fechas::ordinal(fechaTexto);
                    if (fechaOrd >= inicio && fechaOrd < fin)
                        informe.penalizaciones += r.getPenalizacion();
                }
            }
        }
    }
    return informe;
}

// servicios especificos y notificaciones desacopladas.
ControladorReservas::ControladorReservas(ServicioLimpieza& limpieza, ServicioComida& comida,
        ServicioLavanderia& lavanderia, IPersonalRecepcion& recepcion,
        NotificadorReserva& notificador)
    : limpieza_(&limpieza), comida_(&comida), lavanderia_(&lavanderia),
      recepcion_(&recepcion), notificador_(&notificador) {}

bool ControladorReservas::solicitarLimpieza(int numeroHabitacion) {
    if (!limpieza_ || !buscarHabitacion(numeroHabitacion)) return false;
    limpieza_->limpiarHabitacion(numeroHabitacion);
    return true;
}

bool ControladorReservas::solicitarComida(int numeroHabitacion, const std::string& pedido) {
    if (!comida_ || !buscarHabitacion(numeroHabitacion) ||
        pedido.find_first_not_of(" \t\r\n") == std::string::npos) return false;
    comida_->servirComida(numeroHabitacion, pedido);
    return true;
}

bool ControladorReservas::solicitarLavanderia(int numeroHabitacion) {
    if (!lavanderia_ || !buscarHabitacion(numeroHabitacion)) return false;
    lavanderia_->lavarRopa(numeroHabitacion);
    return true;
}

bool ControladorReservas::registrarEntrada(int idReserva) {
    const Reserva* reserva = buscarReserva(idReserva);
    if (!recepcion_ || !reserva || reserva->estaCancelada() ||
        entradasRegistradas_.count(idReserva)) return false;
    recepcion_->registrarEntrada(idReserva);
    entradasRegistradas_.insert(idReserva);
    return true;
}

bool ControladorReservas::registrarSalida(int idReserva) {
    const Reserva* reserva = buscarReserva(idReserva);
    if (!recepcion_ || !reserva || reserva->estaCancelada() ||
        !entradasRegistradas_.count(idReserva) || salidasRegistradas_.count(idReserva))
        return false;
    recepcion_->registrarSalida(idReserva);
    salidasRegistradas_.insert(idReserva);
    // El historial sigue en Reserva. Una salida anticipada libera el bloqueo.
    for (const auto& registro : reservas_)
        if (registro.reserva->getId() == idReserva)
            gestorDisponibilidad_.cancelar(registro.idOcupacion);
    return true;
}

bool ControladorReservas::notificarConfirmacion(int idReserva) {
    const Reserva* reserva = buscarReserva(idReserva);
    if (!notificador_ || !reserva || reserva->estaCancelada()) return false;
    notificador_->notificarConfirmacion(idReserva);
    return true;
}

bool ControladorReservas::notificarCancelacion(int idReserva) {
    const Reserva* reserva = buscarReserva(idReserva);
    if (!notificador_ || !reserva || !reserva->estaCancelada()) return false;
    notificador_->notificarCancelacion(idReserva);
    return true;
}
