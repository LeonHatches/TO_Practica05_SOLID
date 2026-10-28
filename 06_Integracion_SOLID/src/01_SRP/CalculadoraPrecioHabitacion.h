#pragma once
#include <string>
#include <functional>

// SRP: calcula tarifas; no crea ni modifica reservas.
class CalculadoraPrecioHabitacion {
public:
    enum class Temporada { Baja, Regular, Alta };
    // Estrategia de descuento aplicable al subtotal.
    // Recibe subtotal y devuelve importe final (no negativo).
    using EstrategiaPromocion = std::function<double(double)>;
    struct Cotizacion {
        int noches;
        double tarifaPorNoche;
        double factorTemporada;
        double subtotal;
        double total;
    };
    Cotizacion calcular(double tarifaPorNoche, const std::string& entrada,
                        const std::string& salida, Temporada temporada,
                        const EstrategiaPromocion& promocion = {}) const;
};
