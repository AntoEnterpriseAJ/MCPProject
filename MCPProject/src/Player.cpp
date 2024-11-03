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
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        dir = Direction::UP;
        m_sprite.setRotation(0.0f);
        if (canMove(Direction::UP, bricks) && playerBounds.top > 0)
        {
            m_sprite.move(0, -1);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);
        if (canMove(Direction::DOWN, bricks) && playerBounds.top + playerBounds.height < 600)
        {
            m_sprite.move(0, 1);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);
        if (canMove(Direction::LEFT, bricks) && playerBounds.left > 0)
        {
            m_sprite.move(-1, 0);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        dir = Direction::RIGHT;
        m_sprite.setRotation(90.0f);
        if (canMove(Direction::RIGHT, bricks) && playerBounds.left + playerBounds.width < 900)
        {
            m_sprite.move(1, 0);
        }
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