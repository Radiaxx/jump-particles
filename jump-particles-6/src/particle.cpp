#include "particle.hpp"

const float RESTITUTION = 0.8f;           // Coefficient of restitution for bounciness (0 = no bounce, 1 = perfect bounce)
const float GROUND_FRICTION = 0.97f;      // Coefficient of friction (1 = no friction, 0 = full friction)
const float GROUND_THRESHOLD = 0.1f;      // Threshold for considering the particle as grounded
const float VELOCITY_X_THRESHOLD = 0.1f;  // Threshold for stopping the particle
const float VELOCITY_Y_THRESHOLD = 0.01f; // Threshold for stopping the particle

Particle::Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f accelleration, float radius, sf::Color color, const sf::RenderTarget &target)
    : m_position(position),
      m_velocity(velocity),
      m_acceleration(accelleration),
      m_radius(radius),
      m_target(target)
{
    m_shape.setRadius(radius);
    m_shape.setOrigin({radius, radius});
    m_shape.setPosition(position);
    m_shape.setFillColor(color);
}

void Particle::update(float deltaTime)
{
    const sf::Vector2u &targetSize = m_target.getSize();

    if (std::abs(m_velocity.x) < VELOCITY_X_THRESHOLD)
    {
        m_velocity.x = 0.f;
    }

    if (std::abs(m_velocity.y) < VELOCITY_Y_THRESHOLD)
    {
        m_velocity.y = 0.f;
    }

    // If sliding on the ground, slow down the horizontal velocity
    if (m_isGrounded)
    {
        m_velocity.x *= GROUND_FRICTION;
    }
    else
    {
        m_velocity += m_acceleration * deltaTime;
        m_position = m_position + m_velocity * deltaTime;
    }

    handleBoundaryCollisions();

    m_shape.setPosition(m_position);
}

void Particle::draw(sf::RenderTarget &target) const
{
    target.draw(m_shape);
}

void Particle::setPosition(const sf::Vector2f &position)
{
    m_position = position;
    m_shape.setPosition(position);
}

void Particle::setVelocity(const sf::Vector2f &velocity)
{
    m_velocity = velocity;
}

sf::Vector2f Particle::getPosition() const
{
    return m_position;
}

sf::Vector2f Particle::getVelocity() const
{
    return m_velocity;
}

float Particle::getRadius() const
{
    return m_radius;
}

sf::CircleShape &Particle::getShape()
{
    return m_shape;
}

void Particle::handleBoundaryCollisions()
{
    const sf::Vector2u &targetSize = m_target.getSize();

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

        if (std::abs(m_velocity.y) < VELOCITY_Y_THRESHOLD)
        {
            m_isGrounded = true;
        }
    }
    else
    {
        m_isGrounded = false;
    }
}