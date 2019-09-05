#ifndef JED_LOG_LOGGER_HPP
#define JED_LOG_LOGGER_HPP

#define SPDLOG_NO_NAME
#define SPDLOG_NO_ATOMIC_LEVELS
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/file_sinks.h"

namespace log
{
std::shared_ptr<spdlog::logger> get_logger();

std::shared_ptr<spdlog::sinks::stdout_sink_mt> get_console_sink();

std::shared_ptr<spdlog::sinks::simple_file_sink_mt> get_file_sink();

}; // namespace log

#define LOG_TRACE(...)                   \
    do                                   \
    {                                    \
        auto logger = log::get_logger(); \
        logger->trace(__VA_ARGS__);      \
    } while (0)

#define LOG_DEBUG(...)                   \
    do                                   \
    {                                    \
        auto logger = log::get_logger(); \
        logger->debug(__VA_ARGS__);      \
    } while (0)

#define LOG_INFO(...)                    \
    do                                   \
    {                                    \
        auto logger = log::get_logger(); \
        logger->info(__VA_ARGS__);       \
    } while (0)

#define LOG_WARN(...)                    \
    do                                   \
    {                                    \
        auto logger = log::get_logger(); \
        logger->warn(__VA_ARGS__);       \
    } while (0)

#define LOG_ERROR(...)                   \
    do                                   \
    {                                    \
        auto logger = log::get_logger(); \
        logger->error(__VA_ARGS__);      \
    } while (0)

#define LOG_CRITICAL(...)                \
    do                                   \
    {                                    \
        auto logger = log::get_logger(); \
        logger->critical(__VA_ARGS__);   \
    } while (0)

#endif

#ifdef JED_LOG_IMPLEMENTATION

namespace log
{
std::shared_ptr<spdlog::sinks::stdout_sink_mt> get_console_sink()
{
    static auto sink = std::make_shared<spdlog::sinks::stdout_sink_mt>();

    return sink;
}

std::shared_ptr<spdlog::sinks::simple_file_sink_mt> get_file_sink()
{
    static auto sink = std::make_shared<spdlog::sinks::simple_file_sink_mt>("log.txt");

    return sink;
}

std::shared_ptr<spdlog::logger> get_logger()
{
    static auto logger = spdlog::create("log", {get_console_sink(), get_file_sink()});

    return logger;
}
}; // namespace log

#endif