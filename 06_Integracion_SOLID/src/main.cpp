#include "05_Integracion/ControladorReservas.h"
#include "03_LSP/HabitacionEstandar.h"
#include "03_LSP/HabitacionSuite.h"
#include "03_LSP/HabitacionPremium.h"
#include "02_OCP/PoliticaCancelacionFlexible.h"
#include "02_OCP/PoliticaCancelacionModerada.h"
#include "02_OCP/PoliticaCancelacionEstricta.h"
#include "02_OCP/PromocionClienteFrecuente.h"
#include "02_OCP/PromocionTemporadaAlta.h"
#include "04_ISP_DIP/EjemploServicios.h"
#include "04_ISP_DIP/EnviadorCorreo.h"
#include "04_ISP_DIP/NotificadorReserva.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>

using Temporada = CalculadoraPrecioHabitacion::Temporada;

namespace {
void cargarEjemplos(ControladorReservas& controlador) {
    controlador.registrarHabitacion(std::make_unique<HabitacionEstandar>(101));
    controlador.registrarHabitacion(std::make_unique<HabitacionSuite>(201));
    controlador.registrarHabitacion(std::make_unique<HabitacionPremium>(301));
    controlador.registrarCliente(std::make_unique<Cliente>(
        1, "Ana Torres", "ana@correo.com", "987654321"));
    controlador.registrarCliente(std::make_unique<Cliente>(
        2, "Luis Ramos", "luis@correo.com", "999111222"));
}

void mostrarHabitaciones(const ControladorReservas& controlador,
                        const std::string& entrada = "2026-12-10",
                        const std::string& salida = "2026-12-13") {
    std::cout << "Habitaciones compatibles y libres entre " << entrada
              << " y " << salida << " para 3 huespedes:\n";
    for (const Habitacion* h : controlador.consultarDisponibles(3, entrada, salida))
        std::cout << "  " << h->getNumero() << " - " << h->getTipo()
                  << " (" << h->getCapacidad() << " personas, S/ "
                  << h->getTarifaPorNoche() << " por noche)\n";
}

void imprimirReserva(const Reserva& r) {
    std::cout << "Reserva " << r.getId() << " | Cliente " << r.getIdCliente()
              << " | Habitacion " << r.getNumeroHabitacion() << " | "
              << r.getFechaEntrada() << " a " << r.getFechaSalida()
              << " | Total S/ " << r.getMontoTotal()
              << " | Estado " << (r.estaCancelada() ? "CANCELADA" : "CONFIRMADA");
    if (r.estaCancelada()) std::cout << " | Penalizacion S/ " << r.getPenalizacion();
    std::cout << '\n';
}

void imprimirInforme(const ControladorReservas& c, const std::string& desde,
                     const std::string& hasta) {
    std::cout << "\nINFORME " << desde << " a " << hasta << " (salida excluida)\n";
    for (const auto& par : c.ocupacionPorTipo(desde, hasta))
        std::cout << "  " << par.first << ": " << par.second
                  << " reservas activas que cruzan el periodo\n";
    const auto ingresos = c.ingresosPorPeriodo(desde, hasta);
    std::cout << "  Importe de reservas activas con check-in en periodo: S/ "
              << ingresos.reservasConfirmadas << '\n';
    std::cout << "  Penalizaciones de cancelaciones en periodo: S/ "
              << ingresos.penalizaciones << '\n';
    std::cout << "  Total estimado: S/ " << ingresos.total() << '\n';
}

void demostracion(ControladorReservas& c) {
    std::cout << "=== SISTEMA DE RESERVAS - INTEGRACION SOLID ===\n";
    std::cout << "Demostracion con datos de ejemplo y fechas fijas.\n";
    mostrarHabitaciones(c);

    auto flexible = std::make_shared<PoliticaCancelacionFlexible>();
    auto moderada = std::make_shared<PoliticaCancelacionModerada>();
    auto estricta = std::make_shared<PoliticaCancelacionEstricta>();
    PromocionClienteFrecuente frecuente(10, true);
    PromocionTemporadaAlta temporadaAlta(20, true);

    const int r1 = c.crearReserva(1, 101, 2, "2026-12-10", "2026-12-12",
                                   flexible, Temporada::Regular, &frecuente);
    const int r2 = c.crearReserva(2, 201, 3, "2026-12-10", "2026-12-13",
                                   moderada, Temporada::Alta, &temporadaAlta);
    const int r3 = c.crearReserva(1, 301, 3, "2026-12-20", "2026-12-22",
                                   estricta);
    imprimirReserva(*c.buscarReserva(r1));
    imprimirReserva(*c.buscarReserva(r2));
    imprimirReserva(*c.buscarReserva(r3));

    try {
        c.crearReserva(2, 101, 1, "2026-12-11", "2026-12-13", flexible);
        std::cout << "ERROR: reserva superpuesta aceptada\n";
    } catch (const std::logic_error& e) {
        std::cout << "Reserva superpuesta rechazada: " << e.what() << '\n';
    }
    mostrarHabitaciones(c);

    const bool cancelacionModerada = c.cancelarReserva(
        r2, "2026-12-01");
    std::cout << "Cancelar reserva 2 (moderada): "
              << (cancelacionModerada ? "ACEPTADA" : "RECHAZADA") << '\n';
    const bool cancelacionEstricta = c.cancelarReserva(
        r3, "2026-12-01");
    std::cout << "Cancelar reserva 3 (estricta): "
              << (cancelacionEstricta ? "ACEPTADA" : "RECHAZADA") << '\n';
    imprimirReserva(*c.buscarReserva(r2));
    mostrarHabitaciones(c);

    c.registrarEntrada(r1);
    c.solicitarLimpieza(101);
    c.solicitarComida(101, "Desayuno");
    c.solicitarLavanderia(101);
    c.registrarSalida(r1);

    std::cout << "\nHistorial de Ana:\n";
    for (const Reserva* r : c.historialCliente(1)) imprimirReserva(*r);
    imprimirInforme(c, "2026-12-01", "2027-01-01");
    std::cout << "\nDemostracion integrada finalizada.\n";
}

std::string leerTexto(const char* texto) {
    std::cout << texto;
    std::string dato;
    std::getline(std::cin >> std::ws, dato);
    if (dato.empty()) throw std::invalid_argument("El texto no puede estar vacio");
    return dato;
}

int leerEntero(const char* texto) {
    std::cout << texto;
    int valor;
    if (!(std::cin >> valor)) throw std::invalid_argument("Se esperaba un numero entero");
    return valor;
}

void ejecutarMenu(ControladorReservas& c) {
    std::cout << "Modo interactivo: datos de ejemplo precargados.\n";
    while (true) {
        std::cout << "\n1. Registrar habitacion  2. Registrar cliente\n"
                     "3. Consultar disponibles 4. Crear reserva\n"
                     "5. Cancelar reserva    6. Check-in\n"
                     "7. Check-out           8. Solicitar servicio\n"
                     "9. Historial cliente   10. Informes\n"
                     "0. Salir\n";
        int opcion;
        try {
            opcion = leerEntero("Opcion: ");
            if (opcion == 0) return;
            if (opcion == 1) {
                int tipo = leerEntero("Tipo (1 Estandar, 2 Suite, 3 Premium): ");
                int numero = leerEntero("Numero de habitacion: ");
                std::unique_ptr<Habitacion> habitacion;
                if (tipo == 1) habitacion = std::make_unique<HabitacionEstandar>(numero);
                else if (tipo == 2) habitacion = std::make_unique<HabitacionSuite>(numero);
                else if (tipo == 3) habitacion = std::make_unique<HabitacionPremium>(numero);
                else throw std::invalid_argument("Tipo no reconocido");
                std::cout << (c.registrarHabitacion(std::move(habitacion))
                    ? "Habitacion registrada\n" : "Numero duplicado\n");
            } else if (opcion == 2) {
                int id = leerEntero("ID de cliente: ");
                auto cliente = std::make_unique<Cliente>(id, leerTexto("Nombre: "),
                    leerTexto("Correo: "), leerTexto("Telefono: "));
                std::cout << (c.registrarCliente(std::move(cliente))
                    ? "Cliente registrado\n" : "ID de cliente duplicado\n");
            } else if (opcion == 3) {
                int cantidad = leerEntero("Huespedes: ");
                auto entrada = leerTexto("Entrada AAAA-MM-DD: ");
                auto salida = leerTexto("Salida AAAA-MM-DD: ");
                const auto libres = c.consultarDisponibles(cantidad, entrada, salida);
                if (libres.empty()) std::cout << "Sin habitaciones compatibles libres.\n";
                for (const auto* h : libres)
                    std::cout << h->getNumero() << " " << h->getTipo()
                              << " S/ " << h->getTarifaPorNoche() << "/noche\n";
            } else if (opcion == 4) {
                int cliente = leerEntero("ID de cliente: ");
                int habitacion = leerEntero("Numero de habitacion: ");
                int huespedes = leerEntero("Huespedes: ");
                auto entrada = leerTexto("Entrada AAAA-MM-DD: ");
                auto salida = leerTexto("Salida AAAA-MM-DD: ");
                int pol = leerEntero("Politica (1 Flexible, 2 Moderada, 3 Estricta): ");
                std::shared_ptr<const PoliticaCancelacion> politica;
                if (pol == 1) politica = std::make_shared<PoliticaCancelacionFlexible>();
                else if (pol == 2) politica = std::make_shared<PoliticaCancelacionModerada>();
                else if (pol == 3) politica = std::make_shared<PoliticaCancelacionEstricta>();
                else throw std::invalid_argument("Politica no reconocida");
                int t = leerEntero("Temporada (1 Baja, 2 Regular, 3 Alta): ");
                if (t < 1 || t > 3) throw std::invalid_argument("Temporada no reconocida");
                auto temporada = t == 1 ? Temporada::Baja :
                                 t == 3 ? Temporada::Alta : Temporada::Regular;
                int p = leerEntero("Promocion (0 Ninguna, 1 Frecuente, 2 Temporada alta): ");
                PromocionClienteFrecuente frecuente(10, true);
                PromocionTemporadaAlta alta(20, t == 3);
                if (p < 0 || p > 2) throw std::invalid_argument("Promocion no reconocida");
                const Promocion* promocion = p == 1 ? static_cast<const Promocion*>(&frecuente)
                    : (p == 2 ? static_cast<const Promocion*>(&alta) : nullptr);
                int id = c.crearReserva(cliente, habitacion, huespedes, entrada, salida,
                                         std::move(politica), temporada, promocion);
                imprimirReserva(*c.buscarReserva(id));
            } else if (opcion == 5) {
                int id = leerEntero("ID de reserva: ");
                auto fecha = leerTexto("Fecha de cancelacion AAAA-MM-DD: ");
                bool ok = c.cancelarReserva(id, fecha);
                std::cout << (ok ? "Reserva cancelada\n" : "Cancelacion rechazada\n");
                if (ok) imprimirReserva(*c.buscarReserva(id));
            } else if (opcion == 6 || opcion == 7) {
                int id = leerEntero("ID de reserva: ");
                bool ok = opcion == 6 ? c.registrarEntrada(id) : c.registrarSalida(id);
                std::cout << (ok ? "Operacion registrada\n" : "Operacion no permitida\n");
            } else if (opcion == 8) {
                int numero = leerEntero("Numero de habitacion: ");
                int servicio = leerEntero("Servicio (1 Limpieza, 2 Comida, 3 Lavanderia): ");
                bool ok = servicio == 1 ? c.solicitarLimpieza(numero) :
                    servicio == 2 ? c.solicitarComida(numero, leerTexto("Pedido: ")) :
                    servicio == 3 ? c.solicitarLavanderia(numero) : false;
                std::cout << (ok ? "Servicio solicitado\n" : "Solicitud rechazada\n");
            } else if (opcion == 9) {
                int id = leerEntero("ID de cliente: ");
                const auto historial = c.historialCliente(id);
                if (historial.empty()) std::cout << "Sin reservas registradas.\n";
                for (const auto* r : historial) imprimirReserva(*r);
            } else if (opcion == 10) {
                auto desde = leerTexto("Inicio AAAA-MM-DD: ");
                auto hasta = leerTexto("Fin excluido AAAA-MM-DD: ");
                imprimirInforme(c, desde, hasta);
            } else {
                std::cout << "Opcion desconocida.\n";
            }
        } catch (const std::exception& e) {
            if (std::cin.eof()) return;
            std::cout << "Operacion rechazada: " << e.what() << '\n';
            if (!std::cin) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
}
}

int main(int argc, char** argv) {
    std::cout << std::fixed << std::setprecision(2);
    PersonalLimpieza limpieza;
    PersonalComida comida;
    PersonalLavanderia lavanderia;
    PersonalRecepcion recepcion;
    EnviadorCorreo correo;
    NotificadorReserva notificador(correo);
    ControladorReservas controlador(limpieza, comida, lavanderia, recepcion, notificador);
    cargarEjemplos(controlador);
    try {
        if (argc > 1 && std::string(argv[1]) == "--menu") ejecutarMenu(controlador);
        else demostracion(controlador);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
