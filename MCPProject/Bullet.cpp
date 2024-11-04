#include "Bullet.h"

Bullet::Bullet(float x, float y, Direction dir, float speed, const sf::Texture& texture)
    : speed(speed), direction(dir), isActive(true)
{
    sprite.setTexture(texture);
    sprite.setPosition(x, y);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);

    sprite.setScale(0.05f, 0.05f);

    if (dir == Direction::UP)
        sprite.setRotation(0.0f);
    else if (dir == Direction::DOWN)
        sprite.setRotation(180.0f);
    else if (dir == Direction::LEFT)
        sprite.setRotation(270.0f);
    else if (dir == Direction::RIGHT)
        sprite.setRotation(90.0f);
}

void Bullet::update()
{
    if (direction == Direction::UP)
        sprite.move(0, -speed);
    else if (direction == Direction::DOWN)
        sprite.move(0, speed);
    else if (direction == Direction::LEFT)
        sprite.move(-speed, 0);
    else if (direction == Direction::RIGHT)
        sprite.move(speed, 0);

    if (sprite.getPosition().x < 0 || sprite.getPosition().x > 900 ||
        sprite.getPosition().y < 0 || sprite.getPosition().y > 600)
    {
        isActive = false;
    }
}

void Bullet::draw(sf::RenderWindow& window) const
{
    window.draw(sprite);
}

bool Bullet::getIsActive() const
{
    return isActive;
}

sf::FloatRect Bullet::getBounds() const
{
    return sprite.getGlobalBounds();
}

sf::Vector2f Bullet::getPosition() const 
{
    return sprite.getPosition();
}

void Bullet::setInactive()
{
    isActive = false;
}