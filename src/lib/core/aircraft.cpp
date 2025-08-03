#include "aircraft.hpp"
#include <sstream>
#include "log.hpp"
#include "math.h"

SquawkCode::SquawkCode(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    Set(a, b, c, d);
}

SquawkCode::SquawkCode(const std::string& input)
{
    Set(input);
}

SquawkCode::SquawkCode(const char* input)
{
    Set(input);
}

bool SquawkCode::IsValid() const
{
    return IsValid(A, B, C, D);
}

bool SquawkCode::IsValid(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    return a <= 7 && b <= 7 && c <= 7 && d <= 7;
}

void SquawkCode::Set(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    if (!IsValid(a, b, c, d))
        throw std::invalid_argument("Invalid squawk code digits (must be in range 0-7)");
    A = a;
    B = b;
    C = c;
    D = d;
}

void SquawkCode::Set(const std::string& input)
{
    if (input.length() != 4 || input.find_first_not_of("01234567") != std::string::npos)
    {
        throw std::invalid_argument(
            "Invalid squawk code digits (there must be 4 digits & must be in range 0-7)");
    }

    A = input[0] - '0';
    B = input[1] - '0';
    C = input[2] - '0';
    D = input[3] - '0';
}

std::string SquawkCode::GetString() const
{
    std::ostringstream oss;
    oss << A << B << C << D;
    return oss.str();
}

int SquawkCode::GetAsInt() const
{
    return A * 1000 + B * 100 + C * 10 + D;
}

std::ostream& operator<<(std::ostream& outs, const SquawkCode& s)
{
    outs << s.A << s.B << s.C << s.D;
    return outs;
}

std::istream& operator>>(std::istream& ins, SquawkCode& s)
{
    std::string input;
    ins >> input;

    try
    {
        s.Set(input);
    }
    catch (const std::exception& e)
    {
        ins.setstate(std::ios::failbit);
    }

    return ins;
}

std::string to_string(const SquawkCode& s)
{
    return s.GetString();
}

bool SquawkCode::operator==(const SquawkCode& other) const
{
    return (A == other.A && B == other.B && C == other.C && D == other.D);
}

bool SquawkCode::operator<(const SquawkCode& other) const
{
    return GetAsInt() < other.GetAsInt();
}

Aircraft::Aircraft(/* args */) {}

Aircraft::~Aircraft() {}

void Aircraft::Update(float dt)
{
    float rad = mState.heading * 3.14159265f / 180.f;
    SetPosition(mState.position.Lat + dt * mState.speed * std::sin(rad),
                mState.position.Long - dt * mState.speed * std::cos(rad));
    // ATCOS_LIB_DEBUG("Aircraft: ({}):{},{}", mState.speed, mState.position.Lat,
    //                 mState.position.Long);
}

unsigned int Aircraft::GetFlightLevel() const
{
    return mState.flightLevel;
}

std::string Aircraft::GetSquawkCode() const
{
    return mState.squawkCode.GetString();
}

float Aircraft::GetHeading() const
{
    return mState.heading;
}

float Aircraft::GetSpeed() const
{
    return mState.speed;
}

const AircraftState::_position& Aircraft::GetPosition() const
{
    return mState.position;
}

void Aircraft::SetSquawkCode(const std::string& inputCode)
{
    mState.squawkCode.Set(inputCode);
}

void Aircraft::SetHeading(float h)
{
    if (h >= 360)
        h -= 360;
    else if (h < 0)
        h += 360;
    mState.heading = h;
    NotifyStateChanged();
}

void Aircraft::SetSpeed(float s)
{
    mState.speed = s;
    NotifyStateChanged();
}

void Aircraft::SetPosition(float latitude, float longitude)
{
    mState.position = {latitude, longitude};
    NotifyStateChanged();
}

void Aircraft::SetFlightLevel(unsigned int fl)
{
    mState.flightLevel = fl;
    NotifyStateChanged();
}