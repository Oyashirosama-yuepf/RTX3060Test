#include <holo/log/log4cplus/layout/pattern_layout.h>
#include <holo/log/log4cplus/loglevel.h>
#include <log4cplus/spi/loggingevent.h>

#include <holo/os/utils.h>
#include <sys/time.h>
#include <iomanip>
#include <iostream>

namespace holo
{
namespace log
{
namespace log4cplus
{
static holo::char_t const TRACE_STRING[]{"TRACE"};
static holo::char_t const DEBUG_STRING[]{"DEBUG"};
static holo::char_t const INFO_STRING[]{" INFO"};
static holo::char_t const WARN_STRING[]{" WARN"};
static holo::char_t const ERROR_STRING[]{"ERROR"};
static holo::char_t const FATAL_STRING[]{"FATAL"};
static holo::char_t const OFF_STRING[]{"  OFF"};
static holo::char_t const NOTSET_STRING[]{"NOTSET"};
static holo::char_t const UNKNOWN_STRING[]{"UNKNOWN"};

PatternLayout::PatternLayout(std::string const& pattern, Configure::PatternCallback function)
  : ::log4cplus::PatternLayout{pattern}, function_{function}
{
}

PatternLayout::~PatternLayout()
{
}

void PatternLayout::formatAndAppend(::log4cplus::tostream& output, ::log4cplus::spi::InternalLoggingEvent const& event)
{
    static holo::int32_t              pid = holo::os::Utils::GetPid();
    static thread_local holo::int32_t tid = holo::os::Utils::GetTid();
    if (function_)
    {
        output << function_(event.getFile(), event.getLine(), static_cast<LogLevel>(event.getLogLevel()), pid, tid);
        output << event.getMessage();
        output << std::endl;
    }
    else
    {
        appendTime(output);
        output << "PID:" << pid << ' ';
        output << "TID:" << tid << ' ';
        output << event.getFile() << ' ';
        output << event.getLine() << ' ';
        output << logLevelToString(event.getLogLevel());
        output << ']';
        output << event.getMessage();
        output << std::endl;
    }
}

void PatternLayout::appendTime(::log4cplus::tostream& output)
{
    struct timeval tv;
    struct ::tm    tm_time;

    (void)gettimeofday(&tv, NULL);
    (void)localtime_r(&tv.tv_sec, &tm_time);

    (void)output.fill('0');
    output << std::setw(4) << 1900 + tm_time.tm_year << std::setw(2) << 1 + tm_time.tm_mon << std::setw(2)
           << tm_time.tm_mday << ' ' << std::setw(2) << tm_time.tm_hour << ':' << std::setw(2) << tm_time.tm_min << ':'
           << std::setw(2) << tm_time.tm_sec << '.' << std::setw(6) << tv.tv_usec << ' ';
}

holo::char_t const* PatternLayout::logLevelToString(::log4cplus::LogLevel level)
{
    switch (level)
    {
        case ::log4cplus::OFF_LOG_LEVEL:
            return OFF_STRING;
        case ::log4cplus::FATAL_LOG_LEVEL:
            return FATAL_STRING;
        case ::log4cplus::ERROR_LOG_LEVEL:
            return ERROR_STRING;
        case ::log4cplus::WARN_LOG_LEVEL:
            return WARN_STRING;
        case ::log4cplus::INFO_LOG_LEVEL:
            return INFO_STRING;
        case ::log4cplus::DEBUG_LOG_LEVEL:
            return DEBUG_STRING;
        case ::log4cplus::TRACE_LOG_LEVEL:
            return TRACE_STRING;
        case ::log4cplus::NOT_SET_LOG_LEVEL:
            return NOTSET_STRING;
    };

    return UNKNOWN_STRING;
}

}  // namespace log4cplus

}  // namespace log

}  // namespace holo
