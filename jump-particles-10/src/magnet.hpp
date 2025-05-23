#ifndef MAGNET_HPP
#define MAGNET_HPP

#include "particle.hpp"
#include <SFML/Graphics.hpp>

class Magnet
{
public:
    Magnet(std::vector<Particle> &particles, const sf::RenderWindow &window);

    void update(float deltaTime);

private:
    const sf::RenderWindow &m_window;
    std::vector<Particle> &m_particles;
};

#endif