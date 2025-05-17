#ifndef GAME_HPP
#define GAME_HPP

#include "particle.hpp"
#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    void run();

private:
    static const std::string WINDOW_TITLE;
    static const sf::Vector2u INITIAL_WINDOW_SIZE;
    static const unsigned int FRAME_RATE_LIMIT;

    sf::RenderWindow m_window;
    sf::Clock m_clock;
    Particle m_particle;

    void handleEvents();
    void update(float deltaTime);
    void render();

    void handleWindowClose();
    void handleWindowResize(const sf::Event::Resized &newSize);
};

#endif