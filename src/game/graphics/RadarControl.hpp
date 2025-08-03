#pragma once
/*
- HandleInputs()
    - should handle mouse inputs
    - should add commands for user inputs
- DrawEntities
*/
#include <memory>
#include "RenderEngine.hpp"
#include "core/radar.hpp"

class RadarControl : public Radar
{
   public:
    RadarControl();
    ~RadarControl();

    void AddRenderEngine(std::shared_ptr<RenderEngine>);
    void DrawEntities();
    void HandleInputs(const std::optional<sf::Event>& event);

   private:
    std::shared_ptr<RenderEngine> mRenderEngine;
};