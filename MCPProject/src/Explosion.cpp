#include "Explosion.h"

Explosion::Explosion(float x, float y, const std::vector<sf::Texture>& textures)
    : frames(textures), currentFrame(0), frameTime(0.1f), elapsedTime(0.0f), finished(false)
{
    sprite.setTexture(frames[currentFrame]);
    sprite.setPosition(x, y);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
}

void Explosion::update(float deltaTime) 
{
    elapsedTime += deltaTime;
    if (elapsedTime >= frameTime)
    {
        elapsedTime = 0.0f;
        currentFrame++;
        if (currentFrame < frames.size()) 
        {
            sprite.setTexture(frames[currentFrame]);
        }
        else 
        {
            finished = true;
        }
    }
}

void Explosion::draw(sf::RenderWindow& window) const 
{
    if (!finished) 
    {
        window.draw(sprite);
    }
}

bool Explosion::hasFinished() const 
{
    return finished;
}

sf::Vector2f Explosion::getPosition() const
{
    return sprite.getPosition();
}
