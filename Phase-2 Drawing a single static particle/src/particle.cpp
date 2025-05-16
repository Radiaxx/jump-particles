#include "particle.hpp"

Particle::Particle(sf::Vector2f position, float radius, sf::Color color)
    : m_position(position),
      m_radius(radius)
{
    m_shape.setRadius(radius);
    m_shape.setOrigin({radius, radius});
    m_shape.setPosition(position);
    m_shape.setFillColor(color);
}

// It will be used in later steps for movement and physics.
void Particle::update()
{
}

void Particle::draw(sf::RenderTarget &target) const
{
    target.draw(m_shape);
}