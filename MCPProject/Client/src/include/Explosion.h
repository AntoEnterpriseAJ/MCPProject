#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Explosion : public sf::Drawable
{
public:
    Explosion(sf::Vector2f position, const sf::Texture& explosionSheet);

    bool hasFinished() const;
    void update(float deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void updateExplosionFrame();

private:
    sf::Sprite m_explosionSheet;

    int   m_currentFrame;
    float m_frameTime;
    float m_elapsedTime;
    bool  m_finished;
};