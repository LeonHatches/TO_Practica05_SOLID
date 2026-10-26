#pragma once
#include "CanalNotificacion.h"

class NotificadorReserva {
public:
    // El canal debe vivir mas tiempo que el notificador.
    explicit NotificadorReserva(CanalNotificacion& canal);
    void notificarConfirmacion(int idReserva);
    void notificarCancelacion(int idReserva);
private:
    CanalNotificacion& canal_;
};


