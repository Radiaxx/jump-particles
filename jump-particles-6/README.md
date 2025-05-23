# Jump Particles - 2D Particle Simulator

## Phase 6: Implementing particle-particle collisions

![](result.gif)

**Key implementations in this phase:**

*   **New `PhysicsSolver` Class (`physicsSolver.hpp`, `physicsSolver.cpp`):**
    *   Manages inter-particle collision detection and response.
    *   `solvePenetration()`: Separates overlapping particles by adjusting their positions along the collision normal.
    *   `solveCollision()`: Calculates and applies new velocities to colliding particles based on 2D elastic collision formulas and approximates restitution to let stacking particles to rest.
*   **`Particle` Class  (`particle.hpp`, `particle.cpp`):**
    *   Added getter and setter methods.
    *   Conditional application of acceleration and position update based on `m_isGrounded` state.
*   **`Game` Class (`game.hpp`, `game.cpp`):**
    *   Instantiates `PhysicsSolver`.
    *   `update` Implements physics sub-stepping. The main `deltaTime` is divided into smaller `subStepDeltaTime` intervals, and both `ParticleSystem::update()` and `PhysicsSolver::update()` are called multiple times per frame using these smaller time steps for a more accurate simulation.

**Encountered issues:**

After implementing the collision resolution particles were very jittery, this issue has been solved by adding substeps to the physics calculation to get a more accurate calculation within a single frame.

**Result at the end of phase 6:**

Executing the program will now:
1.  Spawn multiple particles as in Phase 5.
2.  Particles will now detect collisions with each other.
3.  Upon collision, particles will bounce off one another, with the direction and magnitude of their new velocities determined by the collision physics.
4.  Overlapping particles will be pushed apart by the penetration solving logic.

**Resources:**
- https://www.youtube.com/watch?v=dJNFPv9Mj-Y
- https://youtu.be/XL8B5nzNEOc?si=B2BgENgxFCLmppCC&t=458
- https://www.vobarian.com/collisions/2dcollisions2.pdf
- https://en.wikipedia.org/wiki/Elastic_collision