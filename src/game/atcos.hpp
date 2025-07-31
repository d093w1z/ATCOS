#pragma once
#include <SFML/Graphics.hpp>
#include "core/radar.hpp"
#include "graphics/renderer.hpp"
class ATCOSApp
{
   private:
    bool IsRunning = false;
    sf::RenderWindow mWindow;
    Radar mRadar;
    Renderer mRenderer;

   public:
    ATCOSApp();
    ~ATCOSApp();

    void RunLoop();
};
