#include "../../06_Integracion_SOLID/src/04_ISP_DIP/EnviadorCorreo.h"
#include "../../06_Integracion_SOLID/src/04_ISP_DIP/EnviadorSMS.h"
#include "../../06_Integracion_SOLID/src/04_ISP_DIP/NotificadorReserva.h"

int main() {
    EnviadorCorreo correo;
    EnviadorSMS sms;
    NotificadorReserva porCorreo(correo);
    NotificadorReserva porSMS(sms);
    porCorreo.notificarConfirmacion(1);
    porSMS.notificarConfirmacion(1);
    porCorreo.notificarCancelacion(1);
    porSMS.notificarCancelacion(1);
}