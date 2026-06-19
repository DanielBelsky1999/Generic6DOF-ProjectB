#include "Tacview.h"

Tacview::Tacview()
{
    if (!Initializer::GetValueAsBool("Tacview"))
        return;

    constexpr int port = 42674;

    WSADATA wsaData{};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        return;

    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenSocket == INVALID_SOCKET)
        return;

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(listenSocket,
        reinterpret_cast<sockaddr*>(&addr),
        sizeof(addr)) == SOCKET_ERROR)
    {
        closesocket(listenSocket);
        return;
    }

    if (listen(listenSocket, 1) == SOCKET_ERROR)
    {
        closesocket(listenSocket);
        return;
    }

    printf("Waiting for Tacview to connect...\n");

    _socket = accept(listenSocket, nullptr, nullptr);

    closesocket(listenSocket);

    if (_socket == INVALID_SOCKET)
        return;

    _socket_initialized = true;

    //
    // Host sends handshake first
    //
    {
        std::string handshake =
            "XtraLib.Stream.0\n"
            "Tacview.RealTimeTelemetry.0\n"
            "Simulator\n";

        handshake.push_back('\0');

        if (!Send(handshake))
            return;
    }

    //
    // Receive Tacview handshake
    //
    {
        char buffer[1024]{};

        int bytesReceived =
            recv(_socket, buffer, sizeof(buffer) - 1, 0);

        if (bytesReceived <= 0)
            return;

        buffer[bytesReceived] = '\0';

        // TODO:
        // Parse and validate:
        // XtraLib.Stream.0
        // Tacview.RealTimeTelemetry.0
        // Username
        // Password hash
    }

    if (!SendHeader())
        return;

    _initialized = true;
}

Tacview::~Tacview()
{
    if (_socket != INVALID_SOCKET)
    {
        closesocket(_socket);
        _socket = INVALID_SOCKET;
    }

    WSACleanup();
}

bool Tacview::Send(const std::string& text)
{
    if (!_socket_initialized)
        return false;

    int result = send(
        _socket,
        text.c_str(),
        static_cast<int>(text.size()),
        0);

    return result != SOCKET_ERROR;
}

bool Tacview::SendHeader()
{
    std::ostringstream ss;

    ss
        << "FileType=text/acmi/tacview\n"
        << "FileVersion=2.2\n"
        << "\n"
        << "0,ReferenceTime=2026-01-01T00:00:00Z\n"
        << "0,Title=My Simulation\n";

    return Send(ss.str());
}

uint32_t Tacview::Subscribe(
    const double* llh,
    const double* euler,
    PlatformType type,
    const std::string& name)
{
    Entity e;

    e.id = static_cast<uint32_t>(_entities.size() + 1);

    e.llh = llh;
    e.euler = euler;

    e.type = type;
    e.name = name;
    e.firstTransmission = true;

    _entities.push_back(e);

    return e.id;
}

const char* Tacview::ToTacviewType(PlatformType type)
{
    switch (type)
    {
    case PlatformType::Plane:
        return "Air+FixedWing";

    case PlatformType::Helicopter:
        return "Air+Rotorcraft";

    case PlatformType::Rocket:
        return "Weapon+Rocket";

    case PlatformType::Missile:
        return "Weapon+Missile";

    case PlatformType::UAV:
        return "Air+Drone";

    case PlatformType::GroundVehicle:
        return "Ground+Vehicle";

    case PlatformType::Ship:
        return "Watercraft";

    default:
        return "Misc";
    }
}

void Tacview::Step(double simTimeSeconds)
{
    if (!_initialized)
        return;

    constexpr double RAD2DEG = 57.29577951308232;

    std::ostringstream ss;

    ss << "#"
        << std::fixed
        << std::setprecision(7)
        << simTimeSeconds
        << "\n";

    for (auto& e : _entities)
    {
        if (e.firstTransmission)
        {
            ss
                << e.id
                << ",Type=" << ToTacviewType(e.type)
                << ",Name=" << e.name
                << ",Color=Red"
                << "\n";

            e.firstTransmission = false;
        }

        double latDeg = e.llh[0] * RAD2DEG;
        double lonDeg = e.llh[1] * RAD2DEG;
        double altM = e.llh[2];

        double yawDeg = e.euler[0] * RAD2DEG;
        double pitchDeg = e.euler[1] * RAD2DEG;
        double rollDeg = e.euler[2] * RAD2DEG;

        ss
            << e.id
            << ",T="
            << lonDeg << "|"
            << latDeg << "|"
            << altM << "|"
            << rollDeg << "|"
            << pitchDeg << "|"
            << yawDeg
            << "\n";
    }

    Send(ss.str());
}