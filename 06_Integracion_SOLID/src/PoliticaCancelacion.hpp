#pragma once

// Ejercicio 06 - OCP
// Responsable: Persona 2
class PoliticaCancelacion {
public:
    virtual ~PoliticaCancelacion() = default;

    // TODO (Persona 2): Definir el contrato para decidir si una reserva puede cancelarse y qué penalización aplicar.
    // TODO (Persona 2): Evitar condicionales por tipo de política dentro de Reserva.
};
