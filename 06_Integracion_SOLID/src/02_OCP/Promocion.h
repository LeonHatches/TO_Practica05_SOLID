#pragma once

class Promocion {
public:
    virtual ~Promocion() = default;

    // Recibe el subtotal y devuelve el precio final, no el descuento.
    virtual double aplicar(double subtotal) const = 0;
};
