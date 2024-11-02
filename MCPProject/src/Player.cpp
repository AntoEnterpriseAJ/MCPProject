#include "Player.h"
#include "Bullet.h"
#include "Brick.h"

Player::Player(const sf::Texture& texture, const sf::Texture& bulletTexture)
    : bulletTexture(bulletTexture)
{
    m_sprite.setTexture(texture);
    m_sprite.setPosition(400, 300);

    sf::FloatRect bounds = m_sprite.getGlobalBounds();
    m_sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(m_sprite);

    for (auto& bullet : bullets)
    {
        bullet.draw(window);
    }
}

bool Player::canMove(Direction direction, const std::vector<Brick>& bricks)
{
    sf::FloatRect nextPosition = m_sprite.getGlobalBounds();

    // Ajustăm poziția viitoare în funcție de direcție
    switch (direction)
    {
    case Direction::UP:
        nextPosition.top -= 1;
        break;
    case Direction::DOWN:
        nextPosition.top += 1;
        break;
    case Direction::LEFT:
        nextPosition.left -= 1;
        break;
    case Direction::RIGHT:
        nextPosition.left += 1;
        break;
    }

    for (const auto& brick : bricks)
    {
        if (nextPosition.intersects(brick.getBounds()))
        {
            return false;
        }
    }
    return true;
}


void Player::movePlayer(const std::vector<Brick>& bricks)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canMove(Direction::UP, bricks))
    {
        m_sprite.move(0, -1);
        dir = Direction::UP;
        m_sprite.setRotation(0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && canMove(Direction::DOWN, bricks))
    {
        m_sprite.move(0, 1);
        dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && canMove(Direction::LEFT, bricks))
    {
        m_sprite.move(-1, 0);
        dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && canMove(Direction::RIGHT, bricks))
    {
        m_sprite.move(1, 0);
        dir = Direction::RIGHT;
        m_sprite.setRotation(90.0f);
    }
}

void Player::shoot()
{
    float centerX = m_sprite.getPosition().x;
    float centerY = m_sprite.getPosition().y;

    Bullet newBullet(centerX, centerY, dir, 5, bulletTexture);
    bullets.push_back(newBullet);
}


void Player::updateBullets(const std::vector<Brick>& bricks)
{
    for (auto& bullet : bullets)
    {
        bullet.update();

        for (const auto& brick : bricks)
        {
            if (bullet.getIsActive() && bullet.getBounds().intersects(brick.getBounds()))
            {
                bullet.setInactive();
                break;
            }
        }
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& bullet) { return !bullet.getIsActive(); }), bullets.end());
}

std::vector<Bullet>& Player::getBullets()
{
    return bullets;
}