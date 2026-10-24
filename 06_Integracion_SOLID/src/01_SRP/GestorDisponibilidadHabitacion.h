#pragma once
#include <string>
#include <vector>

// Responsabilidad unica: administrar ocupacion, nunca calcular tarifas.
class GestorDisponibilidadHabitacion {
public:
    struct Ocupacion {
        int identificador;
        int habitacionId;
        std::string entrada;
        std::string salida; // fecha de salida excluida
    };
    bool estaDisponible(int habitacionId, const std::string& entrada,
                        const std::string& salida) const;
    int reservar(int habitacionId, const std::string& entrada,
                const std::string& salida);
    bool cancelar(int identificador);
    const std::vector<Ocupacion>& obtenerOcupaciones() const;
private:
    std::vector<Ocupacion> ocupaciones_;
    int siguienteId_ = 1;
};
