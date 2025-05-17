#include "particle.hpp"
#include "game.hpp"

const float RESTITUTION = 0.8f;        // Coefficient of restitution for bounciness (0 = no bounce, 1 = perfect bounce)
const float GROUND_FRICTION = 0.9f;    // Coefficient of friction (1 = no friction, 0 = full friction)
const float VELOCITY_THRESHOLD = 0.1f; // Threshold for stopping the particle

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f accelleration, float radius, sf::Color color)
    : m_position(position),
      m_velocity(velocity),
      m_acceleration(accelleration),
      m_radius(radius)
{
    m_shape.setRadius(radius);
    m_shape.setOrigin({radius, radius});
    m_shape.setPosition(position);
    m_shape.setFillColor(color);
}

void Particle::update(float deltaTime)
{
    m_velocity += m_acceleration * deltaTime;
    m_position += m_velocity * deltaTime;

    m_shape.setPosition(m_position);

    handleBoundaryCollisions();
}

void Particle::draw(sf::RenderTarget &target) const
{
    target.draw(m_shape);
}

void Particle::handleBoundaryCollisions()
{
    const sf::Vector2u &targetSize = Game::getWindow().getSize();

    // Left and right boundaries
    if (m_position.x - m_radius < 0.f)
    {
        m_position.x = m_radius;
        m_velocity.x *= -RESTITUTION;
    }
    else if (m_position.x + m_radius > targetSize.x)
    {
        m_position.x = targetSize.x - m_radius;
        m_velocity.x *= -RESTITUTION;
    }

    // Top and bottom boundaries
    if (m_position.y - m_radius < 0.f)
    {
        m_position.y = m_radius;
        m_velocity.y *= -RESTITUTION;
    }
    else if (m_position.y + m_radius > targetSize.y)
    {
        m_position.y = targetSize.y - m_radius;
        m_velocity.y *= -RESTITUTION;

        // Stop the particle if its vertical velocity is below the threshold
        if (std::abs(m_velocity.y) < VELOCITY_THRESHOLD)
        {
            m_velocity.y = 0.f;
            m_isGrounded = true;
        }
        else
        {
            m_isGrounded = false;
        }

        // If sliding on the ground, slow down the horizontal velocity
        if (m_isGrounded)
        {
            m_velocity.x *= GROUND_FRICTION;

            if (std::abs(m_velocity.x) < VELOCITY_THRESHOLD)
            {
                m_velocity.x = 0.f;
            }
        }
    }
}