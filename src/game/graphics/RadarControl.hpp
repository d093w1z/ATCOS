#pragma once
/*
- HandleInputs()
    - should handle mouse inputs
    - should add commands for user inputs
- DrawEntities
*/
#include <memory>
#include "AircraftShape.hpp"
#include "EntityManager.hpp"
#include "core/radar.hpp"

class RadarControl : public Radar
{
   public:
    RadarControl();
    RadarControl(std::shared_ptr<EntityManager>);
    RadarControl(const RadarControl&) = default;
    RadarControl(RadarControl&&) = default;

    ~RadarControl() = default;

    void InitializeRadar();
    void HandleInputs(const std::optional<sf::Event>& event, const sf::RenderWindow& window);

   private:
    std::shared_ptr<EntityManager> mEntityManager;
    std::shared_ptr<AircraftShape> mSelected;
};