#include "SceneManager.hpp"

void SceneManager::changeScene(std::unique_ptr<Scene> newScene)
{
    currentScene = std::move(newScene);
}

void SceneManager::handleEvent(const sf::Event& event)
{
    if (currentScene)
        currentScene->handleEvent(event);
}

void SceneManager::update()
{
    if (currentScene)
        currentScene->update();
}

void SceneManager::render(sf::RenderWindow& window)
{
    if (currentScene)
        currentScene->render(window);
}

bool SceneManager::hasScene() const
{
    return currentScene != nullptr;
}