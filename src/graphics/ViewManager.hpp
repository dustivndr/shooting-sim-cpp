#pragma once

#include <SFML/Graphics.hpp>

class ViewManager
{
public:
    ViewManager(unsigned gameWidth, unsigned gameHeight);

    // Call when window is created or recreated
    void update(const sf::Vector2u& windowSize);

    // Apply view before drawing
    void apply(sf::RenderWindow& window) const;

    // Access if needed (camera movement later)
    sf::View& getView();

private:
    sf::View view;
    unsigned gameW;
    unsigned gameH;
};
