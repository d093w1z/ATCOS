#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <chrono>
#include <cmath>
#include <deque>
#include "core/aircraft.hpp"

class AircraftShape : public sf::Drawable
{
   public:
    AircraftShape(const AircraftShape&);
    AircraftShape(Aircraft*, float size = 100.f);

   public:
    void Initialize();
    void InitializeFont();
    void InitializeAircraft(Aircraft*);

    const std::wstring GetStateLabel() const;

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
    sf::VertexArray mHeadingIndicator;
    std::deque<sf::CircleShape> mTrail;
    sf::CircleShape mRing;
    sf::Text mLabel;
    sf::Font mFont;

    void update();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
