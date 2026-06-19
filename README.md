# Generic 6DOF -  ProjectB  🚀🛩️🚁

> A configurable, generic 6-DOF simulation framework for students and engineers.

> Written completely in C++

> Alpha version! Bugs are expected.

**Version:** Alpha &nbsp;|&nbsp; **Release Date:** 20/06/2026 &nbsp;|&nbsp; **License:** MIT

---

## Overview

ProjectB provides you with an infrastructure for running 6-DOF (six degrees of freedom) simulations, so you can focus on modelling your platform rather than building numerical integrators or kinematic pipelines from scratch.

It is aimed at students, engineers, and researchers who want to test their own aerodynamics, propulsion, and mass-inertia models without implementing the surrounding simulation engine themselves.

> **Looking for flight visualization?** Open-source tools like [JSBSim](https://github.com/JSBSim-Team/jsbsim) may suit you better. ProjectB does support sending live telemetry to [Tacview](https://www.tacview.net/), but its primary focus is recording data for offline analysis. <br>

> **Designing a rocket?** [OpenRocket](https://openrocket.info/) might be the tool you need. Check them out ;) <br>

> **Quick Disclaimer** <br>
> Many of the implemented models have not yet been thoroughly tested and may contain bugs. Please treat all simulation results with caution.

---

## Getting Started

### Dependencies

- [pugixml](https://pugixml.org/) — XML config parsing (included in the project files already)
- Windows SDK (Winsock2) — required for Tacview live telemetry (So this project is Windows only, for now)

### Configuration

All runtime options are read from `Configs/config.xml`. Configurable items include:

- Earth model: `Flat` or `Ellipsoid`
- Earth rotation: on/off (Ellipsoid kinematics only)
- Gravity model: `Constant`, `ConstantEarthCentric`, `NewtonianEarthCentric`, etc.
- Atmosphere model: `ISA1976`, `OffsetISA1976` (with custom sea-level T and P), or `None`
- Integrator: `Euler` or `RK4`, with configurable `DT`
- Tacview: on/off
- Real-time pacing: on/off

> **Note:** The config file path and the output CSV path are currently hard-coded in `Initializer.cpp` and `main.cpp`. The recorded file will be created as "out.csv" in the directory of the `.sln` file.

### Adding Your Own Model

To plug-in your own platform, implement the relevant subsystem models and hand them over to the simulation infrastructure. The models you will need to implement are:

- **Aerodynamics**
- **Mass & Inertia**
- **Propulsion**
- **Actuators**
- **Normal-Force**

You will also need to configure the **IMU placement** — the position and orientation of the IMU relative to the body frame. This is used to apply the lever-arm correction when computing the sensed accelerations published by the `SixDOF` class.


You may, of course, use existing models, so you do not have to implement your own from the ground up. This is especially true for models like the Normal-Force model.

#### Inheritance requirements

Every model class **must** inherit from two interface classes:

1. **The subsystem interface** for the model you are creating — e.g. `IAerodynamics`, `IPropulsion`, etc.
2. **Either `IStatefulModel` or `IStatelessModel`** — depending on whether your model owns internal states (e.g. actuator dynamics) or is purely algebraic.

See the UML diagram in `Docs/` for a full picture of how these interfaces relate.

#### Examples

| Type | Example class | Project |
|------|--------------|---------|
| Model **with** states | `SimpleActuators`, `SimpleMassInertia` | `SimplePlatform` |
| Model **without** states | `SimplePropulsion`, `SimpleAerodynamics` | `SimplePlatform` |

---
## What happens if you run the code "as-is"?
If you compile and run the code "as-is" - you are simulating a 7-Kg rocket with fixed input-commands to the actuators (that are intended to pitch up the rocket). The rocket starts on the "ground" at 1000[m] elevation, at 70 degrees pitch up, facing north. The engine ignites at t=20[sec] and burns until t=40[sec]. The force of the rocket engine is modeled as constant 100[N] of thrust. The aerodynamic constants are made-up numbers. <br>
If everything runs correctly - you will see in the log file how the rocket sits on the ground until t=20[sec], then it accelerates and climbs to around 1763.3[m], and then it falls and hits the ground (h=0[m]) at t=83.16[sec].

## Future work
- Adding more complex and accurate gravity and magnetic-field models.
- Optimizing a few libraries, like NavigationUtils and the StandartAtmophere.
- Redesigning the way the Logger class works - such that every model will be able to log whatever it wants from within itself.
- Generally cleaning up the code in some places.
- Changing the way the SimpleNormal model works, as now the static variables can create problems if you try using the same model across many platforms.
- Adding wind models to the `Environment` class.
- Switching to smart pointers at the platform level for cleaner memory ownership, while keeping raw pointers in `SixDOF` for performance.
---

## License

This project is licensed under the [MIT License](LICENSE).