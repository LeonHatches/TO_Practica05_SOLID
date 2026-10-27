#ifndef HABITACION_PREMIUM_H
#define HABITACION_PREMIUM_H

#include "Habitacion.h"

class HabitacionPremium : public Habitacion {
public:
    explicit HabitacionPremium(int numero);
    std::string getTipo() const override;
};

#endif