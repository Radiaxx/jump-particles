#include "game.hpp"
#include <SFML/Graphics.hpp>

const std::string Game::WINDOW_TITLE = "Jump Particles";
const sf::Vector2u Game::INITIAL_WINDOW_SIZE = {720u, 480u};
const unsigned int Game::FRAME_RATE_LIMIT = 60u;

Game::Game()
    : m_window(sf::RenderWindow(sf::VideoMode(INITIAL_WINDOW_SIZE), WINDOW_TITLE))
{
    m_window.setTitle(WINDOW_TITLE);
    m_window.setFramerateLimit(FRAME_RATE_LIMIT);
}

void Game::run()
{
    while (m_window.isOpen())
    {
        handleEvents();
        update();
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

void Game::update()
{
}

void Game::render()
{
    m_window.clear(sf::Color::Black);
    m_window.display();
}

void Game::handleWindowClose()
{
    m_window.close();
}

void Game::handleWindowResize(const sf::Event::Resized &resized)
{
    sf::Vector2u ws(resized.size.x, resized.size.y);
    m_window.setSize(ws);
}