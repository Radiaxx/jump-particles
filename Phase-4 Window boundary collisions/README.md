# Jump Particles - 2D Particle Simulator

## Phase 4: Window boundary collisions

The particle is now confined within the window boundaries, making it bounce off the edges. Logic is also introduced to allow the particle to come to rest on the "ground" (bottom boundary) and apply friction to sliding.

**Key implementations in this phase:**

*   **`Particle` Class updated (`particle.hpp`, `particle.cpp`):**
    *   New `handleBoundaryCollisions()` method:
        *   Detects and resolves collisions with all four window edges.
        *   Corrects particle position to prevent passing through boundaries.
        *   Reverses and dampens velocity (using `RESTITUTION`) upon collision for bounce.
    *   Ground interaction logic added:
        *   Sets vertical velocity to zero if below `VELOCITY_THRESHOLD` after bottom collision (`m_isGrounded` flag used).
        *   Applies `GROUND_FRICTION` to horizontal velocity when `m_isGrounded`.
        *   Stops horizontal sliding if velocity is below `VELOCITY_THRESHOLD`.
    *   `update()` now calls `handleBoundaryCollisions()`.
*   **Boundary Data:** Window dimensions made accessible to `Particle` (via static `sf::RenderWindow` in `Game`).

**Encoutered issues:**

Getting the grounded logic to work took some time. The issue was that the gravitational acceleration was pulling the particle down so quickly that, even with velocity damping, it never reached the point where it could nullify its vertical velocity.

**Result at the end of phase 4:**

Executing the program will now:
1.  Show a particle affected by gravity and initial velocity as in Phase 3.
2.  The particle will now collide and bounce off all four edges of the window, remaining contained within the viewable area.
3.  The bounces will exhibit a degree of energy loss, controlled by the `RESTITUTION` coefficient.
4.  When the particle hits the bottom boundary (ground) and its vertical motion is within a treshold, it will come to rest vertically.
5.  If the particle is sliding horizontally along the ground friction will be applied gradually slowing its horizontal movement until it stops.
6.  Resizing the window will update the collision boundaries and the particle will correctly interact with the new edges.
