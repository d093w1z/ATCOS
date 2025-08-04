#include "RenderEngine.hpp"
#include <SFML/Graphics/Drawable.hpp>
#include "AircraftShape.hpp"

RenderEngine::RenderEngine() {}

RenderEngine::~RenderEngine()
{
    mDrawables.clear();
}

void RenderEngine::AddDrawables(std::shared_ptr<sf::Drawable> object)
{
    mDrawables.push_back(std::move(object));
}
void RenderEngine::draw(sf::RenderWindow& window)
{
    for (const auto& d : mDrawables)
    {
        if (d) window.draw(*d);
    }
}