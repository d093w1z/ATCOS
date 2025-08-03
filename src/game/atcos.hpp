#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "graphics/RadarControl.hpp"
#include "graphics/RenderEngine.hpp"

class ATCOSApp
{
   private:
    bool IsRunning = false;
    sf::RenderWindow mWindow;

    std::shared_ptr<RadarControl> mRadar;
    std::shared_ptr<RenderEngine> mRenderEngine;

   public:
    ATCOSApp();
    ~ATCOSApp();

    void RunLoop();
};
