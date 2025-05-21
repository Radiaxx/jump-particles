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
        const sf::RenderTarget &target);

    void update(float deltaTime);
    void draw(sf::RenderTarget &target) const;

    std::vector<Particle> &getParticles();

private:
    size_t m_totalParticlesToSpawn;
    size_t m_spawnedParticlesCount = 0;
    float m_spawnInterval;
    float m_spawnTimer = 0.f;

    std::vector<Particle> m_particles;
    const sf::RenderTarget &m_renderTargetRef;

    sf::Vector2f m_spawnPosition;
    std::mt19937 m_rng;

    void trySpawnParticles(float deltaTime);
    void spawnParticle();

    float getRandomFloat(float min, float max);
    sf::Color getRandomColor();
};

#endif