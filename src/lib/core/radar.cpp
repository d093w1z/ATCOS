#include "radar.hpp"
#include <memory>

Radar::Radar() {}

Radar::~Radar() {}

std::map<SquawkCode, std::shared_ptr<Aircraft>>& Radar::GetEntities()
{
    return entities;
}

void Radar::Update(float dt)
{
    for (auto& [key, value] : entities)
    {
        // value.SetHeading(value.GetHeading() + dt * value.GetSpeed());
        value->Update(dt);
    }
}
