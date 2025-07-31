#include "aircraftShape.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <chrono>
#include "log.hpp"

AircraftShape::AircraftShape(float size, float angleDeg)
    : m_size(size), mBody(sf::PrimitiveType::LineStrip, 5), mTail(sf::PrimitiveType::Lines, 2)
{
    mTrailTimer = std::chrono::steady_clock().now();
    mAircraft->RegisterOnStateChanged([this](const AircraftState& state) { update(); });
    update();  // Initial setup
}

AircraftShape::AircraftShape(AircraftShape& as) {}
AircraftShape::AircraftShape(Aircraft& a, float size)
    : m_size(size), mBody(sf::PrimitiveType::LineStrip, 5), mTail(sf::PrimitiveType::Lines, 2)
{
    mAircraft = &a;
    mTrailTimer = std::chrono::steady_clock().now();
    mAircraft->RegisterOnStateChanged([this](const AircraftState& state) { update(); });
    update();
}

void AircraftShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBody, states);
    target.draw(mTail, states);
    for (auto&& it : mTrail)
    {
        target.draw(it, states);
    }
}
void AircraftShape::update()
{
    float s = m_size;
    float half = s / 2;
    // ATCOS_DEBUG(mTrail.size());

    sf::Vector2f center = {mAircraft->GetPosition().Lat, mAircraft->GetPosition().Long};
    if (mAircraft->GetSpeed() != 0)
    {
        auto now = std::chrono::steady_clock().now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - mTrailTimer).count();

        if (elapsed >= 100)
        {
            mTrail.push_front(sf::CircleShape(2));
            mTrail.front().setPosition(center);
            mTrail.front().setFillColor(sf::Color(100, 100, 100));
            mTrailTimer = std::chrono::steady_clock().now();
        }
        // mTrail.front().setOutlineThickness(0);
        if (mTrail.size() > 10)
        {
            mTrail.pop_back();
        }
        ATCOS_DEBUG("AircraftShape: \n\ttrail: ({})\n\tspeed({})\n\tpos:{},{}\n\telapsed:{}",
                    mTrail.size(), mAircraft->GetSpeed(), mAircraft->GetPosition().Lat,
                    mAircraft->GetPosition().Long, elapsed);
    }
    else
    {
        // ATCOS_DEBUG("Trail Cleared!");
        // ATCOS_DEBUG("AircraftShape: ({}):{},{}", mAircraft->GetSpeed(),
        // mAircraft->GetPosition().Lat,
        //             mAircraft->GetPosition().Long);
        mTrail.clear();
    }

    // Square corners (clockwise)
    sf::Vector2f tl = center + sf::Vector2f(-half, -half);
    sf::Vector2f bl = center + sf::Vector2f(-half, half);
    sf::Vector2f br = center + sf::Vector2f(half, half);
    sf::Vector2f tr = center + sf::Vector2f(half, -half);

    mBody[0].position = tl;
    mBody[1].position = bl;
    mBody[2].position = br;
    mBody[3].position = tr;
    mBody[4].position = tl;  // close square

    for (int i = 0; i < 5; i++)
    {
        mBody[i].color = sf::Color::White;
    }

    // Tail line (from center to angle)
    float rad = mAircraft->GetHeading() * 3.14159265f / 180.f;
    float tailLength = s;

    sf::Vector2f tailStart = center;
    sf::Vector2f tailEnd =
        tailStart + sf::Vector2f(std::cos(rad), std::sin(rad)) * tailLength * 2.f;

    mTail[0].position = tailStart;
    mTail[1].position = tailEnd;
    mTail[0].color = mTail[1].color = sf::Color::White;
}
