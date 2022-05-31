#include <holo/log/config/console_configure.h>
#include <algorithm>

namespace holo
{
namespace log
{
ConsoleConfigure::ConsoleConfigure(YAML::Node const& config_node) : Configure(config_node)
{
    parse(config_node);
}

ConsoleConfigure::ConsoleConfigure(YAML::Node const& root_node, YAML::Node const& config_node) : Configure(root_node)
{
    Configure::parse(config_node);
    parse(config_node);
}

void ConsoleConfigure::parse(YAML::Node const& config_node)
{
    std::string name        = extractValue<std::string>(config_node, std::string("name"));
    log_to_stderr_          = extractValue<holo::bool_t>(config_node, std::string("log_to_stderr"), log_to_stderr_);
    immediate_flush_        = extractValue<holo::bool_t>(config_node, std::string("immediate_flush"), immediate_flush_);
    std::string trace_color = extractValue<std::string>(config_node, std::string("trace_color"), "NONE");
    std::string debug_color = extractValue<std::string>(config_node, std::string("debug_color"), "NONE");
    std::string info_color  = extractValue<std::string>(config_node, std::string("info_color"), "NONE");
    std::string warn_color  = extractValue<std::string>(config_node, std::string("warning_color"), "LIGHT_YELLOW");
    std::string error_color = extractValue<std::string>(config_node, std::string("error_color"), "LIGHT_RED");
    std::string fatal_color = extractValue<std::string>(config_node, std::string("fatal_color"), "LIGHT_PINK");

    std::string spaces(" \t\f\v\n\r");
    std::size_t found = name.find_first_not_of(spaces);
    if (found == std::string::npos)
    {
        ConfigureNameException e{config_node["name"].Mark()};
        throw e;
    }
    setName(name);

    std::unordered_map<std::string, Color> string_to_color{
        {"BLACK", Color::BLACK},   {"LIGHT_BLACK", Color::LIGHT_BLACK},
        {"RED", Color::RED},       {"LIGHT_RED", Color::LIGHT_RED},
        {"GREEN", Color::GREEN},   {"LIGHT_GREEN", Color::LIGHT_GREEN},
        {"YELLOW", Color::YELLOW}, {"LIGHT_YELLOW", Color::LIGHT_YELLOW},
        {"BLUE", Color::BLUE},     {"LIGHT_BLUE", Color::LIGHT_BLUE},
        {"PINK", Color::PINK},     {"LIGHT_PINK", Color::LIGHT_PINK},
        {"CYAN", Color::CYAN},     {"LIGHT_CYAN", Color::LIGHT_CYAN},
        {"WHITE", Color::WHITE},   {"LIGHT_WHITE", Color::LIGHT_WHITE},
        {"NONE", Color::NONE}};

    (void)std::transform(trace_color.begin(), trace_color.end(), trace_color.begin(), ::toupper);
    if (string_to_color.count(trace_color) > 0U)
    {
        color_map_[LogLevel::TRACE] = string_to_color[trace_color];
    }

    (void)std::transform(debug_color.begin(), debug_color.end(), debug_color.begin(), ::toupper);
    if (string_to_color.count(debug_color) > 0U)
    {
        color_map_[LogLevel::DEBUG] = string_to_color[debug_color];
    }

    (void)std::transform(info_color.begin(), info_color.end(), info_color.begin(), ::toupper);
    if (string_to_color.count(info_color) > 0U)
    {
        color_map_[LogLevel::INFO] = string_to_color[info_color];
    }

    (void)std::transform(warn_color.begin(), warn_color.end(), warn_color.begin(), ::toupper);
    if (string_to_color.count(warn_color) > 0U)
    {
        color_map_[LogLevel::WARNING] = string_to_color[warn_color];
    }

    (void)std::transform(error_color.begin(), error_color.end(), error_color.begin(), ::toupper);
    if (string_to_color.count(error_color) > 0U)
    {
        color_map_[LogLevel::ERROR] = string_to_color[error_color];
    }

    (void)std::transform(fatal_color.begin(), fatal_color.end(), fatal_color.begin(), ::toupper);
    if (string_to_color.count(fatal_color) > 0U)
    {
        color_map_[LogLevel::FATAL] = string_to_color[fatal_color];
    }
}

}  // namespace log

}  // namespace holo

