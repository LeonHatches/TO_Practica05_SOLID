#pragma once
#include <string>

class ServicioLavanderia {
public:
    virtual ~ServicioLavanderia() = default;
    virtual void lavarRopa(int idHabitacion) = 0;
};