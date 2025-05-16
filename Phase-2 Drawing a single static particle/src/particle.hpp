#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(sf::Vector2f position, float radius, sf::Color color);

    void update();
    void draw(sf::RenderTarget &target) const;

private:
    sf::Vector2f m_position;
    float m_radius;
    sf::CircleShape m_shape;
};

#endif