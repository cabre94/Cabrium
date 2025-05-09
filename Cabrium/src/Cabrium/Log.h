#pragma once

#include <memory>

#include "spdlog/spdlog.h"

#include "Core.h"

namespace cabrium {

class CBRM_API Log {
public:
    // Log();
    //~Log();

    static void init();

    inline static std::shared_ptr<spdlog::logger> &getCoreLogger() { return s_core_logger; }
    inline static std::shared_ptr<spdlog::logger> &getClientLogger() { return s_client_logger; }

private:
    static std::shared_ptr<spdlog::logger> s_core_logger;
    static std::shared_ptr<spdlog::logger> s_client_logger;
};

} // namespace cabrium

#define CBRM_CORE_TRACE(...)    ::cabrium::Log::getCoreLogger()->trace(__VA_ARGS__)
#define CBRM_CORE_DEBUG(...)    ::cabrium::Log::getCoreLogger()->debug(__VA_ARGS__)
#define CBRM_CORE_INFO(...)     ::cabrium::Log::getCoreLogger()->info(__VA_ARGS__)
#define CBRM_CORE_WARN(...)     ::cabrium::Log::getCoreLogger()->warn(__VA_ARGS__)
#define CBRM_CORE_ERROR(...)    ::cabrium::Log::getCoreLogger()->error(__VA_ARGS__)
#define CBRM_CORE_CRITICAL(...) ::cabrium::Log::getCoreLogger()->critical(__VA_ARGS__)

#define CBRM_TRACE(...)    ::cabrium::Log::getClientLogger()->trace(__VA_ARGS__)
#define CBRM_DEBUG(...)    ::cabrium::Log::getClientLogger()->debug(__VA_ARGS__)
#define CBRM_INFO(...)     ::cabrium::Log::getClientLogger()->info(__VA_ARGS__)
#define CBRM_WARN(...)     ::cabrium::Log::getClientLogger()->warn(__VA_ARGS__)
#define CBRM_ERROR(...)    ::cabrium::Log::getClientLogger()->error(__VA_ARGS__)
#define CBRM_CRITICAL(...) ::cabrium::Log::getClientLogger()->critical(__VA_ARGS__)