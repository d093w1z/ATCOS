#include <functional>
#include <iostream>
#include <string>

#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

class SquawkCode
{
   private:
    unsigned int A = 0, B = 0, C = 0, D = 0;

   public:
    SquawkCode() = default;

    SquawkCode(const std::string& input);

    SquawkCode(const char* input);

    SquawkCode(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

    [[nodiscard]] bool IsValid() const;

    [[nodiscard]] static bool IsValid(unsigned int a, unsigned int b, unsigned int c,
                                      unsigned int d);

    void Set(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

    void Set(const std::string& input);

    [[nodiscard]] std::string GetString() const;

    [[nodiscard]] int GetAsInt() const;

    bool operator==(const SquawkCode& other) const;
    bool operator<(const SquawkCode& other) const;

    friend std::ostream& operator<<(std::ostream& outs, const SquawkCode& s);

    friend std::istream& operator>>(std::istream& ins, SquawkCode& s);

    friend std::string to_string(const SquawkCode& s);
};

struct AircraftState
{
    SquawkCode squawkCode;
    float speed = 0;
    float heading = 0;
    unsigned int flightLevel = 0;
    struct _position
    {
        float Lat = 0;
        float Long = 0;
    } position;
};

struct AircraftTargetState
{
    float speed = 0;
    float heading = 0;
    unsigned int flightLevel = 0;
};

class Aircraft
{
   public:
    AircraftState mState;
    AircraftTargetState mTargetState;
    std::vector<std::function<void(const AircraftState&)>> m_onStateChanged;

    void NotifyStateChanged()
    {
        update();
    }

   public:
    Aircraft(/* args */);
    virtual ~Aircraft() = default;

    void Update(float);
    virtual void update() = 0;

    void SetSquawkCode(const std::string&);
    [[nodiscard]] std::string GetSquawkCode() const;

    void SetHeading(float);
    [[nodiscard]] float GetHeading() const;

    void SetSpeed(float);
    [[nodiscard]] float GetSpeed() const;

    void SetFlightLevel(unsigned int);
    [[nodiscard]] unsigned int GetFlightLevel() const;

    void SetTargetHeading(float);
    [[nodiscard]] float GetTargetHeading() const;

    void SetTargetSpeed(float);
    [[nodiscard]] float GetTargetSpeed() const;

    void SetTargetFlightLevel(unsigned int);
    [[nodiscard]] unsigned int GetTargetFlightLevel() const;

    void SetPosition(float, float);
    [[nodiscard]] const AircraftState::_position& GetPosition() const;
};
#endif