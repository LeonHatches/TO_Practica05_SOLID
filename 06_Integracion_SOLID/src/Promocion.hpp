#pragma once

// Ejercicio 06 - OCP
// Responsable: Persona 2
class Promocion {
public:
    virtual ~Promocion() = default;

    // TODO (Persona 2): Definir una interfaz común para las estrategias de descuento.
    // TODO (Persona 2): Permitir agregar promociones nuevas sin modificar el cálculo principal de precios.
};
