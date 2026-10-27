#pragma once

#include "Promocion.h"

class PromocionClienteFrecuente : public Promocion {
private:
    double porcentajeDescuento;
    bool esClienteFrecuente;

public:
    PromocionClienteFrecuente(double porcentajeDescuento, bool esClienteFrecuente);
    double aplicar(double subtotal) const override;
};
