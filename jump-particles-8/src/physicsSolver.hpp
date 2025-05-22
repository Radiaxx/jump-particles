#ifndef PHYSICSSOLVER_HPP
#define PHYSICSSOLVER_HPP

#include "particle.hpp"

class PhysicsSolver
{
public:
    PhysicsSolver(std::vector<Particle> &particles);

    void update(float deltaTime);

private:
    std::vector<Particle> &m_particles;

    void solvePenetration(Particle &p1, Particle &p2, const sf::Vector2f &collisionNormal, float penetrationDepth);
    void solveCollision(Particle &p1, Particle &p2, const sf::Vector2f &collisionNormal);
};

#endif