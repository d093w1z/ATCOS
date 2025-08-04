#pragma once
#include <map>
#include <memory>

#include "aircraft.hpp"

class Radar
{
   private:
    std::map<SquawkCode, std::shared_ptr<Aircraft>> entities;

   public:
    Radar(/* args */);
    ~Radar();
    [[nodiscard]] std::map<SquawkCode, std::shared_ptr<Aircraft>>& GetEntities();
    void Update(float);
};
