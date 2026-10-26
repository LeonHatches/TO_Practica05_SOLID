#pragma once
#include "ServicioLimpieza.h"
#include "ServicioComida.h"
#include "ServicioLavanderia.h"
#include "IPersonalRecepcion.h"
#include <iostream>


class PersonalLimpieza : public ServicioLimpieza {
public:
    void limpiarHabitacion(int id) override {
        std::cout << "Limpieza de habitacion " << id << '\n';
    }
};
class PersonalComida : public ServicioComida {
public:
    void servirComida(int id, const std::string& pedido) override {
        std::cout << "Comida para habitacion " << id << ": " << pedido << '\n';
    }
};
class PersonalLavanderia : public ServicioLavanderia {
public:
    void lavarRopa(int id) override {
        std::cout << "Lavanderia de habitacion " << id << '\n';
    }
};
class PersonalRecepcion : public IPersonalRecepcion {
public:
    void registrarEntrada(int id) override {
        std::cout << "Entrada de reserva " << id << '\n';
    }
    void registrarSalida(int id) override {
        std::cout << "Salida de reserva " << id << '\n';
    }
};

