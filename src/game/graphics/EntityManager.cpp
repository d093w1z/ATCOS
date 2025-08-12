#include "EntityManager.hpp"
#include "AircraftShape.hpp"
#include "Event.hpp"

void EntityManager::HandleInputs(std::shared_ptr<EventDispatcher> eventDispatcher,
                                 const std::optional<sf::Event>& event,
                                 const sf::RenderWindow& window)
{
    if (const auto* clickPos = event->getIf<sf::Event::MouseButtonPressed>())
    {
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);  // convert to world space
        // Check if any entity contains the clicked point
        for (auto& [_, aircraft] : entities)
        {
            if (auto shape = std::dynamic_pointer_cast<AircraftShape>(aircraft))
            {
                if (shape->ContainsPoint(mouseWorld))
                {
                    eventDispatcher->dispatch<EntitySelectedEvent>(
                        EntitySelectedEvent{shape->getId()});
                }
            }
        }
    }
}