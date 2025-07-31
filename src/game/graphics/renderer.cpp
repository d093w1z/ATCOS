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
    for (auto&& e : radar.entities)
    {
        mDrawables.push_back(new AircraftShape(e, 5));
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
