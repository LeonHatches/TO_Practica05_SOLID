#pragma once
#include "CanalNotificacion.h"

class EnviadorCorreo : public CanalNotificacion {
public:
    void enviarNotificacion(const std::string& mensaje) override;
};