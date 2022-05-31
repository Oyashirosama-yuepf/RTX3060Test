#include <holo/log/config/time_based_rolling_file_configure.h>

namespace holo
{
namespace log
{
TimeBasedRollingFileConfigure::TimeBasedRollingFileConfigure(YAML::Node const& config_node) : Configure(config_node)
{
    parse(config_node);
}

TimeBasedRollingFileConfigure::TimeBasedRollingFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node)
  : Configure(root_node)
{
    Configure::parse(config_node);
    parse(config_node);
}

void TimeBasedRollingFileConfigure::parse(YAML::Node const& config_node)
{
    std::string name  = extractValue<std::string>(config_node, std::string("name"));
    filename_         = extractValue<std::string>(config_node, std::string("file"));
    filename_pattern_ = extractValue<std::string>(config_node, std::string("filename_pattern"), filename_pattern_);
    create_dirs_      = extractValue<holo::bool_t>(config_node, std::string("create_dirs"), create_dirs_);
    immediate_flush_  = extractValue<holo::bool_t>(config_node, std::string("immediate_flush"), immediate_flush_);
    max_history_      = extractValue<holo::uint32_t>(config_node, std::string("max_history"), max_history_);
    clean_history_on_start_ =
        extractValue<holo::bool_t>(config_node, std::string("clean_history_on_start"), clean_history_on_start_);
    roll_on_close_ = extractValue<holo::bool_t>(config_node, std::string("roll_on_close"), roll_on_close_);

    std::string spaces(" \t\f\v\n\r");
    std::size_t found = name.find_first_not_of(spaces);
    if (found == std::string::npos)
    {
        ConfigureNameException e{config_node["name"].Mark()};
        throw e;
    }
    setName(name);

    found = filename_.find_first_not_of(spaces);
    if (found == std::string::npos)
    {
        FileNameNotSetException e{config_node["file"].Mark()};
        throw e;
    }
}

}  // namespace log

}  // namespace holo

