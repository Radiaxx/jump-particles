#include "game.hpp"
#include <SFML/Graphics.hpp>

const size_t PARTICLE_COUNT = 100;
const float PARTICLE_SPAWN_INTERVAL = 0.15f; // seconds
const sf::Vector2f PARTICLE_SPAWN_POSITION = {39.f, 30.f};

const size_t PHYSICS_SUBSTEPS = 16;

Game::Game(std::string title, sf::Vector2u initialWindowSize, unsigned int frameRateLimit)
    : m_window(sf::VideoMode(initialWindowSize), title),
      m_particleSystem(
          PARTICLE_COUNT,
          PARTICLE_SPAWN_INTERVAL,
          sf::Vector2f(PARTICLE_SPAWN_POSITION),
          m_window),
      m_physicsSolver(m_particleSystem.getParticles())
{
    m_window.setTitle(title);
    m_window.setFramerateLimit(frameRateLimit);
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
    const float subStepDeltaTime = deltaTime / PHYSICS_SUBSTEPS;

    for (int i = 0; i < PHYSICS_SUBSTEPS; ++i)
    {
        m_particleSystem.update(subStepDeltaTime);
        m_physicsSolver.update(subStepDeltaTime);
    }
}

void Game::render()
{
    m_window.clear(sf::Color::Black);

    m_particleSystem.draw(m_window);

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