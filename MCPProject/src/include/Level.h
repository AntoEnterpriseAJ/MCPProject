#include <vector>
#include "Brick.h"

class Level : public sf::Drawable
{
public:
    void loadResources();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    const std::vector<Brick>& getBricks() const;

private:
    int m_levelWidth = 30;
    int m_levelHeight = 20;
    std::vector<Brick> m_levelLayout;
    sf::Texture m_brickTexture;
};