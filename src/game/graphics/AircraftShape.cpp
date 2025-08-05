#include "AircraftShape.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <chrono>
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>
#include "log.hpp"

void AircraftShape::Initialize()
{
    InitializeFont();
    mTrailTimer = std::chrono::steady_clock().now();

    mRing.setFillColor(sf::Color::Transparent);
    mRing.setRadius(mSize * 1.5);
    mRing.setOutlineColor(sf::Color::Blue);
    mRing.setOutlineThickness(3);
    sf::FloatRect ringRect = mRing.getLocalBounds();
    mRing.setOrigin(ringRect.getCenter());

    for (int i = 0; i < 5; i++)
    {
        mBody[i].color = sf::Color::Green;
    }

    mHeadingIndicator[0].color = mHeadingIndicator[1].color = sf::Color{0, 255, 0, 127};
}

void AircraftShape::InitializeFont()
{
    if (!mFont.openFromFile("assets/DejaVuSansMono-Bold.ttf"))
    {
        throw std::runtime_error("Failed to load font");
    }
    mLabel.setFont(mFont);
    mLabel.setCharacterSize(12);
    mLabel.setFillColor(sf::Color::Green);
}

AircraftShape::AircraftShape(float size, float angleDeg)
    : mSize(size),
      mBody(sf::PrimitiveType::LineStrip, 5),
      mHeadingIndicator(sf::PrimitiveType::Lines, 2),
      mLabel(mFont)
{
    Initialize();

    mTrailTimer = std::chrono::steady_clock().now();
}

AircraftShape::AircraftShape(const AircraftShape& as) : mLabel(mFont)
{
    Initialize();
}

void AircraftShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto&& it : mTrail)
    {
        target.draw(it, states);
    }
    sf::Vector2f center = {GetPosition().Lat, GetPosition().Long};

    target.draw(mBody, states);
    target.draw(mHeadingIndicator, states);
    target.draw(mRing);
    target.draw(mLabel);
}

void AircraftShape::update()
{
    float s = mSize;
    float half = s / 2;

    sf::Vector2f center = {GetPosition().Lat, GetPosition().Long};
    if (GetSpeed() != 0)
    {
        auto now = std::chrono::steady_clock().now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(now - mTrailTimer).count();

        if (elapsed >= 100)
        {
            mTrail.push_front(sf::CircleShape(1));
            mTrail.front().setPosition(center);
            mTrail.front().setFillColor(sf::Color{0, 255, 0, 127});
            mTrailTimer = std::chrono::steady_clock().now();
        }
        if (mTrail.size() > 10)
        {
            mTrail.pop_back();
        }
    }
    else
    {
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

    // Tail line (from center to angle)
    float rad = GetHeading() * 3.14159265f / 180.f;
    float tailLength = 2 * s;

    sf::Vector2f tailStart = center;
    sf::Vector2f tailEnd =
        tailStart + sf::Vector2f(std::sin(rad), -std::cos(rad)) * tailLength * 2.f;

    mHeadingIndicator[0].position = tailStart;
    mHeadingIndicator[1].position = tailEnd;

    mRing.setPosition({center.x, center.y});
    mRing.setOutlineColor(mSelected ? sf::Color::Magenta : sf::Color::Blue);

    mLabel.setString(GetStateLabel());
    sf::FloatRect textRect = mLabel.getLocalBounds();
    mLabel.setOrigin({textRect.size.x / 2, textRect.size.y});
    mLabel.setPosition({center.x, center.y - 20});
}

const std::wstring AircraftShape::GetStateLabel() const
{
    std::wostringstream stringStream;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    // stringStream << "CODE: " << converter.from_bytes(GetSquawkCode())
    //              << " | FL: " << GetFlightLevel() << std::endl;
    // stringStream << "SPD: " << static_cast<int>(GetSpeed()) << "kt"
    //              << " | HDG: " << static_cast<int>(GetHeading()) << "°";

    stringStream << "[" << converter.from_bytes(GetSquawkCode()) << "]\n";
    stringStream << static_cast<int>(GetSpeed())
                 << ((static_cast<int>(GetSpeed()) == static_cast<int>(GetTargetSpeed()))
                         ? L"="
                         : ((GetSpeed() < GetTargetSpeed()) ? L"↑" : L"↓"));
    stringStream << static_cast<int>(GetTargetSpeed()) << std::endl;

    stringStream << static_cast<int>(GetHeading())
                 << ((static_cast<int>(GetHeading()) == static_cast<int>(GetTargetHeading()))
                         ? L"="
                         : ((GetHeading() < GetTargetHeading()) ? L"↑" : L"↓"));
    stringStream << static_cast<int>(GetTargetHeading());

    return stringStream.str();
}

bool AircraftShape::ContainsPoint(const sf::Vector2f& point) const
{
    // Get the center of the circle in world space
    sf::Vector2f center = mRing.getTransform().transformPoint(mRing.getOrigin());

    float radius = mRing.getRadius();

    float dx = point.x - center.x;
    float dy = point.y - center.y;

    return (dx * dx + dy * dy) <= (radius * radius);
}
