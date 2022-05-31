#include <holo/metadata/sensors/camera/image_structure_type_description.h>
#include <holo/metadata/sensors/format/lidar_scan_type_description.h>
#include <holo/metadata/sensors/format/packed_data_type_description.h>
#include <holo/metadata/sensors/lidar/livox/livox_format_type_description.h>
#include <holo/metadata/sensors/lidar/livox/livox_hap_format_type_description.h>
#include <holo/metadata/sensors/lidar/pandar128/pandar128_format_type_description.h>
#include <holo/metadata/sensors/lidar/rsbpearl/rsbpearl_format_type_description.h>
#include <holo/metadata/sensors/lidar/rsm1/rsm1_format_type_description.h>

#include <sys/stat.h>
#include <fstream>
#include <map>

static std::string version = "v0_7";

static std::map<std::string, holo::metadata::TypeDescription::PtrType> td_map = {
    {version + "/sensors/camera/ImagePacket",
     holo::metadata::TypeDescriptionResolver<holo::sensors::camera::ImagePacket>::Get()},
    {version + "/sensors/lidar/livox/RawLivoxPacket", holo::metadata::TypeDescriptionResolver<RawLivoxPacket>::Get()},
    {version + "/sensors/lidar/livox/RawLivoxHapPacket",
     holo::metadata::TypeDescriptionResolver<RawLivoxHapPacket, 1U, true>::Get()},
    {version + "/sensors/lidar/pandar128/RawPandar128MsopPacket",
     holo::metadata::TypeDescriptionResolver<RawPandar128MsopPacket, 1U, true>::Get()},
    {version + "/sensors/lidar/rsbpearl/RawRsbpMsopPacket",
     holo::metadata::TypeDescriptionResolver<RawRsbpMsopPacket, 1U, true>::Get()},
    {version + "/sensors/lidar/rsm1/RawRsm1MsopPacket",
     holo::metadata::TypeDescriptionResolver<RawRsm1MsopPacket, 1U, true>::Get()},
    {version + "/sensors/format/LidarScan",
     holo::metadata::TypeDescriptionResolver<holo::sensors::format::LidarScan<0U>, 4U, true>::Get()},
    {version + "/sensors/format/SensorCompressedPacket",
     holo::metadata::TypeDescriptionResolver<holo::sensors::format::SensorCompressedPacket<0U>, 4U, true>::Get()}};

int createDirectory(std::string const& relpath)
{
    size_t end = 0;
    while (end != std::string::npos)
    {
        end     = relpath.find_first_of("/", end + 1);
        int ret = mkdir(relpath.substr(0, end).c_str(), 0755);
        if (ret != 0)
        {
            if (errno != EEXIST)
            {
                return -1;
            }
            else
            {
                struct stat s;
                if (stat(relpath.substr(0, end).c_str(), &s) == 0)
                {
                    if (s.st_mode & S_IFDIR)
                    {
                        continue;
                    }
                    else
                    {
                        return -2;
                    }
                }
                else
                {
                    return -3;
                }
            }
        }
    }
    return 0;
}

int main()
{
    for (auto const& value : td_map)
    {
        std::string relpath = "metadata/" + value.first + ".yaml";
        if (relpath.find_last_of("/") != std::string::npos)
        {
            if (createDirectory(relpath.substr(0, relpath.find_last_of("/"))) != 0)
            {
                continue;
            }
        }
        std::ofstream of;
        of.open(relpath);
        of << value.second->ToYaml() << std::endl;
        of.close();
    }
    return 0;
}
