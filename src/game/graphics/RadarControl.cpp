#include "RadarControl.hpp"
#include "AircraftShape.hpp"

RadarControl::RadarControl() {}
RadarControl::~RadarControl() {}

void RadarControl::AddRenderEngine(std::shared_ptr<RenderEngine> re)
{
    mRenderEngine = re;
}
void RadarControl::DrawEntities()
{
    for (auto& [key, value] : GetEntities())
    {
        mRenderEngine->AddDrawables(new AircraftShape(&value, 10));
    }
}

void RadarControl::HandleInputs(const std::optional<sf::Event>& event)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        Aircraft& a = GetEntities().begin()->second;
        a.SetHeading(a.GetHeading() - 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        Aircraft& a = GetEntities().begin()->second;
        a.SetHeading(a.GetHeading() + 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        Aircraft& a = GetEntities().begin()->second;
        a.SetSpeed(a.GetSpeed() - 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        Aircraft& a = GetEntities().begin()->second;
        a.SetSpeed(a.GetSpeed() + 1);
    }
}