#ifndef HOLO_LOG_LOG4CPLUS_LAYOUT_PATTERN_LAYOUT_H_
#define HOLO_LOG_LOG4CPLUS_LAYOUT_PATTERN_LAYOUT_H_

#include <holo/core/types.h>
#include <holo/log/configure.h>
#include <log4cplus/layout.h>

namespace holo
{
namespace log
{
namespace log4cplus
{
class PatternLayout : public ::log4cplus::PatternLayout
{
public:
    static constexpr holo::char_t const* SIMPLEST_PATTERN_LAYOUT{"%m%n"};
    PatternLayout(std::string const&         pattern  = std::string{SIMPLEST_PATTERN_LAYOUT},
                  Configure::PatternCallback function = nullptr);

    ~PatternLayout() noexcept override;

    void formatAndAppend(::log4cplus::tostream& output, ::log4cplus::spi::InternalLoggingEvent const& event) override;

private:
    PatternLayout(PatternLayout const&) = delete;
    PatternLayout(PatternLayout&&)      = delete;
    PatternLayout& operator=(PatternLayout const&) = delete;
    PatternLayout& operator=(PatternLayout&&) = delete;

    void                appendTime(::log4cplus::tostream& output);
    holo::char_t const* logLevelToString(::log4cplus::LogLevel level);

private:
    Configure::PatternCallback function_{nullptr};
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo
#endif
