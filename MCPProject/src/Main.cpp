#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Bullet.h"
#include "Level.h"
#include "Explosion.h"

std::vector<sf::Texture> loadExplosionFrames(const std::string& filePath, int frameWidth, int frameHeight, int numFrames)
{
    sf::Image image;
    if (!image.loadFromFile(filePath))
    {
        std::cerr << "ERROR: Unable to load image!" << std::endl;
        return {};
    }

    std::vector<sf::Texture> textures(numFrames);
    for (int i = 0; i < numFrames; ++i)
    {
        sf::Texture texture;
        sf::IntRect rect((i % 4) * frameWidth, (i / 4) * frameHeight, frameWidth, frameHeight);
        texture.loadFromImage(image, rect);
        textures[i] = texture;
    }

    return textures;
}

int main() {
    const float baseWidth = 900.0f;
    const float baseHeight = 600.0f;

    sf::RenderWindow window(sf::VideoMode(baseWidth, baseHeight), "Player Shoot Example", sf::Style::Close);
    window.setFramerateLimit(100);

    //TODO: textures bounding boxes are slightly bigger than the actual texture (SEE res/plane.png, res/missile.png, ....)
    //      fix the bounding boxes
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("res/plane.png"))
    {
        std::cerr << "ERROR: Unable to load player texture!" << std::endl;
        return -1;
    }

    //TODO: textures bounding boxes are slightly bigger than the actual texture (SEE res/plane.png, res/missile.png, ....)
    //      fix the bounding boxes
    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("res/missile.png"))
    {
        std::cerr << "ERROR: Unable to load bullet texture!" << std::endl;
        return -1;
    }

    Player player(sf::Vector2f{ 100.0f, 80.0f }, playerTexture, sf::Vector2f{ 45.0f, 45.0f });
    Level level;
    level.loadResources();

    std::vector<Explosion> explosions;
    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                player.shoot(bulletTexture);
            }
        }

        player.movePlayer(level.getBricks());
        player.updateBullets(level.getBricks());

        window.clear();

        for (auto& bullet : player.getBullets())
        {
            window.draw(bullet);
        }

        window.draw(level);
        window.draw(player);

        window.display();



        //TODO: Move this inside a class. Game class?
        // 
        //for (auto& bullet : player.getBullets())
        //{
        //    sf::FloatRect bulletBounds = bullet.getBounds();

        //    bulletBounds.left -= 15;
        //    bulletBounds.top -= 15;
        //    bulletBounds.width += 30;
        //    bulletBounds.height += 30;

        //    for (auto& brick : level.getBricks())
        //    {
        //        if (bulletBounds.intersects(brick.getBounds()))
        //        {
        //            float explosionX = bullet.getPosition().x;
        //            float explosionY = bullet.getPosition().y;

        //            explosions.emplace_back(explosionX, explosionY, loadExplosionFrames("res/explosion.png", 32, 32, 16));
        //            bullet.setInactive();

        //            if (brick.hit())
        //            {
        //                level.getBricks().erase(std::remove(level.getBricks().begin(), level.getBricks().end(), brick), level.getBricks().end());
        //            }
        //            break;
        //        }
        //    }
        //}

        //float deltaTime = clock.restart().asSeconds();

        //for (auto& explosion : explosions)
        //{
        //    explosion.update(deltaTime);
        //}

        //explosions.erase(std::remove_if(explosions.begin(), explosions.end(),
        //    [](const Explosion& explosion) { return explosion.hasFinished(); }),
        //    explosions.end());

        //window.clear();
        //window.draw(level);
        //player.draw(window);

        //for (const auto& explosion : explosions)
        //{
        //    explosion.draw(window);
        //}
    }

    return 0;
}
