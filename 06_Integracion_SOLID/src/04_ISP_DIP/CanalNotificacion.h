#pragma once
#include <string>

class CanalNotificacion {
public:
    virtual ~CanalNotificacion() = default;
    virtual void enviarNotificacion(const std::string& mensaje) = 0;
};