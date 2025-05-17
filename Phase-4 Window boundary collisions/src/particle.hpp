#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(sf::Vector2f position, sf::Vector2f initialVelocity, sf::Vector2f accelleration, float radius, sf::Color color);

    void update(float deltaTime);
    void draw(sf::RenderTarget &target) const;

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    bool m_isGrounded = false;

    float m_radius;
    sf::CircleShape m_shape;

    void handleBoundaryCollisions();
};

#endif