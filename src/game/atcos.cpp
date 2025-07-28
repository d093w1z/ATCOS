#include "atcos.hpp"

#include <spdlog/spdlog.h>

#include <SFML/Graphics.hpp>

#include "core/core.hpp"
#include "log.hpp"

ATCOSApp::ATCOSApp()
{
    Log::Init();

    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(100, 100));
    ATCOS_INFO("Started application");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
                ATCOS_INFO("Window closed");
            }
        }

        window.clear();
        window.display();
    }
}

ATCOSApp::~ATCOSApp() {}
