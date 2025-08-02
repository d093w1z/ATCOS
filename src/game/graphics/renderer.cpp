#include "renderer.hpp"
#include "aircraftShape.hpp"

Renderer::Renderer() {}

Renderer::~Renderer()
{
    for (auto it : mDrawables)
    {
        delete it;
    }
    mDrawables.clear();
}

void Renderer::AddDrawables(Radar& radar)
{
    for (auto&& [key, value] : radar.GetEntities())
    {
        mDrawables.push_back(new AircraftShape(&value, 5));
    }
}

void Renderer::Update(Radar& radar, float dt)
{
    radar.Update(dt);
}

void Renderer::draw(sf::RenderWindow& window)
{
    for (auto&& it : mDrawables)
    {
        window.draw(*it);
    }
}

void Renderer::handleInput(const std::optional<sf::Event>& event, Radar& radar)
{
    if (const auto* resized = event->getIf<sf::Event::KeyPressed>())
    {
        radar.GetEntities().begin();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        Aircraft& a = radar.GetEntities().begin()->second;
        a.SetHeading(a.GetHeading() - 1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        Aircraft& a = radar.GetEntities().begin()->second;
        a.SetHeading(a.GetHeading() + 1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        Aircraft& a = radar.GetEntities().begin()->second;
        a.SetSpeed(a.GetSpeed() - 1);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        Aircraft& a = radar.GetEntities().begin()->second;
        a.SetSpeed(a.GetSpeed() + 1);
    }
}
