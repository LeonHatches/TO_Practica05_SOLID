#pragma once

#include "Promocion.h"

class PromocionTemporadaAlta : public Promocion {
private:
    double porcentajeDescuento;
    bool esTemporadaAlta;

public:
    PromocionTemporadaAlta(double porcentajeDescuento, bool esTemporadaAlta);
    double aplicar(double subtotal) const override;
};
