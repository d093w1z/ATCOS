#include "radar.hpp"
#include "log.hpp"
#include <random>

Radar::Radar(/* args */)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> speedDist(0, 15);
    std::uniform_real_distribution<> headingDist(0, 360);

    std::uniform_int_distribution<> squawkDist(0, 7);
    std::uniform_real_distribution<> posXDist(100, 300);
    std::uniform_real_distribution<> posYDist(100, 300);

    ATCOS_LIB_INFO("Radar Initialized!");
    for (int i = 0; i < 5; i++)
    {
        SquawkCode s({
            (unsigned int) squawkDist(gen),
            (unsigned int) squawkDist(gen),
            (unsigned int) squawkDist(gen),
            (unsigned int) squawkDist(gen),
        });
        entities[s] = Aircraft();
        entities[s].SetSquawkCode(s.GetString());
    }
        //ATCOS_LIB_INFO("Aircrafts Added");
    for (auto& [key, value] : entities)
    {
        value.SetFlightLevel(5);
        value.SetHeading(headingDist(gen));
        value.SetSpeed(speedDist(gen));
        value.SetPosition(posXDist(gen), posYDist(gen));
    }
}

Radar::~Radar() {}

std::map<SquawkCode, Aircraft>& Radar::GetEntities()
{
    return entities;
}

void Radar::Update(float dt)
{
    for (auto& [key, value] : entities)
    {
        //value.SetHeading(value.GetHeading() + dt * value.GetSpeed());
        value.Update(dt);
    }
}
