#include "graphics/ViewManager.hpp"

ViewManager::ViewManager(unsigned gameWidth, unsigned gameHeight)
    : view(sf::FloatRect(0.f, 0.f,
          static_cast<float>(gameWidth),
          static_cast<float>(gameHeight)))
{
}

void ViewManager::update(const sf::Vector2u& windowSize)
{
    float windowRatio =
        static_cast<float>(windowSize.x) / windowSize.y;
    float viewRatio =
        view.getSize().x / view.getSize().y;

    float sizeX = 1.f;
    float sizeY = 1.f;
    float posX  = 0.f;
    float posY  = 0.f;

    if (windowRatio > viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX  = (1.f - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY  = (1.f - sizeY) / 2.f;
    }

    view.setViewport({ posX, posY, sizeX, sizeY });
}

const sf::View& ViewManager::getView() const
{
    return view;
}
