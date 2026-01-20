#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class MenuView
{
public:
    MenuView(sf::Font& font);

    void setTitle(const std::string& text);
    void setItems(const std::vector<std::string>& labels);

    void setSelected(int index);
    int  getItemCount() const;

    void updateLayout(const sf::View& view);
    void draw(sf::RenderWindow& window);

private:
    sf::Text title;
    std::vector<sf::Text> items;
    int selected = 0;
};
