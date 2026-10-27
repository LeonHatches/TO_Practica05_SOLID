#ifndef HABITACION_ESTANDAR_H
#define HABITACION_ESTANDAR_H

#include "Habitacion.h"

class HabitacionEstandar : public Habitacion {
public:
    explicit HabitacionEstandar(int numero);
    std::string getTipo() const override;
};

#endif