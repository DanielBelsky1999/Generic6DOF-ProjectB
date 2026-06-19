#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <winsock2.h>
#include <ws2tcpip.h>

#include <vector>
#include <string>
#include <iomanip>

#include "Initializer.h"

#pragma comment(lib, "Ws2_32.lib")

class Tacview
{
public:

    enum class PlatformType
    {
        Plane,
        Helicopter,
        Rocket,
        Missile,
        UAV,
        GroundVehicle,
        Ship
    };

    Tacview();
    ~Tacview();

    uint32_t Subscribe(
        const double* llh,
        const double* euler,
        PlatformType type,
        const std::string& name = "");

    void Step(double simTimeSeconds);

private:

    struct Entity
    {
        uint32_t id;

        const double* llh;
        const double* euler;

        PlatformType type;
        std::string name;

        bool firstTransmission;
    };

    bool Send(const std::string& text);

    bool SendHeader();

    static const char* ToTacviewType(PlatformType type);

private:

    bool _initialized = false;
    bool _socket_initialized = false;

    SOCKET _socket = INVALID_SOCKET;

    std::vector<Entity> _entities;
};