#include <iostream>
#include "05_Integracion/ControladorReservas.h"
#include "04_ISP_DIP/EjemploServicios.h"
#include "04_ISP_DIP/EnviadorCorreo.h"
#include "04_ISP_DIP/EnviadorSMS.h"
#include "04_ISP_DIP/NotificadorReserva.h"
#include "03_LSP/HabitacionEstandar.h"

int main() {
    // TODO (Persona 1): integrar disponibilidad y precios.
    // TODO (Persona 2): integrar cancelaciones y promociones.
    // TODO (Persona 3): coordinar el controlador y las habitaciones.
    // Persona 4: el controlador recibe los servicios y el notificador.
    PersonalLimpieza limpieza;
    PersonalComida comida;
    PersonalLavanderia lavanderia;
    PersonalRecepcion recepcion;
    EnviadorCorreo correo;
    EnviadorSMS sms;
    NotificadorReserva porCorreo(correo);
    NotificadorReserva porSMS(sms);
    ControladorReservas controlador(limpieza, comida, lavanderia, recepcion, porCorreo);
    controlador.registrarHabitacion(std::make_unique<HabitacionEstandar>(101));
    controlador.solicitarLimpieza(101);
    controlador.solicitarComida(101, "Desayuno");
    controlador.solicitarLavanderia(101);
    // Identificadores de ejemplo: Reserva aun no implementa el flujo real.
    controlador.registrarEntrada(1);
    controlador.notificarConfirmacion(1);
    controlador.registrarSalida(1);
    // El mismo controlador puede utilizar un notificador con otro canal.
    ControladorReservas controladorSMS(limpieza, comida, lavanderia, recepcion, porSMS);
    controladorSMS.notificarCancelacion(1);
    // TODO (Todos): probar el flujo completo del sistema de reservas.
    std::cout << "Ejercicio 06: estructura de integracion SOLID preparada." << std::endl;
    return 0;
}
