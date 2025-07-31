#include "log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Log::sGameLogger;
std::shared_ptr<spdlog::logger> Log::sLibLogger;

void Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %L: %v%$");
    sGameLogger = spdlog::stdout_color_mt("ATCOS");
    sGameLogger->set_level(spdlog::level::trace);
    sLibLogger = spdlog::stdout_color_mt("ATCOS_lib");
    sLibLogger->set_level(spdlog::level::trace);
}