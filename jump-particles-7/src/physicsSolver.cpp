#include "physicsSolver.hpp"

const float DISTANCE_THRESHOLD = 0.1f;         // Minimum distance to consider particles as colliding
const float RESTITUTION_APPROXIMATION = 0.95f; // Approximation for the coefficient of restitution

PhysicsSolver::PhysicsSolver(std::vector<Particle> &particles)
    : m_particles(particles)
{
}

void PhysicsSolver::update(float deltaTime)
{
    for (size_t i = 0; i < m_particles.size(); ++i)
    {
        // Start j from i + 1 to avoid self-collision and duplicate pairs
        for (size_t j = i + 1; j < m_particles.size(); ++j)
        {
            Particle &p1 = m_particles[i];
            Particle &p2 = m_particles[j];

            sf::Vector2f normal = p2.getPosition() - p1.getPosition();
            float magnitudeSq = normal.lengthSquared();
            float combinedRadii = p1.getRadius() + p2.getRadius();
            float combinedRadiiSquared = combinedRadii * combinedRadii;

            // Colliding (and not exactly at the same spot)
            if (magnitudeSq < combinedRadiiSquared && magnitudeSq > DISTANCE_THRESHOLD)
            {
                float magnitude = normal.length();
                sf::Vector2f collisionNormal = normal.normalized();
                float penetrationDepth = combinedRadii - magnitude;

                solvePenetration(p1, p2, collisionNormal, penetrationDepth);
                solveCollision(p1, p2, collisionNormal);
            }
        }
    }
}

void PhysicsSolver::solvePenetration(Particle &p1, Particle &p2, const sf::Vector2f &collisionNormal, float penetrationDepth)
{
    sf::Vector2f correctionVector = collisionNormal * penetrationDepth;

    // Move particles apart along the collision normal to resolve overlap.
    // Each particle moves half the penetration depth.
    sf::Vector2f p1NewPosition = p1.getPosition() - correctionVector * 0.5f;
    sf::Vector2f p2NewPosition = p2.getPosition() + correctionVector * 0.5f;

    p1.setPosition(p1NewPosition);
    p2.setPosition(p2NewPosition);

    p1.getShape().setPosition(p1NewPosition);
    p2.getShape().setPosition(p2NewPosition);
}

void PhysicsSolver::solveCollision(Particle &p1, Particle &p2, const sf::Vector2f &collisionNormal)
{
    sf::Vector2f v1 = p1.getVelocity();
    sf::Vector2f v2 = p2.getVelocity();
    sf::Vector2f x1 = p1.getPosition();
    sf::Vector2f x2 = p2.getPosition();
    float m1 = p1.getMass();
    float m2 = p2.getMass();

    // Vector from p2 to p1
    sf::Vector2f positionDiff12 = x1 - x2;
    float distSquared12 = positionDiff12.lengthSquared();

    // For v'1
    sf::Vector2f relVel12 = v1 - v2;
    float dotProduct1 = relVel12.dot(positionDiff12);
    float massFactor1 = (2.0f * m2 / (m1 + m2));
    float scalarFactor1 = massFactor1 * (dotProduct1 / distSquared12);
    sf::Vector2f v1Prime = v1 - scalarFactor1 * positionDiff12 * RESTITUTION_APPROXIMATION;

    // For v'2
    // Note: (x2 - x1) = -posDiff12
    //       (v2 - v1) = -relVel12
    //       dot(v2 - v1, x2 - x1) = dot(-relVel12, -posDiff12) = dot(relVel12, posDiff12) = dotProduct1
    //       ||x2 - x1||^2 = distSquared12
    // So the dot product and distance squared terms are the same.
    float massFactor2 = (2.0f * m1 / (m1 + m2));
    float scalarFactor2 = massFactor2 * (dotProduct1 / distSquared12);

    // The direction vector is (x2 - x1) which is -posDiff12x
    sf::Vector2f v2Prime = v2 - scalarFactor2 * (-positionDiff12) * RESTITUTION_APPROXIMATION;

    p1.setVelocity(v1Prime);
    p2.setVelocity(v2Prime);
}