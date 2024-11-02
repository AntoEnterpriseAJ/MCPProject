#include "Player.h"
#include "Bullet.h"

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


void Player::movePlayer()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_sprite.move(0, -1);
        dir = Direction::UP;
        m_sprite.setRotation(0.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_sprite.move(0, 1);
        dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_sprite.move(-1, 0);
        dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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


void Player::updateBullets()
{
    for (auto& bullet : bullets)
    {
        bullet.update();
    }
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& bullet) {
        return !bullet.getIsActive();
        }), bullets.end());
}

std::vector<Bullet>& Player::getBullets()
{
    return bullets;
}
