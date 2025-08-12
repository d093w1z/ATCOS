#include "RadarControl.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <random>
#include <utility>
#include "graphics/AircraftShape.hpp"
#include "log.hpp"

RadarControl::RadarControl(std::shared_ptr<EntityManager> entityManager)
    : mEntityManager(std::move(entityManager)), mSelected(nullptr)
{
    // Initialize the radar with some aircrafts
    InitializeRadar();
}

void RadarControl::InitializeRadar()
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
        auto aircraft = std::make_shared<AircraftShape>(i);
        aircraft->SetSquawkCode(s.GetString());
        aircraft->SetTargetFlightLevel(5);
        aircraft->SetTargetHeading(headingDist(gen));
        aircraft->SetTargetSpeed(speedDist(gen));
        aircraft->SetPosition(posXDist(gen), posYDist(gen));
        mEntityManager->registerEntity(aircraft);
    }
    // ATCOS_LIB_INFO("Aircrafts Added");
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

        // for (auto& [_, aircraft] : mEntityManager->getEntity())
        // {
        //     if (auto shape = std::dynamic_pointer_cast<AircraftShape>(aircraft))
        //     {
        //         if (shape->ContainsPoint(mouseWorld))
        //         {
        //             // Clicked on this AircraftShape
        //             if (mSelected)
        //             {
        //                 mSelected->SetSelected(false);
        //             }
        //             mSelected = shape;
        //             mSelected->SetSelected(true);
        //         }
        //     }
        // }
    }
}