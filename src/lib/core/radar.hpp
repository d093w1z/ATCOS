#pragma once
#include <vector>

#include "aircraft.hpp"

class Radar
{
   public:
    std::vector<Aircraft> entities;

   public:
    Radar(/* args */);
    ~Radar();
    void Update(float);
};
