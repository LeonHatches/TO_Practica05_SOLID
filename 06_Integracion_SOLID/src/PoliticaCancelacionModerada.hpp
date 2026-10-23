#pragma once

#include "PoliticaCancelacion.hpp"

// Ejercicio 06 - OCP
// Responsable: Persona 2
class PoliticaCancelacionModerada : public PoliticaCancelacion {
public:
    // TODO (Persona 2): Permitir cancelación hasta 72 horas antes del check-in con penalización del 50 %.
};
