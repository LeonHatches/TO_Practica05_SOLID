#pragma once
#include <string>

class ServicioLimpieza {
public:
    virtual ~ServicioLimpieza() = default;
    virtual void limpiarHabitacion(int idHabitacion) = 0;
};