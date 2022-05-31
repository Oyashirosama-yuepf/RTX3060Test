#ifndef HOLO_LOG_CONFIG_SINGLE_FILE_CONFIGURE_H_
#define HOLO_LOG_CONFIG_SINGLE_FILE_CONFIGURE_H_

#include <holo/log/config/configure.h>

namespace holo
{
namespace log
{
class SingleFileConfigure : public Configure
{
public:
    SingleFileConfigure(std::string const& name, std::string const& filename) : Configure(name), filename_(filename)
    {
    }

    SingleFileConfigure(YAML::Node const& config_node);
    SingleFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node);

    virtual ~SingleFileConfigure() noexcept
    {
    }

    void SetFilename(std::string const& filename)
    {
        filename_ = filename;
    }

    std::string GetFilename() const
    {
        return filename_;
    }

    void SetOpenMode(std::ios_base::openmode mode)
    {
        mode_ = mode;
    }

    std::ios_base::openmode GetOpenMode() const
    {
        return mode_;
    }

    void SetImmediateFlush(holo::bool_t value)
    {
        immediate_flush_ = value;
    }

    holo::bool_t GetImmediateFlush() const
    {
        return immediate_flush_;
    }

    void SetCreateDirs(holo::bool_t value)
    {
        create_dirs_ = value;
    }

    holo::bool_t GetCreateDirs() const
    {
        return create_dirs_;
    }

private:
    /**
     * @brief parse configure form yaml node
     *
     * @param node YAML::Node
     */
    void parse(YAML::Node const& node);

private:
    std::string             filename_;
    std::ios_base::openmode mode_{std::ios_base::app};
    holo::bool_t            immediate_flush_{true};
    holo::bool_t            create_dirs_{true};
};

}  // namespace log

}  // namespace holo

#endif
