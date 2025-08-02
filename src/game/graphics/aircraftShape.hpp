#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <chrono>
#include <cmath>
#include <queue>
#include "core/aircraft.hpp"

class AircraftShape : public sf::Drawable
{
   public:
    AircraftShape(AircraftShape&);
    AircraftShape(Aircraft*, float size = 100.f);

   public:
    AircraftShape(float size = 100.f, float angleDeg = 90.f);

    void setSize(float size)
    {
        m_size = size;
        update();
    }

   private:
    float m_size;
    Aircraft* mAircraft;
    std::chrono::time_point<std::chrono::steady_clock> mTrailTimer =
        std::chrono::steady_clock::now();

    sf::VertexArray mBody;
    sf::VertexArray mTail;
    std::deque<sf::CircleShape> mTrail;

    void update();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
