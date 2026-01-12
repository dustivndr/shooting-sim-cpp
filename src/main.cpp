#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <optional>

// TEST CODE, GENERATED WITH AI

// --------------------------------------------------
// Letterbox helper
// --------------------------------------------------
sf::View getLetterboxView(sf::View view, int winW, int winH)
{
    float windowRatio = static_cast<float>(winW) / static_cast<float>(winH);
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

    view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));
    return view;
}

// --------------------------------------------------
// Menu enum
// --------------------------------------------------
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

    sf::VideoMode windowedMode({GAME_W, GAME_H});
    sf::VideoMode fullscreenMode = sf::VideoMode::getDesktopMode();

    sf::RenderWindow window(
        windowedMode,
        "SFML Game",
        sf::Style::Default);

    window.setVerticalSyncEnabled(true);

    sf::View gameView(sf::FloatRect({0.f, 0.f}, {GAME_W, GAME_H}));
    window.setView(gameView);

    // --------------------------------------------------
    // Window recreation (fullscreen toggle)
    // --------------------------------------------------
    auto recreateWindow = [&](bool fs)
    {
        window.close();

        if (fs)
        {
            window.create(
                fullscreenMode,
                "SFML Game",
                sf::State::Fullscreen);
        }
        else
        {
            window.create(
                windowedMode,
                "SFML Game",
                sf::State::Windowed);
        }

        gameView = getLetterboxView(
            sf::View(sf::FloatRect({0.f, 0.f}, {GAME_W, GAME_H})),
            window.getSize().x,
            window.getSize().y);

        window.setView(gameView);
        window.setVerticalSyncEnabled(true);
    };

    sf::Font font;
    if (!font.openFromFile("assets/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "Failed to load font\n";
        return 1;
    }

    sf::Text title(font);
    title.setFont(font);
    title.setString("TITLE EXAMPLE");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);

    auto titleBounds = title.getLocalBounds();
    title.setOrigin({
        titleBounds.size.x / 2.f,
        titleBounds.size.y / 2.f
    });
    title.setPosition({400.f, 150.f});

    sf::Text playText(font);
    playText.setFont(font);
    playText.setString("PLAY");
    playText.setCharacterSize(40);

    sf::Text exitText(font);
    exitText.setFont(font);
    exitText.setString("EXIT");
    exitText.setCharacterSize(40);

    playText.setPosition({200.f, 250.f});
    exitText.setPosition({200.f, 300.f});

    sf::Text loremText(font);
    loremText.setFont(font);
    loremText.setCharacterSize(28);
    loremText.setString(
        "Lorem ipsum dolor sit amet,\n"
        "consectetur adipiscing elit.\n"
        "Sed do eiusmod tempor incididunt.");
    loremText.setPosition({200.f, 200.f});

    MenuItem selected = PLAY;
    bool showLorem = false;
    bool dpadUsed = false;

    // --------------------------------------------------
    // Main loop
    // --------------------------------------------------
    while (window.isOpen())
    {
        // ---------------- Events ----------------
        while (auto event = window.pollEvent())
        {
            // Close
            if (event->is<sf::Event::Closed>())
                window.close();

            // Resize
            if (const auto *resized = event->getIf<sf::Event::Resized>())
            {
                gameView = getLetterboxView(
                    gameView,
                    resized->size.x,
                    resized->size.y);
                window.setView(gameView);
            }

            // Keyboard input
            if (const auto *key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::F11)
                {
                    fullscreen = !fullscreen;
                    recreateWindow(fullscreen);
                }

                if (key->code == sf::Keyboard::Key::Up)
                    selected = PLAY;

                if (key->code == sf::Keyboard::Key::Down)
                    selected = EXIT;

                if (key->code == sf::Keyboard::Key::Enter)
                {
                    if (selected == PLAY)
                        showLorem = true;
                    else
                        return 0;
                }
            }

            // Joystick button
            if (const auto *joy = event->getIf<sf::Event::JoystickButtonPressed>())
            {
                const unsigned X_BUTTON = 3;

                if (joy->joystickId == 0 && joy->button == X_BUTTON)
                {
                    if (selected == PLAY)
                        showLorem = true;
                    else
                        return 0;
                }
            }
        }

        // ---------------- D-Pad navigation ----------------
        if (sf::Joystick::isConnected(0))
        {
            float povY = sf::Joystick::getAxisPosition(
                0,
                sf::Joystick::Axis::PovY);

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

        // ---------------- Visual state ----------------
        sf::Color inactive(120, 120, 120);
        playText.setFillColor(selected == PLAY ? sf::Color::White : inactive);
        exitText.setFillColor(selected == EXIT ? sf::Color::White : inactive);

        // ---------------- Draw ----------------
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
