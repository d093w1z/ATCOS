#include "RenderEngine.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include "AircraftShape.hpp"

RenderEngine::RenderEngine() {}

RenderEngine::~RenderEngine()
{
    for (auto it : mDrawables)
    {
        delete it;
    }
    mDrawables.clear();
}

void RenderEngine::AddDrawables(sf::Drawable* object)
{
    mDrawables.push_back(object);
}

void RenderEngine::draw(sf::RenderWindow& window)
{
    for (auto&& it : mDrawables)
    {
        window.draw(*it);
    }
}

// void RenderEngine::handleInput(const std::optional<sf::Event>& event, Radar& radar)
// {
//     if (const auto* resized = event->getIf<sf::Event::KeyPressed>())
//     {
//         radar.GetEntities().begin();
//     }

//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
//     {
//         Aircraft& a = radar.GetEntities().begin()->second;
//         a.SetHeading(a.GetHeading() - 1);
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
//     {
//         Aircraft& a = radar.GetEntities().begin()->second;
//         a.SetHeading(a.GetHeading() + 1);
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
//     {
//         Aircraft& a = radar.GetEntities().begin()->second;
//         a.SetSpeed(a.GetSpeed() - 1);
//     }
//     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
//     {
//         Aircraft& a = radar.GetEntities().begin()->second;
//         a.SetSpeed(a.GetSpeed() + 1);
//     }
// }
