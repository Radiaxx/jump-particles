# Jump Particles - 2D Particle Simulator

## Phase 9: UI Options and Controls

Adds user control over the simulation by adding more UI buttons for various options, including manipulating gravity and adding more particles on demand.

**Key Implementations in this Phase:**

*   **`Game` Class (`game.hpp`, `game.cpp`):**
    *   Added multiple new `Button` instances for simulation controls (e.g., "Positive Gravity", "Disable Gravity", "Negative Gravity", "+10 Particles", "+100 Particles").
*   **`ParticleSystem` Class (`particleSystem.hpp`, `particleSystem.cpp`):**
    *   Adjusted the class to support new buttons functionalities.
*   **`Particle` Class (`particle.cpp`):**
    *   Adjusted the class to support new buttons functionalities.


**Result at the end of phase 9:**

Executing the program will now:
1.  Display the particle simulation with the initial "Reset" and "Clear" buttons.
2.  Additional UI buttons will be visible with options like:
    *   Changing the direction of gravity (positive, negative, disabled).
    *   Altering the spawn location for particles when gravity changes (e.g., spawn from bottom for negative gravity).
    *   Adding a specific number of new particles to the spawn queue (e.g., +10, +100).