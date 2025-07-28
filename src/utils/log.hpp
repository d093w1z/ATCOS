#include <spdlog/spdlog.h>

class Log
{
   public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetLogger() { return sLogger; };

   private:
    static std::shared_ptr<spdlog::logger> sLogger;
};