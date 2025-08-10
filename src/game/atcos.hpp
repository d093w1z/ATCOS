#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "config.hpp"
#include "graphics/RadarControl.hpp"
#include "graphics/RenderEngine.hpp"

class ATCOSApp
{
   private:
    bool IsRunning = false;
    sf::RenderWindow mWindow;
    AppConfig mConfig;

    std::shared_ptr<RadarControl> mRadar;
    std::shared_ptr<RenderEngine> mRenderEngine;

   public:
    ATCOSApp();
    ~ATCOSApp();

    void RunLoop();
};
