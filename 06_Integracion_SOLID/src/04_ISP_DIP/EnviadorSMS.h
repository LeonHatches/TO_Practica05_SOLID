#pragma once
#include "CanalNotificacion.h"

class EnviadorSMS : public CanalNotificacion {
public:
    void enviarNotificacion(const std::string& mensaje) override;
};





