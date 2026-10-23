#pragma once

// Ejercicio 06 - DIP
// Responsable: Persona 4
class CanalNotificacion {
public:
    virtual ~CanalNotificacion() = default;

    // TODO (Persona 4): Definir el contrato enviarNotificacion(mensaje) independiente del canal concreto.
};
