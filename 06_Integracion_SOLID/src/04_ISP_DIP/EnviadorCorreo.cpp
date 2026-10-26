#include "EnviadorCorreo.h"
#include <iostream>

void EnviadorCorreo::enviarNotificacion(const std::string& mensaje) {
    std::cout << "[Correo simulado] " << mensaje << '\n';
}