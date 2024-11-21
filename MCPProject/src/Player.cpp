#include "Player.h"
#include "Bullet.h"
#include "Brick.h"
#include "Game.h"
#include "Bush.h"
#include <variant>
#include <vector>
#include <iostream>

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ 100 }, m_direction{Direction::Left} //Health currently unused
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_cooldownDuration = 0.5f;
}

void Player::update(float deltaTime)
{
    if (m_cooldownDuration > 0)
    {
        m_cooldownDuration -= deltaTime;
        if (m_cooldownDuration < 0) m_cooldownDuration = 0; \
    }
}

bool Player::canShoot() const
{
    return m_cooldownDuration <= 0; 
}

void Player::restartCooldown()
{
    m_cooldownDuration = kCooldownTime;
}


bool Player::canMove(const std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& levelLayout, float deltaTime)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    sf::Vector2f movement = { 0, 0 };

    switch (m_direction)
    {
    case Direction::Up:
        movement.y = -kPlayerSpeed * deltaTime;
        break;
    case Direction::Down:
        movement.y = kPlayerSpeed * deltaTime;
        break;
    case Direction::Left:
        movement.x = -kPlayerSpeed * deltaTime;
        break;
    case Direction::Right:
        movement.x = kPlayerSpeed * deltaTime;
        break;
    }

    playerBounds.left += movement.x;
    playerBounds.top += movement.y;

    for (const auto& obj : levelLayout)
    {
        if (auto brick = std::get_if<Brick>(&obj))
        {
            if (playerBounds.intersects(brick->getBounds()))
            {
                std::cout << "Collides with brick\n";
                return false;
            }
        }
        
    }

    for (const auto& obj : levelLayout)
    {
        if (auto unbreakableBrick = std::get_if<UnbreakableBrick>(&obj))
        {
            if (playerBounds.intersects(unbreakableBrick->getBounds()))
            {
                std::cout << "Collides with unbreakable brick\n";
                return false;
            }
        }

    }

    return true;
}

void Player::movePlayer(const std::vector<std::variant<Brick, Bush, UnbreakableBrick>>& levelLayout, float deltaTime)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_direction = Direction::Up;
        m_sprite.setRotation(0.0f);

        if (canMove(levelLayout, deltaTime) && playerBounds.top > 0)
        {
            m_sprite.move(0, -kPlayerSpeed * deltaTime);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_direction = Direction::Down;
        m_sprite.setRotation(180.0f);

        if (canMove(levelLayout, deltaTime) && playerBounds.top + playerBounds.height < Game::getWindowHeight())
        {
            m_sprite.move(0, kPlayerSpeed * deltaTime);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_direction = Direction::Left;
        m_sprite.setRotation(270.0f);

        if (canMove(levelLayout, deltaTime) && playerBounds.left > 0)
        {
            m_sprite.move(-kPlayerSpeed * deltaTime, 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_direction = Direction::Right;
        m_sprite.setRotation(90.0f);

        if (canMove(levelLayout, deltaTime) && playerBounds.left + playerBounds.width < Game::getWindowWidth())
        {
            m_sprite.move(kPlayerSpeed * deltaTime, 0);
        }
    }
}
Direction Player::getDirection() const
{
    return m_direction;
}