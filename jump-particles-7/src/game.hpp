#ifndef GAME_HPP
#define GAME_HPP

#include "particleSystem.hpp"
#include "physicsSolver.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(std::string title, sf::Vector2u initialWindowSize, unsigned int frameRateLimit);

    void run();

private:
    sf::RenderWindow m_window;
    sf::Clock m_clock;

    ParticleSystem m_particleSystem;
    PhysicsSolver m_physicsSolver;

    void handleEvents();
    void update(float deltaTime);
    void render();

    void handleWindowClose();
    void handleWindowResize(const sf::Event::Resized &newSize);
};

#endif