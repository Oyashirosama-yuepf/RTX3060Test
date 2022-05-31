/*!
 *  \brief map setting
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */
#ifndef HOLO_MAP_COMMON_MAP_SETTINGS_H_
#define HOLO_MAP_COMMON_MAP_SETTINGS_H_

#include <stdio.h> /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDirForYamlConfigureFile _getcwd
#else
#include <unistd.h>
#define GetCurrentDirForYamlConfigureFile getcwd
#endif

#include <memory>
#include <string>

namespace holo
{
namespace map
{
enum class MapVersion
{
    WRONG_VERSION,
    NIHAD_V211,
    NIHAD_V206,
    NIHAD_V206_DEPRECATED,
    SELF_MADE_MAP_RTK,
    SELF_MADE_MAP_RELEASE,
    NIHAD_V300
};

enum class DataSourceType : uint8_t
{
    INVALID_SOURCE,
    NIHAD_HOLO_MIF,
    NIHAD_NDS_SDK
};

class MapSetting
{
public:
    /// Constructor with default path
    MapSetting();

    /// Constructor with specified path
    MapSetting(const std::string& _path);

    /// Reset
    void Reset();

    /// Is GCJ coordinate
    bool IsBias() const
    {
        return bias_;
    }
    std::string GetCoordinateSystem()
    {
        return coordinate_system_;
    }
    /// Set path
    void SetPath(const std::string& _path)
    {
        config_file_ = _path;
    }

    /// Load setings from yml file
    bool LoadSettings();

    bool IsVersion(const MapVersion& _version) const
    {
        return version_ == _version;
    }

    std::string GetMapDataDirectory() const
    {
        return map_data_directory_;
    }

    std::string GetConfigFile() const
    {
        return config_file_;
    }

    DataSourceType GetDataSourceType() const
    {
        return source_type_;
    }

private:
    /// Path to configuration file
    std::string config_file_;
    /// Directory path where all MID MIF files are located
    std::string map_data_directory_;
    /// Map version
    MapVersion version_ = MapVersion::WRONG_VERSION;
    // coordinate system
    // project coordinate system or geographical coordiante system;
    std::string coordinate_system_;
    //  if data is gcj;
    bool bias_ = false;
    // Map source type
    DataSourceType source_type_ = DataSourceType::INVALID_SOURCE;
};

typedef std::shared_ptr<MapSetting> PtrMapSetting;

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_COMMON_MAP_SETTINGS_H_ */
