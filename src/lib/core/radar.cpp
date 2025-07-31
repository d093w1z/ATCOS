#include "radar.hpp"
#include "log.hpp"
Radar::Radar(/* args */)
{
    ATCOS_LIB_INFO("Radar Initialized!");
    entities.resize(1);
    for (auto& it : entities)
    {
        it.SetFlightLevel(5);
        it.SetHeading(0);
        it.SetSpeed(100);
        it.SetSquawkCode("0033");
        it.SetPosition(200, 200);
    }
}

Radar::~Radar() {}

void Radar::Update(float dt)
{
    for (auto&& it : entities)
    {
        it.SetHeading(it.GetHeading() + dt * it.GetSpeed());
        it.Update(dt);
    }
}
