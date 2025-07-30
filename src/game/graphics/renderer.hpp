#include <SFML/Graphics.hpp>
#include "core/core.hpp"

class Renderer
{
   public:
    Renderer();
    ~Renderer();

    void Update(sf::RenderWindow&, Radar&);

   private:
};
