#pragma once
#include <map>

#include "aircraft.hpp"

class Radar
{
   private:
    std::map<SquawkCode, Aircraft> entities;

   public:
    Radar(/* args */);
    ~Radar();
    [[nodiscard]] std::map<SquawkCode, Aircraft>& GetEntities();
    void Update(float);
};
