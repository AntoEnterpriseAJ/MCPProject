#include "Player.h"
#include "Bullet.h"
#include "Brick.h"
#include "Game.h"
#include "Bush.h"
#include <variant>
#include <vector>

#include <algorithm>

#include <iostream> // Only used for the cerr below, TODO: delete it

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ 100 }, m_dir{Direction::LEFT} //Health currently unused
{
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_cooldownDuration = 2.f;
    m_canShoot = true;
}

bool Player::canMove(Direction direction, const std::vector<std::variant<Brick, Bush>>& levelLayout)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();
    sf::Vector2f movement = { 0, 0 };

    switch (direction)
    {
    case Direction::UP:
        movement.y = -kPlayerSpeed;
        break;
    case Direction::DOWN:
        movement.y = kPlayerSpeed;
        break;
    case Direction::LEFT:
        movement.x = -kPlayerSpeed;
        break;
    case Direction::RIGHT:
        movement.x = kPlayerSpeed;
        break;
    }

    playerBounds.left += movement.x;
    playerBounds.top += movement.y;

    for (const auto& obj : levelLayout)
    {
        if (auto* brick = std::get_if<Brick>(&obj))
        {
            if (playerBounds.intersects(brick->getBounds()))
            {
                return false;
            }
        }
        else if (auto* bush = std::get_if<Bush>(&obj))
        {
            if (playerBounds.intersects(bush->getBounds()))
            {
                //return false;
            }
        }
    }
    return true;
}


void Player::movePlayer(const std::vector<std::variant<Brick, Bush>>& levelLayout)
{
    sf::FloatRect playerBounds = m_sprite.getGlobalBounds();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        m_dir = Direction::UP;
        m_sprite.setRotation(0.0f);

        if (canMove(Direction::UP, levelLayout) && playerBounds.top > 0)
        {
            m_sprite.move(0, -kPlayerSpeed);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);

        if (canMove(Direction::DOWN, levelLayout) && playerBounds.top + playerBounds.height < Game::getWindowHeight())
        {
            m_sprite.move(0, kPlayerSpeed);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);

        if (canMove(Direction::LEFT, levelLayout) && playerBounds.left > 0)
        {
            m_sprite.move(-kPlayerSpeed, 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_dir = Direction::RIGHT;
        m_sprite.setRotation(90.0f);

        if (canMove(Direction::RIGHT, levelLayout) && playerBounds.left + playerBounds.width < Game::getWindowWidth())
        {
            m_sprite.move(kPlayerSpeed, 0);
        }
    }
}

void Player::shoot(const sf::Texture& bulletTexture)
{
    if (m_canShoot)
    {
        float centerX = m_sprite.getPosition().x;
        float centerY = m_sprite.getPosition().y;

        m_bullets.push_back(Bullet(
            sf::Vector2f{ centerX, centerY }, 
            bulletTexture, 
            m_dir
        ));

        m_canShoot = false;
        m_cooldownClock.restart();
    }
}

//TODO: should the player handle it's own bullets? Maybe a bullet manager in the Game class? 
void Player::updateBullets(std::vector<std::variant<Brick, Bush>>& levelLayout)
{
    for (Bullet& bullet : m_bullets)
    {
        bullet.update();

        for (auto& obj : levelLayout)
        {
            if (auto* brick = std::get_if<Brick>(&obj))
            {
                if (bullet.getState() == Bullet::State::Active &&
                    bullet.getSprite().getGlobalBounds().intersects(brick->getSprite().getGlobalBounds()))
                {
                    bullet.setState(Bullet::State::Inactive);

                    if (brick->hit())
                    {
                        levelLayout.erase(std::remove(levelLayout.begin(), levelLayout.end(), obj), levelLayout.end());
                    }
                }
            }
            else if (auto* bush = std::get_if<Bush>(&obj))
            {
                
            }
        }
    }

    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
        [](const Bullet& bullet) {
            return bullet.getState() == Bullet::State::Inactive;
        }), m_bullets.end());
}

std::list<Bullet>& Player::getBullets()
{
    return m_bullets;
}

void Player::updateTimer()
{
    if (!m_canShoot && m_cooldownClock.getElapsedTime().asSeconds() >= m_cooldownDuration)
    {
        m_canShoot = true;
    }
}
