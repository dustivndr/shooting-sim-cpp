#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

// TEST FILE FOR MENU NAVIGATION USING KEYBOARD AND CONTROLLER, WILL DELETE LATER

/* START OF IGNORE

sf::View getLetterboxView(sf::View view, int winW, int winH)
{
    float windowRatio = (float)winW / (float)winH;
    float viewRatio = view.getSize().x / view.getSize().y;

    float sizeX = 1.f, sizeY = 1.f;
    float posX = 0.f, posY = 0.f;

    if (windowRatio > viewRatio)
    {
        sizeX = viewRatio / windowRatio;
        posX = (1.f - sizeX) / 2.f;
    }
    else
    {
        sizeY = windowRatio / viewRatio;
        posY = (1.f - sizeY) / 2.f;
    }

    view.setViewport({posX, posY, sizeX, sizeY});
    return view;
}

enum MenuItem
{
    PLAY,
    EXIT
};

int main()
{
    constexpr unsigned GAME_W = 800;
    constexpr unsigned GAME_H = 600;

    bool fullscreen = false;

    sf::VideoMode windowedMode(GAME_W, GAME_H);
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(
        windowedMode,
        "SFML Game",
        sf::Style::Default);

    window.setFramerateLimit(60);

    sf::View gameView(sf::FloatRect(0, 0, GAME_W, GAME_H));
    window.setView(gameView);


    auto recreateWindow = [&](bool fs)
    {
        window.close();

        if (fs)
        {
            window.create(
                fullscreenMode,
                "SFML Game",
                sf::Style::Fullscreen);
        }
        else
        {
            window.create(
                windowedMode,
                "SFML Game",
                sf::Style::Default);
        }

        gameView = getLetterboxView(
            sf::View(sf::FloatRect(0, 0, GAME_W, GAME_H)),
            window.getSize().x,
            window.getSize().y);

        window.setView(gameView);
        window.setVerticalSyncEnabled(true);
    };

    // ---- Load font ----
    sf::Font font;
    if (!font.loadFromFile("assets/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    // ---------- TITLE ----------
    sf::Text title("TITLE EXAMPLE", font, 48);
    title.setFillColor(sf::Color::White);

    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2.f, titleBounds.height / 2.f);
    title.setPosition(400.f, 150.f);

    // ---- Text objects ----
    sf::Text playText("PLAY", font, 40);
    sf::Text exitText("EXIT", font, 40);
    sf::Text loremText(
        "Lorem ipsum dolor sit amet,\n"
        "consectetur adipiscing elit.\n"
        "Sed do eiusmod tempor incididunt.",
        font, 28);

    playText.setPosition(200.f, 250.f);
    exitText.setPosition(200.f, 300);
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

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::F11)
            {
                fullscreen = !fullscreen;
                recreateWindow(fullscreen);
            }

            if (event.type == sf::Event::Resized)
            {
                gameView = getLetterboxView(
                    gameView,
                    event.size.width,
                    event.size.height);
                window.setView(gameView);
            }

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
            window.draw(title);
            window.draw(playText);
            window.draw(exitText);
        }

        window.display();
    }

    return 0;
}

END OF THE IGNORE PART*/
