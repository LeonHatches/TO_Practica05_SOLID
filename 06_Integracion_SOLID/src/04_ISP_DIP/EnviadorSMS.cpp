#include "EnviadorSMS.h"
#include <iostream>

void EnviadorSMS::enviarNotificacion(const std::string& mensaje) {
    std::cout << "[SMS simulado] " << mensaje << '\n';
}