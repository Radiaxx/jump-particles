#include "particle.hpp"

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
}

void Particle::draw(sf::RenderTarget &target) const
{
    target.draw(m_shape);
}