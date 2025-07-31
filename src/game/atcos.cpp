#include "atcos.hpp"
#include <spdlog/spdlog.h>
#include "config.hpp"
#include "core/core.hpp"
#include "log.hpp"
#include <tracy/Tracy.hpp>

ATCOSApp::ATCOSApp()
{
    Log::Init();
    ATCOS_INFO("Game Starting Up");
    AppConfig config;
    Radar r;

    config.parseFile("GameConfiguration.toml");
    Settings& settings = config.GetSettings();


    mWindow = sf::RenderWindow(sf::VideoMode({settings.Window.Width, settings.Window.Height}),
                               settings.Window.Title);
    mWindow.setFramerateLimit(144);
    mWindow.setPosition(sf::Vector2i(100, 100));
}

ATCOSApp::~ATCOSApp()
{
    ATCOS_INFO("Game Shutdown");
}

void ATCOSApp::RunLoop()
{
    sf::RectangleShape rect[5];
    int i = 0, j = 50, l = 0;
    while (mWindow.isOpen())
    {
        while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                mWindow.close();
                ATCOS_INFO("Window closed");
            }
        }

        mWindow.clear();

        while (l < sizeof(rect) / sizeof(rect[0]))
        {
            rect[l].setSize(sf::Vector2f(20, 20));
            rect[l].setPosition(sf::Vector2f((float)i, (float)j));
            mWindow.draw(rect[l]);
            i += 25;
            l++;
        }
        j++;
        // Reset variables.
        l = 0;
        i = 0;
        // Copy the buffer to the mWindow.
        mWindow.display();
        FrameMark;
    }
}
