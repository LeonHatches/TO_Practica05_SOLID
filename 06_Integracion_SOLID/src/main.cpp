#include <iostream>
#include "05_Integracion/ControladorReservas.h"
#include "04_ISP_DIP/EjemploServicios.h"
#include "04_ISP_DIP/EnviadorCorreo.h"
#include "04_ISP_DIP/EnviadorSMS.h"
#include "04_ISP_DIP/NotificadorReserva.h"

int main() {
    // TODO (Persona 1): integrar disponibilidad y precios.
    // TODO (Persona 2): integrar cancelaciones y promociones.
    // TODO (Persona 3): coordinar el controlador y las habitaciones.
    // Demostracion de Persona 4. El controlador podra recibir estas interfaces.
    PersonalLimpieza limpieza;
    PersonalComida comida;
    PersonalLavanderia lavanderia;
    PersonalRecepcion recepcion;
    ServicioLimpieza& servicioLimpieza = limpieza;
    ServicioComida& servicioComida = comida;
    ServicioLavanderia& servicioLavanderia = lavanderia;
    IPersonalRecepcion& servicioRecepcion = recepcion;
    servicioRecepcion.registrarEntrada(1);
    servicioLimpieza.limpiarHabitacion(101);
    servicioComida.servirComida(101, "Desayuno");
    servicioLavanderia.lavarRopa(101);
    EnviadorCorreo correo;
    EnviadorSMS sms;
    NotificadorReserva porCorreo(correo);
    NotificadorReserva porSMS(sms);
    porCorreo.notificarConfirmacion(1);
    porSMS.notificarCancelacion(1);
    servicioRecepcion.registrarSalida(1);
    // TODO (Todos): probar el flujo completo del sistema de reservas.
    std::cout << "Ejercicio 06: estructura de integracion SOLID preparada." << std::endl;
    return 0;
}
