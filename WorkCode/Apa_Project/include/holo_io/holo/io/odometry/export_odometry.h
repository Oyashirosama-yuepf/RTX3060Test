#ifndef HOLO_IO_EXPORT_ODOMETRY_H_
#define HOLO_IO_EXPORT_ODOMETRY_H_

#include <holo/common/odometry.h>
#include <holo/io/io.h>
#include <holo/utils/yaml.h>

namespace holo_io
{
class ExportOdometry
{
public:
    ExportOdometry(const std::string& config_file, const std::string& output_path);

    template<typename T>
    void SetOutput(const std::string& topic_name, T& input);

protected:
    std::vector<std::string>   topic_name_list_;
    std::vector<std::ofstream> file_path_list_;
    std::vector<holo::bool_t>  need_rotate_list_;

private:
    bool          LoadConfigFile(const std::string& config_file, const std::string& output_path);
    std::ofstream InitFile(const std::string& file_path);
};

class ExportOdometryFromRecord : public ExportOdometry
{
public:
    ExportOdometryFromRecord(const std::string& config_file, const std::string& output_path)
      : ExportOdometry(config_file, output_path)
    {
    }
};

}  // namespace holo_io

#endif
