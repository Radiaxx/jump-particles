# Jump Particles - 2D Particle Simulator

## Phase 10: Adding Magnet

Added "magnet" feature, allowing users to attract particles towards the mouse cursor by holding down the left mouse button.

**Key Implementations in this Phase:**

*   **`Magnet` Class (`magnet.hpp`, `magnet.cpp`):**
    *   `update(float deltaTime)`:
        *   Checks if the left mouse button is pressed.
        *   If pressed, gets the current mouse position.
        *   Iterates through particles.
        *   Calculates the vector from each particle to the mouse and the distance from the particle's edge to the mouse.
        *   If a particle is within `MAGNET_RADIUS` of the mouse :
            *   Calculates a `newVelocity` by adding a component towards the mouse (`normal.normalized() * MAGNET_STRENGTH * deltaTime`) to the particle's current velocity.

**Result at the end of phase 10:**

Executing the program will now:
1.  Display the particle simulation with all previous UI controls.
2.  When the user holds down the left mouse button, particles within a defined radius (`MAGNET_RADIUS`) of the mouse cursor will be attracted towards it.
3.  The strength of the attraction is determined by `MAGNET_STRENGTH`.
4.  Releasing the mouse button will stop the magnet effect, and particles will resume their normal physics behavior.