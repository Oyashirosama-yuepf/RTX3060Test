#include <holo/log/config/daily_rolling_file_configure.h>
#include <algorithm>

namespace holo
{
namespace log
{
DailyRollingFileConfigure::DailyRollingFileConfigure(YAML::Node const& config_node) : Configure(config_node)
{
    parse(config_node);
}

DailyRollingFileConfigure::DailyRollingFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node)
  : Configure(root_node)
{
    Configure::parse(config_node);
    parse(config_node);
}

void DailyRollingFileConfigure::parse(YAML::Node const& config_node)
{
    std::string name     = extractValue<std::string>(config_node, std::string("name"));
    filename_            = extractValue<std::string>(config_node, std::string("file"));
    filename_pattern_    = extractValue<std::string>(config_node, std::string("filename_pattern"), filename_pattern_);
    std::string schedule = extractValue<std::string>(config_node, std::string("schedule"), "DAILY");
    create_dirs_         = extractValue<holo::bool_t>(config_node, std::string("create_dirs"), create_dirs_);
    immediate_flush_     = extractValue<holo::bool_t>(config_node, std::string("immediate_flush"), immediate_flush_);
    max_backup_index_    = extractValue<holo::uint32_t>(config_node, std::string("backup"), max_backup_index_);
    roll_on_close_       = extractValue<holo::bool_t>(config_node, std::string("roll_on_close"), roll_on_close_);

    (void)std::transform(schedule.begin(), schedule.end(), schedule.begin(), ::toupper);
    if (schedule_map_.count(schedule) > 0U)
    {
        schedule_ = schedule_map_[schedule];
    }
    else
    {
        ScheduleStringException e{config_node["schedule"].Mark()};
        throw e;
    }

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

