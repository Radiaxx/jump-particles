#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle(sf::Vector2f position, sf::Vector2f initialVelocity, sf::Vector2f accelleration, float mass, float radius, sf::Color color, const sf::RenderTarget &target);

    void update(float deltaTime);
    void draw(sf::RenderTarget &target) const;

    void setPosition(const sf::Vector2f &position);
    void setVelocity(const sf::Vector2f &velocity);

    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    float getMass() const;
    float getRadius() const;

    sf::CircleShape &getShape();

private:
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    float m_mass;
    float m_radius;
    bool m_isGrounded = false;

    sf::CircleShape m_shape;
    const sf::RenderTarget &m_target;

    void handleBoundaryCollisions();
};

#endif