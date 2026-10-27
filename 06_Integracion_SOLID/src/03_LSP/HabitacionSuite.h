#ifndef HABITACION_SUITE_H
#define HABITACION_SUITE_H

#include "Habitacion.h"

class HabitacionSuite : public Habitacion {
public:
    explicit HabitacionSuite(int numero);
    std::string getTipo() const override;
};

#endif