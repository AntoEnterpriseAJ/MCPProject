#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Bullet.h"
#include "Level.h"
#include "Explosion.h"
#include "Game.h"

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

    Game game;

    game.render();

    return 0;
}
  