#include "atcos.hpp"
#include <spdlog/spdlog.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <tracy/Tracy.hpp>
#include "config.hpp"
#include "graphics/aircraftShape.hpp"
#include "log.hpp"
#include "timer.hpp"

ATCOSApp::ATCOSApp()
{
    Log::Init();
    ATCOS_INFO("Game Starting Up");
    AppConfig config;

    config.parseFile("GameConfiguration.toml");
    Settings& settings = config.GetSettings();

    mWindow = sf::RenderWindow(sf::VideoMode({settings.Window.Width, settings.Window.Height}),
                               settings.Window.Title, sf::Style::Resize);
    mWindow.setFramerateLimit(settings.Window.FPS);
    mWindow.setPosition(sf::Vector2i({settings.Window.PositionX, settings.Window.PositionY}));
}

ATCOSApp::~ATCOSApp()
{
    ATCOS_INFO("Game Shutdown");
}

void ATCOSApp::RunLoop()
{
    ZoneScoped;
    sf::View view = mWindow.getDefaultView();

    mRenderer.AddDrawables(mRadar);

    int i = 0, j = 50, l = 0;
    float dt = 1.f / 144.f;
    while (mWindow.isOpen())
    {
        ScopedTimer st("Update Loop");
        while (const std::optional event = mWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                mWindow.close();
                ATCOS_INFO("Window closed");
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                view.setSize(
                    {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
                view.setCenter({view.getSize().x / 2.f, view.getSize().y / 2.f});
                mWindow.setView(view);
            }
            mRenderer.handleInput(event, mRadar);
        }

        mWindow.clear();

        mRenderer.Update(mRadar, dt);
        mRenderer.draw(mWindow);

        auto viewCenter = view.getCenter();
        auto viewSize = view.getSize();

        sf::Vector2f topLeft(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f);
        sf::Vector2f bottomRight(viewCenter.x + viewSize.x / 2.f, viewCenter.y + viewSize.y / 2.f);

        
        mWindow.display();
        FrameMark;
    }
}
