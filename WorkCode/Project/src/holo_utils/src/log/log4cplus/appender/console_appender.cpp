#include <holo/log/color.h>
#include <holo/log/exception.h>
#include <holo/log/log4cplus/appender/console_appender.h>
#include <holo/log/log4cplus/filter/loglevel_filter.h>
#include <holo/log/log4cplus/layout/pattern_layout.h>
#include <log4cplus/layout.h>
#include <log4cplus/spi/loggingevent.h>
#include <log4cplus/streams.h>
#include <log4cplus/thread/syncprims-pub-impl.h>

namespace holo
{
namespace log
{
namespace log4cplus
{
ConsoleAppender::ConsoleAppender(ConsoleConfigure const& configure)
  : ::log4cplus::ConsoleAppender(configure.GetLogToStderr(), configure.GetImmediateFlush())
  , color_map_{{LogLevel::TRACE, None},     {LogLevel::DEBUG, None},
               {LogLevel::INFO, None},      {LogLevel::WARNING, LightYellow},
               {LogLevel::ERROR, LightRed}, {LogLevel::FATAL, LightPink},
               {LogLevel::OFF, None}}
{
    ConsoleAppender::setName(configure.GetName());
    setThreshold(static_cast<::log4cplus::LogLevel>(configure.GetLevel()));
    ConsoleAppender::setLayout(std::unique_ptr<::log4cplus::Layout>(
        new PatternLayout(configure.GetPattern(), configure.GetPatternFunction())));
    if (configure.GetMaxLevel() < LogLevel::FATAL)
    {
        setFilter(::log4cplus::spi::FilterPtr(new LogLevelFilter(configure.GetLevel(), configure.GetMaxLevel())));
    }
}

void ConsoleAppender::append(::log4cplus::spi::InternalLoggingEvent const& event)
{
    ::log4cplus::thread::MutexGuard guard(getOutputMutex());
    ::log4cplus::tostream&          output = (logToStdErr ? ::log4cplus::tcerr : ::log4cplus::tcout);
    output << color_map_[static_cast<LogLevel>(event.getLogLevel())];
    layout->formatAndAppend(output, event);
    output << None;
    if (immediateFlush)
    {
        (void)output.flush();
    }
}

}  // namespace log4cplus

}  // namespace log

}  // namespace holo
