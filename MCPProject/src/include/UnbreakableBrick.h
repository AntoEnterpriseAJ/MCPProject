#pragma once
#include "Brick.h"

class UnbreakableBrick : public Brick {
public:
    /**
     * Constructor pentru UnbreakableBrick.
     *
     * @param pos - poziția cărămizii în joc.
     * @param texture - textura asociată cărămizii.
     * @param size - dimensiunea cărămizii.
     */
    UnbreakableBrick(sf::Vector2f pos, const sf::Texture& texture, sf::Vector2f size = sf::Vector2f(32.0f, 32.0f));

    /**
     * Suprascrierea metodei hit. Cărămida indestructibilă nu poate fi distrusă.
     */
    void hit() override;

    /**
     * Verifică dacă este distrusă (mereu returnează false).
     *
     * @return false - cărămida este indestructibilă.
     */
    bool isDestroyed() const override;
};