#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>
class RenderEngine
{
   public:
    RenderEngine();
    ~RenderEngine();

    void AddDrawables(sf::Drawable *);
    void draw(sf::RenderWindow &);
    // void handleInput(const std::optional<sf::Event> &);

   private:
    std::vector<sf::Drawable *> mDrawables;
};
