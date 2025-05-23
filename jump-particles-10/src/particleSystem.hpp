#ifndef PARTICLESYSTEM_HPP
#define PARTICLESYSTEM_HPP

#include "particle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class ParticleSystem
{
public:
    ParticleSystem(
        size_t totalParticlesToSpawn,
        float spawnIntervalSeconds,
        sf::Vector2f spawnPosition,
        sf::Vector2f gravity,
        const sf::RenderTarget &target);

    void update(float deltaTime);
    void draw(sf::RenderTarget &target) const;

    void setSpawnPosition(const sf::Vector2f &position);
    void setGravity(const sf::Vector2f &gravity);

    std::vector<Particle> &getParticles();

    void addParticlesToSpawn(size_t count);
    void reset();
    void clear();

private:
    size_t m_totalParticlesToSpawn;
    size_t m_initialTotalParticlesToSpawn;
    size_t m_spawnedParticlesCount = 0;
    float m_spawnInterval;
    float m_spawnTimer = 0.f;
    sf::Vector2f m_gravity;
    sf::Vector2f m_initialGravity;

    std::vector<Particle> m_particles;
    const sf::RenderTarget &m_renderTargetRef;

    sf::Vector2f m_spawnPosition;
    sf::Vector2f m_initialSpawnPosition;
    std::mt19937 m_rng;

    void trySpawnParticles(float deltaTime);
    void spawnParticle();

    float getRandomFloat(float min, float max);
    sf::Color getRandomColor();
};

#endif