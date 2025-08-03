#include "AircraftShape.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <chrono>
#include "log.hpp"

void AircraftShape::Initialize()
{
    InitializeFont();
    mTrailTimer = std::chrono::steady_clock().now();
}

void AircraftShape::InitializeAircraft(Aircraft* a)
{
    mAircraft = a;
    mAircraft->RegisterOnStateChanged([this](const AircraftState& state) { update(); });
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
    : m_size(size),
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
AircraftShape::AircraftShape(Aircraft* a, float size)
    : m_size(size),
      mBody(sf::PrimitiveType::LineStrip, 5),
      mHeadingIndicator(sf::PrimitiveType::Lines, 2),
      mLabel(mFont)
{
    Initialize();
    InitializeAircraft(a);
    mTrailTimer = std::chrono::steady_clock().now();
}

void AircraftShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto&& it : mTrail)
    {
        target.draw(it, states);
    }
    sf::Vector2f center = {mAircraft->GetPosition().Lat, mAircraft->GetPosition().Long};

    sf::CircleShape ring(m_size);

    // target.draw(mRing);

    target.draw(mBody, states);
    target.draw(mHeadingIndicator, states);
    target.draw(mLabel);
}
void AircraftShape::update()
{
    float s = m_size;
    float half = s / 2;

    sf::Vector2f center = {mAircraft->GetPosition().Lat, mAircraft->GetPosition().Long};
    if (mAircraft->GetSpeed() != 0)
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

    for (int i = 0; i < 5; i++)
    {
        mBody[i].color = sf::Color::Green;
    }

    // Tail line (from center to angle)
    float rad = mAircraft->GetHeading() * 3.14159265f / 180.f;
    float tailLength = 2 * s;

    sf::Vector2f tailStart = center;
    sf::Vector2f tailEnd =
        tailStart + sf::Vector2f(std::sin(rad), -std::cos(rad)) * tailLength * 2.f;

    mHeadingIndicator[0].position = tailStart;
    mHeadingIndicator[1].position = tailEnd;
    mHeadingIndicator[0].color = mHeadingIndicator[1].color = sf::Color{0, 255, 0, 127};

    mRing.setFillColor(sf::Color::Transparent);
    mRing.setRadius(m_size / 2);
    mRing.setOutlineColor(sf::Color::Green);
    mRing.setOutlineThickness(2);
    mRing.setPosition({center.x - half, center.y - half});

    sf::FloatRect textRect = mLabel.getLocalBounds();
    mLabel.setOrigin({textRect.size.x / 2, textRect.size.y / 2});
    mLabel.setPosition({center.x - half, center.y - half - 20});
    mLabel.setString(GetStateLabel());
    mLabel.setPosition({center.x - half - 10, center.y - half - 10});
}

const std::wstring AircraftShape::GetStateLabel() const
{
    std::wostringstream stringStream;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

    // stringStream << "CODE: " << converter.from_bytes(mAircraft->GetSquawkCode())
    //              << " | FL: " << mAircraft->GetFlightLevel() << std::endl;
    // stringStream << "SPD: " << static_cast<int>(mAircraft->GetSpeed()) << "kt"
    //              << " | HDG: " << static_cast<int>(mAircraft->GetHeading()) << "°";

    stringStream << "[" << converter.from_bytes(mAircraft->GetSquawkCode()) << "]\n";
    stringStream << static_cast<int>(mAircraft->GetSpeed()) << L"↑" << L"↓";

    return stringStream.str();
}
