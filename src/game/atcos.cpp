#include "atcos.hpp"
#include <spdlog/spdlog.h>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <memory>
#include <tracy/Tracy.hpp>
#include "graphics/RadarControl.hpp"
#include "graphics/RenderEngine.hpp"
#include "log.hpp"
#include "timer.hpp"

ATCOSApp::ATCOSApp()
{
    Log::Init();
    ATCOS_INFO("Game Starting Up");

    mConfig.parseFile("GameConfiguration.toml");
    Settings& settings = mConfig.GetSettings();

    mWindow = sf::RenderWindow(sf::VideoMode({settings.Window.Width, settings.Window.Height}),
                               settings.Window.Title, sf::Style::Default);
    mWindow.setFramerateLimit(settings.Window.FPS);
    mWindow.setPosition(sf::Vector2i({settings.Window.PositionX, settings.Window.PositionY}));

    // Initialize RadarControl & RenderEngine
    mRenderEngine = std::make_shared<RenderEngine>();
    mRadar = std::make_shared<RadarControl>();
    mRadar->AddRenderEngine(mRenderEngine);
}

ATCOSApp::~ATCOSApp()
{
    ATCOS_INFO("Game Shutdown");
}

void ATCOSApp::RunLoop()
{
    ZoneScoped;
    constexpr float VIEW_CENTER_DIVISOR = 2.f;  // Avoid magic number

    sf::View view = mWindow.getDefaultView();

    mRadar->DrawEntities();
    Settings& settings = mConfig.GetSettings();
    float dt = 1.f / (float) settings.Window.FPS;
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
                view.setCenter({view.getSize().x / VIEW_CENTER_DIVISOR,
                                view.getSize().y / VIEW_CENTER_DIVISOR});
                mWindow.setView(view);
            }
            mRadar->HandleInputs(event, mWindow);
        }

        mWindow.clear(sf::Color());

        mRadar->Update(dt);
        mRenderEngine->draw(mWindow);

        mWindow.display();
        FrameMark;
    }
}
