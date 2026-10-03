#pragma once

namespace Constants {
    // Numerical
    static constexpr double D_EPS = 1e-8;

    // Mathematical
    static constexpr double PI = 3.14159265358979323846;
    static constexpr double RAD2DEG = 180.0 / PI;
    static constexpr double DEG2RAD = PI / 180.0;

    // Navigation-related constants
    struct WGS84
    {
        static constexpr double a = 6378137.0; // Earth's radius
        static constexpr double f = 1.0 / 298.257223563; // Flattening ratio of the Earth 
        static constexpr double e2 = f * (2.0 - f); // Eccentricity of the Earth (squared)
    };
}

