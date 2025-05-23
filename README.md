# Jump Particles - 2D Particle Simulator

This repository contains a C++ project built with [SFML](https://www.sfml-dev.org/) to create a 2D particle simulator. The simulation features particles influenced by gravity, colliding with window boundaries and each other, and allows for user interaction through UI elements and a mouse-driven "magnet" effect.

The project is structured to demonstrate an iterative development process, with different phases (represented by the `jump-particles-X` subdirectories) building upon each other to add new features and refinements. This README provides an overview of the final implemented state (represented by the latest phase `jump-particles-10`).

## Project Overview

**"Jump Particles"** simulates the behavior of 2D circular particles within a defined window space. The core features include:

*   **Particle Physics:**
    *   **Kinematics:** Particles have position, velocity, and acceleration.
    *   **Gravity:** A configurable gravitational force affects all particles.
    *   **Boundary collisions:** Particles realistically bounce off the window edges, with a coefficient of restitution to simulate energy loss.
    *   **Ground resting & friction:** Particles can come to rest on the "ground" (bottom window boundary) and experience friction while sliding.
    *   **Particle-Particle collisions:** Circular particles detect and respond to collisions with each other. The response includes positional correction (to resolve overlap) and velocity changes based on elastic collision principles (approximating restitution).
    *   **Mass proportional to size:** Particles are assigned a mass proportional to their area (radius squared).
*   **Particle Management (`ParticleSystem`):**
    *   Manages the spawning of a configurable number of particles over time at set intervals.
    *   New particles are created with randomized properties (radius, color) and initial velocities.
    *   Provides an interface to control global simulation parameters like gravity and to manage the particle collection (e.g., `reset()`, `clear()`).
*   **User Interface (`Button` class & `Game` integration):**
    *   Clickable UI buttons allow users to interact with the simulation.
    *   **Controls include:** Resetting the simulation, clearing all particles, toggling gravity (positive, negative, disabled), and adding more particles on demand.
    *   The UI button layout is responsive to window resizing, maintaining relative positions to the window's top right corner.
*   **Interactive "Magnet" Feature (`Magnet` class):**
    *   When the user holds down the left mouse button, particles within a defined radius of the mouse cursor are attracted towards it.
*   **Physics Sub-stepping:** The main physics update loop is divided into smaller sub-steps to improve collision handling accuracy.

## Prerequisites

To build and run this project, you will need:
- **CMake** (Version 3.28 or higher recommended): A cross-platform open-source build system.
- **A C++ Compiler** (e.g., MSVC, Clang) that supports C++17 or later.
- **SFML Libraries**: The project uses SFML v3.0.1.

## Summary of Source Files (based on latest phase)

*   **`main.cpp`**: Entry point of the application, creates and runs the `Game` instance.
*   **`game.hpp` / `game.cpp`**: Orchestrates the entire simulation, including window management, event handling, UI, and the main update/render loop. Initializes and calls `ParticleSystem`, `PhysicsSolver`, and `Magnet`.
*   **`particle.hpp` / `particle.cpp`**: Defines the properties (position, velocity, acceleration, mass, radius, grounded state) and behavior (kinematic updates, boundary collisions, drawing) of a single particle.
*   **`particleSystem.hpp` / `particleSystem.cpp`**: Manages the creation, storage (`std::vector<Particle>`), timed spawning, and updates for all particles.
*   **`physicsSolver.hpp` / `physicsSolver.cpp`**: Implements the logic for detecting collisions between pairs of particles and calculating their new positions and velocities after impact.
*   **`button.hpp` / `button.cpp`**: A generic UI button component with text, size, position, and a callback function for click events.
*   **`magnet.hpp` / `magnet.cpp`**: Implements the logic to attract particles towards the mouse cursor while the left mouse button is held down.