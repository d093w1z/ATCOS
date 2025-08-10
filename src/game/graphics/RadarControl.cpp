#include "RadarControl.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <random>
#include "graphics/AircraftShape.hpp"
#include "log.hpp"

RadarControl::RadarControl()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> speedDist(0, 15);
    std::uniform_real_distribution<float> headingDist(0, 360);

    std::uniform_int_distribution<> squawkDist(0, 7);
    std::uniform_real_distribution<float> posXDist(100, 300);
    std::uniform_real_distribution<float> posYDist(100, 300);

    ATCOS_LIB_INFO("Radar Initialized!");
    for (int i = 0; i < 10; i++)
    {
        SquawkCode s((unsigned int) squawkDist(gen), (unsigned int) squawkDist(gen),
                     (unsigned int) squawkDist(gen), (unsigned int) squawkDist(gen));
        GetEntities()[s] = std::make_shared<AircraftShape>();
        GetEntities()[s]->SetSquawkCode(s.GetString());
    }
    // ATCOS_LIB_INFO("Aircrafts Added");
    for (auto& [key, value] : GetEntities())
    {
        value->SetTargetFlightLevel(5);
        value->SetTargetHeading(headingDist(gen));
        value->SetTargetSpeed(speedDist(gen));
        value->SetPosition(posXDist(gen), posYDist(gen));
    }
}

void RadarControl::AddRenderEngine(std::shared_ptr<RenderEngine> re)
{
    mRenderEngine = re;
}

void RadarControl::DrawEntities()
{
    for (auto& [key, value] : GetEntities())
    {
        // Attempt to cast Aircraft -> AircraftShape (which is also sf::Drawable)
        if (auto shape = std::dynamic_pointer_cast<AircraftShape>(value))
        {
            mRenderEngine->AddDrawables(shape);
        }
    }
}

void RadarControl::HandleInputs(const std::optional<sf::Event>& event,
                                const sf::RenderWindow& window)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        if (mSelected) mSelected->SetTargetHeading(mSelected->GetTargetHeading() - 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        if (mSelected) mSelected->SetTargetHeading(mSelected->GetTargetHeading() + 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        if (mSelected) mSelected->SetTargetSpeed(mSelected->GetTargetSpeed() - 1);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if (mSelected) mSelected->SetTargetSpeed(mSelected->GetTargetSpeed() + 1);
    }
    if (const auto* clickPos = event->getIf<sf::Event::MouseButtonPressed>())
    {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);  // convert to world space

        for (auto& [_, aircraft] : GetEntities())
        {
            if (auto shape = std::dynamic_pointer_cast<AircraftShape>(aircraft))
            {
                if (shape->ContainsPoint(mouseWorld))
                {
                    // Clicked on this AircraftShape
                    if (mSelected)
                    {
                        mSelected->SetSelected(false);
                    }
                    mSelected = shape;
                    mSelected->SetSelected(true);
                }
            }
        }
    }
}