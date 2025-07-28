#include <spdlog/spdlog.h>

class Log
{
   public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetGameLogger() { return sGameLogger; };
    inline static std::shared_ptr<spdlog::logger>& GetLibLogger() { return sLibLogger; };

   private:
    static std::shared_ptr<spdlog::logger> sGameLogger;
    static std::shared_ptr<spdlog::logger> sLibLogger;
};

#define ATCOS_WARN(message) Log::GetGameLogger()->warn(message);
#define ATCOS_DEBUG(message) Log::GetGameLogger()->debug(message);
#define ATCOS_TRACE(message) Log::GetGameLogger()->trace(message);
#define ATCOS_ERROR(message) Log::GetGameLogger()->error(message);
#define ATCOS_INFO(message) Log::GetGameLogger()->info(message);
#define ATCOS_CRITICAL(message) Log::GetGameLogger()->critical(message);
#define ATCOS_LOG(level, message) Log::GetGameLogger()->log(level, message);

#define ATCOS_LIB_WARN(message) Log::GetLibLogger()->warn(message);
#define ATCOS_LIB_DEBUG(message) Log::GetLibLogger()->debug(message);
#define ATCOS_LIB_TRACE(message) Log::GetLibLogger()->trace(message);
#define ATCOS_LIB_ERROR(message) Log::GetLibLogger()->error(message);
#define ATCOS_LIB_INFO(message) Log::GetLibLogger()->info(message);
#define ATCOS_LIB_CRITICAL(message) Log::GetLibLogger()->critical(message);
#define ATCOS_LIB_LOG(level, message) Log::GetLibLogger()->log(level, message);
