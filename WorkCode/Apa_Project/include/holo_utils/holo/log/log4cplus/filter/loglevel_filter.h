#ifndef HOLO_LOG_LOG4CPLUS_FILTER_LOG_LEVEL_FILTER_H_
#define HOLO_LOG_LOG4CPLUS_FILTER_LOG_LEVEL_FILTER_H_

#include <holo/core/types.h>
#include <holo/log/exception.h>
#include <log4cplus/spi/filter.h>
#include <log4cplus/spi/loggingevent.h>

#include "../loglevel.h"

namespace holo
{
namespace log
{
namespace log4cplus
{
class LogLevelFilter : public ::log4cplus::spi::Filter
{
public:
    using Base = ::log4cplus::spi::Filter;
    LogLevelFilter(LogLevel const level) : Base{}, min_level_{level}, max_level_{level}
    {
    }

    LogLevelFilter(LogLevel const min_level, LogLevel const max_level)
      : Base{}, min_level_{min_level}, max_level_{max_level}
    {
    }

    ::log4cplus::spi::FilterResult decide(::log4cplus::spi::InternalLoggingEvent const& event) const override
    {
        LogLevel const                       level{static_cast<LogLevel>(event.getLogLevel())};
        ::log4cplus::spi::FilterResult const result{((min_level_ <= level) && (max_level_ >= level)) ?
                                                        ::log4cplus::spi::FilterResult::ACCEPT :
                                                        ::log4cplus::spi::FilterResult::DENY};
        return result;
    }

private:
    LogLevelFilter() = delete;
    LogLevel min_level_;
    LogLevel max_level_;
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo
#endif
