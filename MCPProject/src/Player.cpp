#include "Player.h"
#include "Bullet.h"
#include "Brick.h"

#include <iostream> // Only used for the cerr below, TODO: delete it

Player::Player(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size)
    : GameObject{ pos, texture, size }, m_health{ 100 }, m_dir{Direction::LEFT} //Health currently unused
{
    //sf::FloatRect bounds = m_sprite.getGlobalBounds();
    // We're setting the origin in local space, not in world space
    // this means we don't need those extra offsets to center the origin of the sprite
    //m_sprite.setOrigin(bounds.width / 2 + Brick::getSize() / 2, bounds.height / 2 + Brick::getSize() / 2);

    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

bool Player::canMove(Direction direction, const std::vector<Brick>& bricks)
{
    sf::FloatRect nextPosition = m_sprite.getGlobalBounds();

    // TODO: fix
    // We move by the set velocity in GameObject, not by 1
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
        m_dir = Direction::UP;
        m_sprite.setRotation(0.0f);
        if (canMove(Direction::UP, bricks) && playerBounds.top > 0)
        {
            m_sprite.move(0, -1);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        m_dir = Direction::DOWN;
        m_sprite.setRotation(180.0f);
        if (canMove(Direction::DOWN, bricks) && playerBounds.top + playerBounds.height < 900)
        {
            m_sprite.move(0, 1);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_dir = Direction::LEFT;
        m_sprite.setRotation(270.0f);
        if (canMove(Direction::LEFT, bricks) && playerBounds.left > 0)
        {
            m_sprite.move(-1, 0);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_dir = Direction::RIGHT;
        m_sprite.setRotation(90.0f);
        if (canMove(Direction::RIGHT, bricks) && playerBounds.left + playerBounds.width < 1200)
        {
            m_sprite.move(1, 0);
        }
    }
}

// TODO: think about how we're gonna handle the texture loading
//       textures should load ONLY ONCE per game, not every time we shoot
//       ResourceManager singleton class?
void Player::shoot(const sf::Texture& bulletTexture)
{
    float centerX = m_sprite.getPosition().x;
    float centerY = m_sprite.getPosition().y;

    m_bullets.push_back(Bullet(sf::Vector2f{ centerX, centerY }, bulletTexture, m_dir)); //TODO: emplace back
}

//TODO: should the player handle it's own bullets? Maybe a bullet manager in the Game class? 
void Player::updateBullets(std::vector<Brick>& bricks)
{
    for (auto& bullet : m_bullets)  
    {
        bullet.update();

        for (auto& brick : bricks)
        {
            //TODO: maybe make it so GameObject has a getBounds() function
            //      so we don't do getSprite().getGlobalBounds() all the time
            if (bullet.getState() == Bullet::State::Active && bullet.getSprite().getGlobalBounds().intersects(brick.getSprite().getGlobalBounds()))
            {
                bullet.setState(Bullet::State::Inactive);

                if (brick.hit())
                {
                    bricks.erase(std::remove(bricks.begin(), bricks.end(), brick), bricks.end());
                }
                break;
            }
        }
    }

    // TODO: fix, slow
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
        [](const Bullet& bullet) { return bullet.getState() == Bullet::State::Inactive; }), m_bullets.end());
}

std::vector<Bullet>& Player::getBullets()
{
    return m_bullets;
}