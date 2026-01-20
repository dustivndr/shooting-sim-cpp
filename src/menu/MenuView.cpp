#include "MenuView.hpp"

MenuView::MenuView(sf::Font& font)
{
    title.setFont(font);
    title.setCharacterSize(52);
    title.setFillColor(sf::Color(57, 255, 20));
}

void MenuView::setTitle(const std::string& text)
{
    title.setString(text);
}

void MenuView::setItems(const std::vector<std::string>& labels)
{
    items.clear();

    for (auto& label : labels)
    {
        sf::Text t;
        t.setFont(*title.getFont());
        t.setString(label);
        t.setCharacterSize(36);
        items.push_back(t);
    }
}

int MenuView::getItemCount() const
{
    return static_cast<int>(items.size());
}

void MenuView::setSelected(int index)
{
    selected = index;

    for (int i = 0; i < items.size(); ++i)
    {
        items[i].setFillColor(
            i == selected
                ? sf::Color(57, 255, 20)
                : sf::Color(30, 160, 20)
        );
    }
}

void MenuView::updateLayout(const sf::View& view)
{
    // Title
    auto tb = title.getLocalBounds();
    title.setOrigin(tb.width / 2.f, tb.height / 2.f);
    title.setPosition(view.getCenter().x, view.getCenter().y - 180.f);

    // Items
    float startY = view.getCenter().y - 20.f;

    for (int i = 0; i < items.size(); ++i)
    {
        auto b = items[i].getLocalBounds();
        items[i].setOrigin(b.width / 2.f, b.height / 2.f);
        items[i].setPosition(
            view.getCenter().x,
            startY + i * 50.f
        );
    }
}

void MenuView::draw(sf::RenderWindow& window)
{
    // Title glow
    for (int g = 0; g < 2; ++g)
    {
        sf::Text glow = title;
        glow.setFillColor(sf::Color(57, 255, 20, 60 - g * 20));
        glow.setScale(1.f + g * 0.04f, 1.f + g * 0.04f);
        window.draw(glow);
    }
    window.draw(title);

    // Items
    for (int i = 0; i < items.size(); ++i)
    {
        if (i == selected)
        {
            for (int g = 0; g < 2; ++g)
            {
                sf::Text glow = items[i];
                glow.setFillColor(sf::Color(57, 255, 20, 80 - g * 30));
                glow.setScale(1.f + g * 0.05f, 1.f + g * 0.05f);
                window.draw(glow);
            }
        }
        window.draw(items[i]);
    }
}
