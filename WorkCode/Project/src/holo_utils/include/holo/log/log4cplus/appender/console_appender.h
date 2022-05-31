#ifndef HOLO_LOG_LOG4CPLUS_APPENDER_CONSOLE_APPENDER_H_
#define HOLO_LOG_LOG4CPLUS_APPENDER_CONSOLE_APPENDER_H_

#include <holo/core/types.h>
#include <holo/log/color.h>
#include <holo/log/config/console_configure.h>
#include <log4cplus/consoleappender.h>
#include <unordered_map>

#include "../loglevel.h"

namespace holo
{
namespace log
{
namespace log4cplus
{
class ConsoleAppender : public ::log4cplus::ConsoleAppender
{
public:
    static constexpr holo::uint32_t MAX_COLOR_NUM{17U};

    ConsoleAppender(ConsoleConfigure const& configure);

protected:
    void append(::log4cplus::spi::InternalLoggingEvent const& event) override;

private:
    std::unordered_map<LogLevel, ColorType> color_map_;
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo
#endif
