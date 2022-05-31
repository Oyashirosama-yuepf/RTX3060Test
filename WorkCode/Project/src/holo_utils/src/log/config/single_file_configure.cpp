#include <holo/log/config/single_file_configure.h>

namespace holo
{
namespace log
{
SingleFileConfigure::SingleFileConfigure(YAML::Node const& config_node) : Configure(config_node)
{
    parse(config_node);
}

SingleFileConfigure::SingleFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node)
  : Configure(root_node)
{
    Configure::parse(config_node);
    parse(config_node);
}

void SingleFileConfigure::parse(YAML::Node const& config_node)
{
    std::string name = extractValue<std::string>(config_node, std::string("name"));
    filename_        = extractValue<std::string>(config_node, std::string("file"));
    create_dirs_     = extractValue<holo::bool_t>(config_node, std::string("create_dirs"), create_dirs_);
    immediate_flush_ = extractValue<holo::bool_t>(config_node, std::string("immediate_flush"), immediate_flush_);

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

