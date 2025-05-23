#ifndef GAME_HPP
#define GAME_HPP

#include "button.hpp"
#include "magnet.hpp"
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

    sf::Font m_font;
    Button m_resetButton;
    Button m_clearButton;
    Button m_positiveGravityButton;
    Button m_disableGravityButton;
    Button m_negativeGravityButton;
    Button m_addTenParticlesButton;
    Button m_addOneHundredParticlesButton;

    ParticleSystem m_particleSystem;
    PhysicsSolver m_physicsSolver;

    Magnet m_magnet;

    void handleEvents();
    void update(float deltaTime);
    void render();

    void handleWindowClose();
    void handleWindowResize(const sf::Event::Resized &newSize);
};

#endif