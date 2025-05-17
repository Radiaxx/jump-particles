#include "game.hpp"
#include <SFML/Graphics.hpp>

const std::string Game::WINDOW_TITLE = "Jump Particles";
const sf::Vector2u Game::INITIAL_WINDOW_SIZE = {720u, 480u};
const unsigned int Game::FRAME_RATE_LIMIT = 60u;

sf::RenderWindow Game::m_window(sf::VideoMode(INITIAL_WINDOW_SIZE), WINDOW_TITLE);

const sf::Vector2f GRAVITY_ACCELERATION = {0.f, 182.f};

Game::Game()
    : m_particle({INITIAL_WINDOW_SIZE.x / 2.0f, INITIAL_WINDOW_SIZE.y / 2.0f}, {120.f, 0.f}, GRAVITY_ACCELERATION, 20.0f, sf::Color::Green)
{
    m_window.setTitle(WINDOW_TITLE);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);
}

void Game::run()
{
    m_clock.restart();

    while (m_window.isOpen())
    {
        float deltaTime = m_clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}

void Game::handleEvents()
{
    m_window.handleEvents(
        [this](const sf::Event::Closed &)
        { this->handleWindowClose(); },
        [this](const sf::Event::Resized &event)
        { this->handleWindowResize(event); });
}

void Game::update(float deltaTime)
{
    m_particle.update(deltaTime);
}

void Game::render()
{
    m_window.clear(sf::Color::Black);

    m_particle.draw(m_window);

    m_window.display();
}

void Game::handleWindowClose()
{
    m_window.close();
}

void Game::handleWindowResize(const sf::Event::Resized &resized)
{
    sf::Vector2u windowSize(resized.size.x, resized.size.y);
    sf::FloatRect visibleArea({0.f, 0.f},
                              static_cast<sf::Vector2f>(windowSize));

    m_window.setView(sf::View(visibleArea));
}