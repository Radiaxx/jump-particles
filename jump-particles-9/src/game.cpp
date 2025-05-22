#include "game.hpp"
#include <SFML/Graphics.hpp>

const size_t PARTICLE_COUNT = 100;
const float PARTICLE_SPAWN_INTERVAL = 0.15f; // seconds
const sf::Vector2f PARTICLE_SPAWN_POSITION = {39.f, 30.f};
const sf::Vector2f GRAVITY = {0.0f, 273.0f};
const size_t PHYSICS_SUBSTEPS = 16;

const float BUTTON_DISTANCE = 10.f;
const sf::Vector2f BUTTON_SIZE = {80.f, 24.f};
const sf::Vector2f WIDE_BUTTON_SIZE = {2 * BUTTON_SIZE.x + BUTTON_DISTANCE, BUTTON_SIZE.y};
const float BUTTON_Y = 10.f;

Game::Game(std::string title, sf::Vector2u initialWindowSize, unsigned int frameRateLimit)
    : m_window(sf::VideoMode(initialWindowSize), title),
      m_font({"./resources/tuffy.ttf"}),
      m_particleSystem(
          PARTICLE_COUNT,
          PARTICLE_SPAWN_INTERVAL,
          sf::Vector2f(PARTICLE_SPAWN_POSITION),
          GRAVITY,
          m_window),
      m_physicsSolver(m_particleSystem.getParticles()),
      m_clearButton("Clear", {initialWindowSize.x - BUTTON_SIZE.x - BUTTON_DISTANCE, BUTTON_Y}, BUTTON_SIZE, m_font, 16,
                    [this]()
                    { m_particleSystem.clear(); }),
      m_resetButton("Reset", {initialWindowSize.x - 2 * BUTTON_SIZE.x - 2 * BUTTON_DISTANCE, BUTTON_Y}, BUTTON_SIZE, m_font, 16,
                    [this]()
                    { m_particleSystem.reset(); }),
      m_positiveGravityButton("Positive Gravity", {initialWindowSize.x - WIDE_BUTTON_SIZE.x - BUTTON_DISTANCE, BUTTON_Y + BUTTON_SIZE.y + BUTTON_DISTANCE}, WIDE_BUTTON_SIZE, m_font, 16,
                              [this]()
                              {
                                  m_particleSystem.setSpawnPosition(PARTICLE_SPAWN_POSITION);
                                  m_particleSystem.setGravity(GRAVITY);
                              }),
      m_disableGravityButton("Disable Gravity", {initialWindowSize.x - WIDE_BUTTON_SIZE.x - BUTTON_DISTANCE, BUTTON_Y + 2 * BUTTON_SIZE.y + 2 * BUTTON_DISTANCE}, WIDE_BUTTON_SIZE, m_font, 16,
                             [this]()
                             { m_particleSystem.setGravity({0.0f, 0.0f}); }),
      m_negativeGravityButton("Negative Gravity", {initialWindowSize.x - WIDE_BUTTON_SIZE.x - BUTTON_DISTANCE, BUTTON_Y + 3 * BUTTON_SIZE.y + 3 * BUTTON_DISTANCE}, WIDE_BUTTON_SIZE, m_font, 16,
                              [this]()
                              {
                                  m_particleSystem.setSpawnPosition({PARTICLE_SPAWN_POSITION.x, m_window.getSize().y - PARTICLE_SPAWN_POSITION.y});
                                  m_particleSystem.setGravity(-GRAVITY);
                              }),
      m_addTenParticlesButton("+10", {initialWindowSize.x - 2 * BUTTON_SIZE.x - 2 * BUTTON_DISTANCE, BUTTON_Y + 4 * BUTTON_SIZE.y + 4 * BUTTON_DISTANCE}, BUTTON_SIZE, m_font, 16,
                              [this]()
                              { m_particleSystem.addParticlesToSpawn(10); }),
      m_addOneHundredParticlesButton("+100", {initialWindowSize.x - BUTTON_SIZE.x - BUTTON_DISTANCE, BUTTON_Y + 4 * BUTTON_SIZE.y + 4 * BUTTON_DISTANCE}, BUTTON_SIZE, m_font, 16,
                                     [this]()
                                     { m_particleSystem.addParticlesToSpawn(100); })

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
        { this->handleWindowResize(event); },
        [this](const sf::Event::MouseButtonPressed &event)
        {   this->m_resetButton.handleEvent(event, m_window);
            this->m_clearButton.handleEvent(event, m_window);
            this->m_positiveGravityButton.handleEvent(event, m_window);
            this->m_disableGravityButton.handleEvent(event, m_window);
            this->m_negativeGravityButton.handleEvent(event, m_window);
            this->m_addTenParticlesButton.handleEvent(event, m_window);
            this->m_addOneHundredParticlesButton.handleEvent(event, m_window); });
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
    m_resetButton.draw(m_window);
    m_clearButton.draw(m_window);
    m_positiveGravityButton.draw(m_window);
    m_disableGravityButton.draw(m_window);
    m_negativeGravityButton.draw(m_window);
    m_addTenParticlesButton.draw(m_window);
    m_addOneHundredParticlesButton.draw(m_window);

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

    sf::Vector2f newSize(static_cast<float>(resized.size.x),
                         static_cast<float>(resized.size.y));

    m_clearButton.setPosition(
        {newSize.x - BUTTON_SIZE.x - BUTTON_DISTANCE,
         BUTTON_Y});

    m_resetButton.setPosition(
        {newSize.x - 2 * BUTTON_SIZE.x - 2 * BUTTON_DISTANCE,
         BUTTON_Y});

    m_positiveGravityButton.setPosition(
        {newSize.x - WIDE_BUTTON_SIZE.x - BUTTON_DISTANCE,
         BUTTON_Y + BUTTON_SIZE.y + BUTTON_DISTANCE});

    m_disableGravityButton.setPosition(
        {newSize.x - WIDE_BUTTON_SIZE.x - BUTTON_DISTANCE,
         BUTTON_Y + 2 * BUTTON_SIZE.y + 2 * BUTTON_DISTANCE});

    m_negativeGravityButton.setPosition(
        {newSize.x - WIDE_BUTTON_SIZE.x - BUTTON_DISTANCE,
         BUTTON_Y + 3 * BUTTON_SIZE.y + 3 * BUTTON_DISTANCE});

    m_addTenParticlesButton.setPosition(
        {newSize.x - 2 * BUTTON_SIZE.x - 2 * BUTTON_DISTANCE,
         BUTTON_Y + 4 * BUTTON_SIZE.y + 4 * BUTTON_DISTANCE});

    m_addOneHundredParticlesButton.setPosition(
        {newSize.x - BUTTON_SIZE.x - BUTTON_DISTANCE,
         BUTTON_Y + 4 * BUTTON_SIZE.y + 4 * BUTTON_DISTANCE});
}