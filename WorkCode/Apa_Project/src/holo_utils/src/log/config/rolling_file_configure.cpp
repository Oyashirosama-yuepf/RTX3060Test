#include <holo/log/config/rolling_file_configure.h>

namespace holo
{
namespace log
{
RollingFileConfigure::RollingFileConfigure(YAML::Node const& config_node) : Configure(config_node)
{
    parse(config_node);
}

RollingFileConfigure::RollingFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node)
  : Configure(root_node)
{
    Configure::parse(config_node);
    parse(config_node);
}

void RollingFileConfigure::parse(YAML::Node const& config_node)
{
    std::string name    = extractValue<std::string>(config_node, std::string("name"));
    filename_           = extractValue<std::string>(config_node, std::string("file"));
    create_dirs_        = extractValue<holo::bool_t>(config_node, std::string("create_dirs"), create_dirs_);
    immediate_flush_    = extractValue<holo::bool_t>(config_node, std::string("immediate_flush"), immediate_flush_);
    max_backup_index_   = extractValue<holo::uint32_t>(config_node, std::string("backup"), max_backup_index_);
    holo::uint32_t size = extractValue<holo::uint32_t>(config_node, std::string("max_size"), 20U);

    max_file_size_ = size * 1024 * 1024;

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

