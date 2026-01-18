#include "ViewManager.hpp"

static sf::View makeLetterboxView(
    const sf::View& baseView,
    unsigned winW,
    unsigned winH)
{
    float windowRatio = static_cast<float>(winW) / winH;
    float viewRatio   = baseView.getSize().x / baseView.getSize().y;

    float sizeX = 1.f, sizeY = 1.f;
    float posX  = 0.f, posY  = 0.f;

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

    sf::View result = baseView;
    result.setViewport({ posX, posY, sizeX, sizeY });
    return result;
}

ViewManager::ViewManager(unsigned gameWidth, unsigned gameHeight)
    : gameW(gameWidth), gameH(gameHeight)
{
    view.reset(
        sf::FloatRect(
            0.f, 0.f,
            static_cast<float>(gameW),
            static_cast<float>(gameH)
        )
    );
}

void ViewManager::update(const sf::Vector2u& windowSize)
{
    view = makeLetterboxView(
        sf::View(
            sf::FloatRect(
                0.f, 0.f,
                static_cast<float>(gameW),
                static_cast<float>(gameH)
            )
        ),
        windowSize.x,
        windowSize.y
    );
}

void ViewManager::apply(sf::RenderWindow& window) const
{
    window.setView(view);
}

sf::View& ViewManager::getView()
{
    return view;
}
