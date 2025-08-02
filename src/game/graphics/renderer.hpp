#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <vector>
#include "core/radar.hpp"
class Renderer
{
   public:
    Renderer();
    ~Renderer();

    void AddDrawables(Radar &);
    void Update(Radar &, float);
    void draw(sf::RenderWindow &);
    void handleInput(const std::optional<sf::Event> &, Radar &);
   private:
    std::vector<sf::Drawable *> mDrawables;
};
