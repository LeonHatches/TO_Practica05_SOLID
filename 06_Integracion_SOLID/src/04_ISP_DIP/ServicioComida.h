#pragma once
#include <string>

class ServicioComida {
public:
    virtual ~ServicioComida() = default;
    virtual void servirComida(int idHabitacion, const std::string& pedido) = 0;
};










