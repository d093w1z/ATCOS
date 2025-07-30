#include <spdlog/spdlog.h>

class Log
{
   public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetGameLogger()
    {
        return sGameLogger;
    };
    inline static std::shared_ptr<spdlog::logger>& GetLibLogger()
    {
        return sLibLogger;
    };

   private:
    static std::shared_ptr<spdlog::logger> sGameLogger;
    static std::shared_ptr<spdlog::logger> sLibLogger;
};

#define ATCOS_WARN(...) Log::GetGameLogger()->warn(__VA_ARGS__)
#define ATCOS_DEBUG(...) Log::GetGameLogger()->debug(__VA_ARGS__)
#define ATCOS_TRACE(...) Log::GetGameLogger()->trace(__VA_ARGS__)
#define ATCOS_ERROR(...) Log::GetGameLogger()->error(__VA_ARGS__)
#define ATCOS_INFO(...) Log::GetGameLogger()->info(__VA_ARGS__)
#define ATCOS_CRITICAL(...) Log::GetGameLogger()->critical(__VA_ARGS__)
#define ATCOS_LOG(level, ...) Log::GetGameLogger()->log(level, __VA_ARGS__)

#define ATCOS_LIB_WARN(...) Log::GetLibLogger()->warn(__VA_ARGS__)
#define ATCOS_LIB_DEBUG(...) Log::GetLibLogger()->debug(__VA_ARGS__)
#define ATCOS_LIB_TRACE(...) Log::GetLibLogger()->trace(__VA_ARGS__)
#define ATCOS_LIB_ERROR(...) Log::GetLibLogger()->error(__VA_ARGS__)
#define ATCOS_LIB_INFO(...) Log::GetLibLogger()->info(__VA_ARGS__)
#define ATCOS_LIB_CRITICAL(...) Log::GetLibLogger()->critical(__VA_ARGS__)
#define ATCOS_LIB_LOG(level, ...) Log::GetLibLogger()->log(level, __VA_ARGS__)
