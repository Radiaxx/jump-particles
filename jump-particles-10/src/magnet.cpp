#include "magnet.hpp"
#include <iostream>

const float MAGNET_STRENGTH = 1250.f;
const float MAGNET_RADIUS = 150.f;

Magnet::Magnet(std::vector<Particle> &particles, const sf::RenderWindow &window) : m_particles(particles), m_window(window)
{
}

void Magnet::update(float deltaTime)
{
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        return;
    }

    const sf::Vector2f mousePosView = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));

    for (Particle &particle : m_particles)
    {
        const sf::Vector2f normal = mousePosView - particle.getPosition();
        const float distance = normal.length() - particle.getRadius();

        if (distance > MAGNET_RADIUS)
        {
            continue;
        }

        const sf::Vector2f newVelocity = particle.getVelocity() + normal.normalized() * MAGNET_STRENGTH * deltaTime;
        particle.setVelocity(newVelocity);
    }
}