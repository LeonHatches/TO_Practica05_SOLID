#pragma once

#include <string>
#include <vector>

class Cliente {
private:
    int id;
    std::string nombre;
    std::string correo;
    std::string telefono;
    std::vector<int> reservas;

public:
    Cliente(int id, const std::string& nombre,
            const std::string& correo, const std::string& telefono);

    int getId() const;
    const std::string& getNombre() const;
    const std::string& getCorreo() const;
    const std::string& getTelefono() const;

    bool agregarReserva(int idReserva);
    const std::vector<int>& getReservas() const;
};