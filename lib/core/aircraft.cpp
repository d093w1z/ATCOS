#include "aircraft.hpp"

SquawkCode::SquawkCode(unsigned int a, unsigned int b, unsigned int c, unsigned int d)
{
    Set(a, b, c, d);
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

Aircraft::Aircraft(/* args */) {}

Aircraft::~Aircraft() {}

uint Aircraft::GetFlightLevel() const
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