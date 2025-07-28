#include <iostream>
#include <sstream>
#include <string>

#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

class SquawkCode
{
   private:
    unsigned int A = 0, B = 0, C = 0, D = 0;

   public:
    SquawkCode() = default;

    SquawkCode(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

    bool IsValid() const;

    static bool IsValid(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

    void Set(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

    void Set(const std::string& input);

    std::string GetString() const;

    int GetAsInt() const;

    friend std::ostream& operator<<(std::ostream& outs, const SquawkCode& s);

    friend std::istream& operator>>(std::istream& ins, SquawkCode& s);

    friend std::string to_string(const SquawkCode& s);
};

struct AircraftState
{
    SquawkCode squawkCode;
    float heading = 0;
    uint flightLevel = 0;
};

class Aircraft
{
   private:
    AircraftState mState;

   public:
    Aircraft(/* args */);
    ~Aircraft();

    void SetSquawkCode();
    std::string GetSquawkCode() const;

    void SetHeading();
    float GetHeading() const;

    void SetFlightLevel();
    uint GetFlightLevel() const;
};
#endif