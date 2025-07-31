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
    // sf::RectangleShape rect[5];
    // sf::CircleShape dots[4];
    // AircraftShape as(10.f);

    mRenderer.AddDrawables(mRadar);
    // as.SetHeading(10);
    // as.SetSpeed(10);

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
        }

        mWindow.clear();

        mRenderer.Update(mRadar, dt);
        mRenderer.draw(mWindow);

        // dots[0].setRadius(30);
        // dots[1].setRadius(30);
        // dots[2].setRadius(30);
        // dots[3].setRadius(30);

        auto viewCenter = view.getCenter();
        auto viewSize = view.getSize();

        sf::Vector2f topLeft(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f);
        sf::Vector2f bottomRight(viewCenter.x + viewSize.x / 2.f, viewCenter.y + viewSize.y / 2.f);

        // dots[0].setPosition(topLeft);                                               // top-left
        // dots[1].setPosition({topLeft.x, bottomRight.y - dots[1].getRadius() * 2});  //
        // bottom-left dots[2].setPosition({bottomRight.x - dots[2].getRadius() * 2, topLeft.y}); //
        // top-right dots[3].setPosition({bottomRight.x - dots[3].getRadius() * 2,
        //                      bottomRight.y - dots[3].getRadius() * 2});  // bottom-right

        // mWindow.draw(dots[0]);
        // mWindow.draw(dots[1]);
        // mWindow.draw(dots[2]);
        // mWindow.draw(dots[3]);
        // mWindow.draw(as);

        // while (l < sizeof(rect) / sizeof(rect[0]))
        // {
        //     rect[l].setSize(sf::Vector2f(20, 20));
        //     rect[l].setPosition(sf::Vector2f((float) i, (float) j));

        //     mWindow.draw(rect[l]);
        //     i += 25;
        //     l++;
        // }
        // j++;
        // if (j > view.getSize().y) j = 0;
        // // Reset variables.
        // l = 0;
        // i = 0;
        // as.SetHeading(as.GetHeading() + 1);
        // Copy the buffer to the mWindow.
        mWindow.display();
        FrameMark;
    }
}
