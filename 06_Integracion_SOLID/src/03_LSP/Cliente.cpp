#include "Cliente.h"
#include <algorithm>
#include <stdexcept>

Cliente::Cliente(int id, const std::string& nombre,
                 const std::string& correo, const std::string& telefono)
    : id(id), nombre(nombre), correo(correo), telefono(telefono) {

    if (id <= 0 || nombre.empty() || (correo.empty() && telefono.empty())) {
        throw std::invalid_argument("Datos de cliente invalidos.");
    }
}

int Cliente::getId() const {
    return id;
}

const std::string& Cliente::getNombre() const {
    return nombre;
}

const std::string& Cliente::getCorreo() const {
    return correo;
}

const std::string& Cliente::getTelefono() const {
    return telefono;
}

bool Cliente::agregarReserva(int idReserva) {
    if (idReserva <= 0) {
        throw std::invalid_argument("Identificador de reserva invalido.");
    }

    if (std::find(reservas.begin(), reservas.end(), idReserva) != reservas.end()) {
        return false;
    }

    reservas.push_back(idReserva);
    return true;
}

const std::vector<int>& Cliente::getReservas() const {
    return reservas;
}