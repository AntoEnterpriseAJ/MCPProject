#include "Explosion.h"
#include <iostream>

Explosion::Explosion(sf::Vector2f position, const sf::Texture& explosionSheet)
    : m_currentFrame{ 0 }, m_frameTime{ 0.05f }
    , m_elapsedTime{ 0.0f }, m_finished{ false }
{
    m_explosionSheet.setTexture(explosionSheet);

    m_explosionSheet.setTextureRect(sf::IntRect(0, 0, 32, 32));

    m_explosionSheet.setOrigin(16.0f, 16.0f);
    m_explosionSheet.setPosition(position);
}

void Explosion::update(float deltaTime) 
{
    m_elapsedTime += deltaTime;
    if (m_elapsedTime >= m_frameTime)
    {
        if (m_currentFrame < 16)
        {
            updateExplosionFrame();
        }
        else
        {
            m_finished = true;

            sf::IntRect finishedFrame = sf::IntRect(0, 0, 0, 0);
            m_explosionSheet.setTextureRect(finishedFrame);
        }


        m_elapsedTime = 0.0f;
        m_currentFrame++;
    }
}

void Explosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_explosionSheet, states);
}

bool Explosion::hasFinished() const 
{
    return m_finished;
}

void Explosion::updateExplosionFrame()
{
    int row = m_currentFrame / 4;
    int col = m_currentFrame % 4;

    sf::IntRect currentFrame = sf::IntRect(col * 32, row * 32, 32, 32);
    m_explosionSheet.setTextureRect(currentFrame);
}
