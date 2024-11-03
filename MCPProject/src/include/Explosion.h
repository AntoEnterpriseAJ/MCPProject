#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Explosion {
public:
    Explosion(float x, float y, const std::vector<sf::Texture>& textures);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool hasFinished() const;

private:
    std::vector<sf::Texture> frames;
    sf::Sprite sprite;
    int currentFrame;
    float frameTime;  // Timpul pentru fiecare cadru
    float elapsedTime;
    bool finished;
};