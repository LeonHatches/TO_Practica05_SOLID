#include "Reserva.h"
#include "PoliticaCancelacionFlexible.h"
#include "PoliticaCancelacionModerada.h"
#include "PoliticaCancelacionEstricta.h"
#include <ctime>
#include <iomanip>
#include <iostream>

std::time_t crearFecha(int dia, int mes, int anio, int hora) {
    std::tm fecha = {};
    fecha.tm_mday = dia;
    fecha.tm_mon = mes - 1;
    fecha.tm_year = anio - 1900;
    fecha.tm_hour = hora;
    fecha.tm_isdst = -1;

    return std::mktime(&fecha);
}

void mostrarCaso(const char* descripcion, const PoliticaCancelacion& politica,
                 std::time_t checkIn, std::time_t fechaCancelacion) {
    Reserva reserva(checkIn, 400.0, politica);
    const bool permitida = reserva.cancelar(fechaCancelacion);
    std::cout << descripcion << ": " << (permitida ? "Permitida" : "Rechazada")
              << " | Penalizacion: S/ " << reserva.getPenalizacion() << '\n';
}

int main() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Ejercicio 02 - Politicas de cancelacion (OCP)\n"
              << "Check-in: 10/11/2026 15:00 | Total: S/ 400.00\n\n";

    const std::time_t checkIn = crearFecha(10, 11, 2026, 15);
    PoliticaCancelacionFlexible flexible;
    PoliticaCancelacionModerada moderada;
    PoliticaCancelacionEstricta estricta;

    mostrarCaso("Flexible, 24 horas antes", flexible, checkIn,
                crearFecha(9, 11, 2026, 15));
    mostrarCaso("Flexible, 23 horas antes", flexible, checkIn,
                crearFecha(9, 11, 2026, 16));
    mostrarCaso("Moderada, 72 horas antes", moderada, checkIn,
                crearFecha(7, 11, 2026, 15));
    mostrarCaso("Moderada, 71 horas antes", moderada, checkIn,
                crearFecha(7, 11, 2026, 16));
    mostrarCaso("Estricta, varios dias antes", estricta, checkIn,
                crearFecha(1, 11, 2026, 15));

    return 0;
}
