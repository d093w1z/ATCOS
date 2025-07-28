#include <vector>

#include "aircraft.hpp"

class Radar
{
   private:
    std::vector<Aircraft*> entities;

   public:
    Radar(/* args */);
    ~Radar();
};
