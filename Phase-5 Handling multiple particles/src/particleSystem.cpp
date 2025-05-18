#include "particleSystem.hpp"

const sf::Vector2f GRAVITY_ACCELERATION = {0.0f, 273.0f};

ParticleSystem::ParticleSystem(
    size_t totalParticlesToSpawn,
    float spawnIntervalSeconds,
    sf::Vector2f spawnPosition,
    const sf::RenderTarget &target)
    : m_totalParticlesToSpawn(totalParticlesToSpawn),
      m_spawnInterval(spawnIntervalSeconds),
      m_spawnPosition(spawnPosition),
      m_renderTargetRef(target)
{
    std::random_device rd;
    m_rng.seed(rd());

    if (m_totalParticlesToSpawn > 0)
    {
        m_particles.reserve(m_totalParticlesToSpawn);
    }
}

void ParticleSystem::update(float deltaTime)
{
    trySpawnParticles(deltaTime);

    for (Particle &p : m_particles)
    {
        p.update(deltaTime);
    }
}

void ParticleSystem::draw(sf::RenderTarget &target) const
{
    for (const Particle &p : m_particles)
    {
        p.draw(target);
    }
}

void ParticleSystem::trySpawnParticles(float deltaTime)
{
    if (m_spawnedParticlesCount >= m_totalParticlesToSpawn)
    {
        return;
    }

    m_spawnTimer += deltaTime;
    if (m_spawnTimer >= m_spawnInterval)
    {
        spawnParticle();
        m_spawnTimer -= m_spawnInterval; // Subtract instead of reset to compensate overshoot
    }
}

void ParticleSystem::spawnParticle()
{
    if (m_spawnedParticlesCount >= m_totalParticlesToSpawn)
    {
        return;
    }

    float newRadius = 10.0f + getRandomFloat(0.f, 10.f);
    sf::Color newColor = getRandomColor();
    sf::Vector2f initialVelocity = {182.f, 136.5f};

    m_particles.emplace_back(
        m_spawnPosition,
        initialVelocity,
        GRAVITY_ACCELERATION,
        newRadius,
        newColor,
        m_renderTargetRef);

    ++m_spawnedParticlesCount;
}

float ParticleSystem::getRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> dist(min, max);
    return dist(m_rng);
}

sf::Color ParticleSystem::getRandomColor()
{
    std::uniform_int_distribution<int> dist(0, 255);
    return sf::Color(dist(m_rng), dist(m_rng), dist(m_rng));
}