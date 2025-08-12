#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "config.hpp"
#include "graphics/EntityManager.hpp"
#include "graphics/RadarControl.hpp"

class ATCOSApp
{
   private:
    bool IsRunning = false;
    sf::RenderWindow mWindow;
    AppConfig mConfig;

    std::shared_ptr<RadarControl> mRadar;
    std::shared_ptr<EntityManager> mEntityManager;

   public:
    ATCOSApp();
    ~ATCOSApp();

    void RunLoop();
};
