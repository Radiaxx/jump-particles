# Jump Particles - 2D Particle Simulator

## Phase 5: Handling multiple particles

![](result.gif)

The capability to simulate multiple particles simultaneously has been introduced. A new `ParticleSystem` class is implemented to manage the creation, update, and rendering of a collection of particles.

**Key implementations in this phase:**

*   **New `ParticleSystem` Class (`particleSystem.hpp`, `particleSystem.cpp`):**
    *   Manages a `std::vector<Particle>` to hold multiple particle instances.
    *   Implements timed spawning: creates a defined number of particles (`PARTICLE_COUNT`) one by one at a specified `PARTICLE_SPAWN_INTERVAL`.
    *   `update(float deltaTime)`: Iterates through all managed particles, calling their individual `update()` methods, and handles new particle spawning.
    *   `draw(sf::RenderTarget& target)`: Iterates through all managed particles, calling their `draw()` methods.
*   **`Game` Class integration (`game.hpp`, `game.cpp`):**
    *   Replaced the single `Particle` member with an instance of `ParticleSystem`.
    *   The `Game` constructor now initializes `m_particleSystem` with desired spawning parameters.
    *   `Game::update()` now calls `m_particleSystem.update()`.
    *   `Game::render()` now calls `m_particleSystem.draw()`.

**Encoutered issues:**

Some refactoring was needed in the `Game` class to better manage the new `ParticleSystem` class.

**Result at the end of phase 5:**

Executing the program will now:
1.  Particles will begin to spawn one after another at the specified `PARTICLE_SPAWN_POSITION` at intervals (`PARTICLE_SPAWN_INTERVAL`) with a total of `PARTICLE_COUNT` particles.
2.  Each spawned particle will have slightly different visual properties (e.g., radius, color).
3.  All active particles will independently move according to gravity, collide with window boundaries, bounce, and attempt to settle on the ground with friction but **without** colliding with each other.
