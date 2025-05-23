# Jump Particles - 2D Particle Simulator

## Phase 7: Adding Mass

![](result.gif)

Mass has been added to particles. Mass is now calculated proportionally to their size (area), and collision responses between particles take their respective masses into account.

**Key implementations in this phase:**
*   **`Particle` Class (`particle.hpp`, `particle.cpp`):**
    *   Added `m_mass` (float) member variable.
*   **`ParticleSystem` Class (`particleSystem.cpp`):**
    *   In `spawnParticle()`:
        *   Mass is now calculated for each new particle, proportional to its area (`PI * radius^2 * DENSITY`).
*   **`PhysicsSolver` Class (`physicsSolver.cpp`):**
    *   `solveCollision()`:
        *   Uses the actual `mass` of each colliding particle.
        *   Utilizes these mass values in the 2D elastic collision formulas to determine the new velocities.

**Result at the end of phase 7:**

Executing the program will now:
1.  Spawn multiple particles with varying radii and masses.
2.  Each particle will now have a mass proportional to its size (area).
3.  When particles collide with each other:
    *   The outcome of the collision will reflect their masses.
    *   Lighter particles will be more affected by collisions with heavier particles.
    *   Heavier particles will be less affected by collisions with lighter particles.