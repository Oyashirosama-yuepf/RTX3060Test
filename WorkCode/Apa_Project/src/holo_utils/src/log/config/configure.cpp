#include <holo/log/config/configure.h>
#include <algorithm>

namespace holo
{
namespace log
{
Configure::Configure(std::string const& name)
  : name_{name}
  , pattern_{HOLO_LOG_DEFAULT_PATTERN}
  , level_{LogLevel::ALL}
  , max_level_{LogLevel::FATAL}
  , async_{false}
  , async_queue_len_{DEFAULT_ASYNC_QUEUE_LEN}
  , function_{nullptr}
  , level_map_{{"ALL", LogLevel::ALL},     {"TRACE", LogLevel::TRACE},     {"DEBUG", LogLevel::DEBUG},
               {"INFO", LogLevel::INFO},   {"WARNING", LogLevel::WARNING}, {"ERROR", LogLevel::ERROR},
               {"FATAL", LogLevel::FATAL}, {"OFF", LogLevel::OFF}}
{
}

Configure::Configure(YAML::Node const& node)
  : name_{}
  , pattern_{HOLO_LOG_DEFAULT_PATTERN}
  , level_{LogLevel::ALL}
  , max_level_{LogLevel::FATAL}
  , async_{false}
  , async_queue_len_{DEFAULT_ASYNC_QUEUE_LEN}
  , function_{nullptr}
  , level_map_{{"ALL", LogLevel::ALL},     {"TRACE", LogLevel::TRACE},     {"DEBUG", LogLevel::DEBUG},
               {"INFO", LogLevel::INFO},   {"WARNING", LogLevel::WARNING}, {"ERROR", LogLevel::ERROR},
               {"FATAL", LogLevel::FATAL}, {"OFF", LogLevel::OFF}}
{
    parse(node);
}

void Configure::parse(YAML::Node const& node)
{
    std::string level     = extractValue<std::string>(node, std::string("level"), "DEBUG");
    std::string max_level = extractValue<std::string>(node, std::string("max_level"), "FATAL");
    pattern_              = extractValue<std::string>(node, std::string("pattern"), pattern_);
    async_                = extractValue<holo::bool_t>(node, std::string("async"), async_);
    async_queue_len_      = extractValue<holo::uint32_t>(node, std::string("async_queue_len"), async_queue_len_);

    (void)std::transform(level.begin(), level.end(), level.begin(), ::toupper);
    if (level_map_.count(level) > 0U)
    {
        level_ = level_map_[level];
    }
    else
    {
        LogLevelStringException e{node["level"].Mark()};
        throw e;
    }

    (void)std::transform(max_level.begin(), max_level.end(), max_level.begin(), ::toupper);
    if (level_map_.count(max_level) > 0U)
    {
        max_level_ = level_map_[max_level];
    }
    else
    {
        LogLevelStringException e{node["max_level"].Mark()};
        throw e;
    }
}

}  // namespace log

}  // namespace holo

