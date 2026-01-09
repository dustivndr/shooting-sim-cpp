#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

enum MenuItem
{
    PLAY,
    EXIT
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Controller Menu");
    window.setFramerateLimit(60);

    // ---- Load font ----
    sf::Font font;
    if (!font.loadFromFile("assets/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    // ---- Text objects ----
    sf::Text playText("PLAY", font, 40);
    sf::Text exitText("EXIT", font, 40);
    sf::Text loremText(
        "Lorem ipsum dolor sit amet,\n"
        "consectetur adipiscing elit.\n"
        "Sed do eiusmod tempor incididunt.",
        font, 28);

    playText.setPosition(350, 220);
    exitText.setPosition(350, 300);
    loremText.setPosition(200, 200);

    MenuItem selected = PLAY;
    bool showLorem = false;

    // Debounce flags
    bool dpadUsed = false;

    // ---- MAIN LOOP ----
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // ---- Keyboard navigation ----
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    selected = PLAY;
                if (event.key.code == sf::Keyboard::Down)
                    selected = EXIT;

                if (event.key.code == sf::Keyboard::Enter)
                {
                    if (selected == PLAY)
                        showLorem = true;
                    else
                        return 0;
                }
            }

            // ---- Controller button pressed (confirm) ----
            if (event.type == sf::Event::JoystickButtonPressed)
            {
                std::cout << "Joystick button pressed: "
                          << event.joystickButton.button << std::endl;

                // Replace this number with YOUR X button index
                const unsigned int X_BUTTON = 3;

                if (event.joystickButton.joystickId == 0 &&
                    event.joystickButton.button == X_BUTTON)
                {

                    if (selected == PLAY)
                        showLorem = true;
                    else
                        return 0;
                }
            }
        }

        // ---- D-Pad navigation (real-time) ----
        if (sf::Joystick::isConnected(0))
        {
            float povY = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);

            if (!dpadUsed)
            {
                if (povY > 50)
                {
                    selected = EXIT;
                    dpadUsed = true;
                }
                else if (povY < -50)
                {
                    selected = PLAY;
                    dpadUsed = true;
                }
            }

            if (povY > -20 && povY < 20)
                dpadUsed = false;
        }

        // ---- Colors ----
        sf::Color inactive(120, 120, 120);
        playText.setFillColor(selected == PLAY ? sf::Color::White : inactive);
        exitText.setFillColor(selected == EXIT ? sf::Color::White : inactive);

        // ---- Draw ----
        window.clear(sf::Color::Black);

        if (showLorem)
        {
            window.draw(loremText);
        }
        else
        {
            window.draw(playText);
            window.draw(exitText);
        }

        window.display();
    }

    return 0;
}
