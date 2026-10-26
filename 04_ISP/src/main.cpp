#include "../../06_Integracion_SOLID/src/04_ISP_DIP/EjemploServicios.h"

void prepararHabitacion(ServicioLimpieza& servicio, int id) {
    servicio.limpiarHabitacion(id);
}
int main() {
    PersonalLimpieza limpieza;
    PersonalComida comida;
    PersonalLavanderia lavanderia;
    PersonalRecepcion recepcion;
    prepararHabitacion(limpieza, 101);
    ServicioComida& servicioComida = comida;
    servicioComida.servirComida(101, "Desayuno");
    ServicioLavanderia& servicioLavanderia = lavanderia;
    servicioLavanderia.lavarRopa(101);
    IPersonalRecepcion& servicioRecepcion = recepcion;
    servicioRecepcion.registrarEntrada(1);
    servicioRecepcion.registrarSalida(1);
}