#pragma once
#include <string>

class IPersonalRecepcion {
public:
    virtual ~IPersonalRecepcion() = default;
    virtual void registrarEntrada(int idReserva) = 0;
    virtual void registrarSalida(int idReserva) = 0;
};