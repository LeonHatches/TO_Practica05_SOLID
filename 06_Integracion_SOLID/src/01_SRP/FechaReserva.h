#pragma once
#include <string>
#include <stdexcept>
#include <tuple>
#include <cctype>

namespace fechas {
inline bool bisiesto(int a) { return (a % 4 == 0 && a % 100 != 0) || a % 400 == 0; }
inline int diasMes(int a, int m) {
    static const int dias[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    return dias[m-1] + (m == 2 && bisiesto(a));
}
// Número ordinal de día: permite comparar y obtener duración sin zonas horarias.
inline int ordinal(const std::string& fecha) {
    if (fecha.size() != 10 || fecha[4] != '-' || fecha[7] != '-')
        throw std::invalid_argument("Fecha invalida: se requiere AAAA-MM-DD");
    for (int i = 0; i < 10; ++i)
        if (i != 4 && i != 7 && !std::isdigit(static_cast<unsigned char>(fecha[i])))
            throw std::invalid_argument("Fecha invalida: se requiere AAAA-MM-DD");
    int a = std::stoi(fecha.substr(0,4)), m = std::stoi(fecha.substr(5,2)), d = std::stoi(fecha.substr(8,2));
    if (a < 1 || m < 1 || m > 12 || d < 1 || d > diasMes(a,m))
        throw std::invalid_argument("Fecha no existe: " + fecha);
    int a1 = a - 1;
    int n = 365*a1 + a1/4 - a1/100 + a1/400 + d;
    for (int i = 1; i < m; ++i) n += diasMes(a,i);
    return n;
}
inline int noches(const std::string& entrada, const std::string& salida) {
    int n = ordinal(salida) - ordinal(entrada);
    if (n <= 0) throw std::invalid_argument("La salida debe ser posterior a la entrada");
    return n;
}
}
