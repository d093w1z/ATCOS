#pragma once
/*
- HandleInputs()
    - should handle mouse inputs
    - should add commands for user inputs
- DrawEntities
*/
#include <memory>
#include "AircraftShape.hpp"
#include "RenderEngine.hpp"
#include "core/radar.hpp"

class RadarControl : public Radar
{
   public:
    RadarControl();
    RadarControl(const RadarControl&) = default;
    RadarControl(RadarControl&&) = default;

    ~RadarControl() = default;

    void AddRenderEngine(std::shared_ptr<RenderEngine>);
    void DrawEntities();
    void HandleInputs(const std::optional<sf::Event>& event, const sf::RenderWindow& window);

   private:
    std::shared_ptr<RenderEngine> mRenderEngine;
    std::shared_ptr<AircraftShape> mSelected;
};