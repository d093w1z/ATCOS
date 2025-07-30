#include <SFML/Graphics.hpp>

class ATCOSApp
{
   private:
    bool IsRunning = false;
    sf::RenderWindow mWindow;

   public:
    ATCOSApp();
    ~ATCOSApp();

    void RunLoop();
};
