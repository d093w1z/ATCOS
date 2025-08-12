#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <chrono>
#include <deque>
#include "Entity.hpp"
#include "core/aircraft.hpp"

class AircraftShape : public IEntity, public Aircraft
{
   public:
    static constexpr float DefaultSize = 10.f;
    static constexpr float DefaultHeading = 90.f;

    AircraftShape(int id, float size = DefaultSize, float angleDeg = DefaultHeading);

    AircraftShape(const AircraftShape&);

   public:
    void Initialize();
    void InitializeFont();

    const std::wstring GetStateLabel() const;

    void SetSize(float size)
    {
        mSize = size;
        update();
    }

    bool ContainsPoint(const sf::Vector2f& point) const;
    void SetSelected(bool state)
    {
        mSelected = state;
    }

   private:
    float mSize;
    std::chrono::time_point<std::chrono::steady_clock> mTrailTimer =
        std::chrono::steady_clock::now();

    sf::VertexArray mBody;
    sf::VertexArray mHeadingIndicator;
    std::deque<sf::CircleShape> mTrail;
    sf::CircleShape mRing;
    sf::Text mLabel;
    sf::Font mFont;
    bool mSelected = false;

    void update() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(float dt) override
    {
        Update(dt);
    }
};
