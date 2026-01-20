#pragma once

#include <SFML/Graphics.hpp>

class ViewManager
{
public:
    ViewManager(unsigned gameWidth, unsigned gameHeight);

    void update(const sf::Vector2u& windowSize);
    const sf::View& getView() const;

private:
    sf::View view;
};
