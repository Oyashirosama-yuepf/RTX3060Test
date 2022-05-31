#ifndef HOLO_IO_COMMON_GNSS_PVT_H_
#define HOLO_IO_COMMON_GNSS_PVT_H_

#include <holo/utils/yaml.h>
#include <holo/io/utils/utils.h>
#include <holo/io/common/timestamp.h>
#include <holo/io/common/coordinate.h>
#include <holo/common/gnss_pvt.h>

namespace YAML
{
template <>
struct convert<holo::common::GnssPvt>
{
    using ValueType = holo::common::GnssPvt;
    using Timestamp = holo::common::Timestamp;
    using Coordinate = holo::common::Coordinate;
    using Mode = ValueType::Mode;

    static std::vector<std::pair<std::string, Mode> > const& StringTypePairs() noexcept
    {
        static const std::vector<std::pair<std::string, Mode> > mode_type_str =    
        {
            {"NO_POSITION"   ,Mode::NO_POSITION},
            {"TIMING_ONLY"   ,Mode::TIMING_ONLY},
            {"SINGLE_FIX"    ,Mode::SINGLE_FIX},
            {"DIFF_POSITION" ,Mode::DIFF_POSITION},
            {"RTK_FLOAT_FIX" ,Mode::RTK_FLOAT_FIX},
            {"RTK_INT_FIX"   ,Mode::RTK_INT_FIX}
        };
        return mode_type_str;
    };

    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["timestamp"] = rhs.GetTimestamp();
        node["coordinate"] = rhs.GetCoordinate();
        node["longitude"] = rhs.GetLongitude();
        node["latitude"] = rhs.GetLatitude();
        node["height"] = rhs.GetHeight();
        node["velocity_east"] = rhs.GetVelocityEast();
        node["velocity_north"] = rhs.GetVelocityNorth();
        node["velocity_up"] = rhs.GetVelocityUp();
        node["longitude_cov"] = rhs.GetLongitudeCov();
        node["latitude_cov"] = rhs.GetLatitudeCov();
        node["height_cov"] = rhs.GetHeightCov();
        node["velocity_east_cov"] = rhs.GetVelocityEastCov();
        node["velocity_north_cov"] = rhs.GetVelocityNorthCov();
        node["velocity_up_cov"] = rhs.GetVelocityUpCov();

        node["status"]["position_valid_flag"] = rhs.IsPositionValid();
        node["status"]["velocity_valid_flag"] = rhs.IsVelocityValid();
        node["status"]["position_cov_valid_flag"] = rhs.IsPositionCovValid();
        node["status"]["velocity_cov_valid_flag"] = rhs.IsVelocityCovValid();
        for (auto const& value : StringTypePairs())
        {
            if (value.second == rhs.GetMode())
            {
                node["status"]["mode"] = value.first;
            }
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.SetTimestamp(node["timestamp"].as<Timestamp>());
            rhs.SetCoordinate(node["coordinate"].as<Coordinate>());
            rhs.SetLongitude(node["longitude"].as<holo::float64_t>());
            rhs.SetLatitude(node["latitude"].as<holo::float64_t>());
            rhs.SetHeight(node["height"].as<holo::float64_t>());
            rhs.SetVelocityEast(node["velocity_east"].as<holo::float64_t>());
            rhs.SetVelocityNorth(node["velocity_north"].as<holo::float64_t>());
            rhs.SetVelocityUp(node["velocity_up"].as<holo::float64_t>());
            rhs.SetLongitudeCov(node["longitude_cov"].as<holo::float64_t>());
            rhs.SetLatitudeCov(node["latitude_cov"].as<holo::float64_t>());
            rhs.SetHeightCov(node["height_cov"].as<holo::float64_t>());
            rhs.SetVelocityEastCov(node["velocity_east_cov"].as<holo::float64_t>());
            rhs.SetVelocityNorthCov(node["velocity_north_cov"].as<holo::float64_t>());
            rhs.SetVelocityUpCov(node["velocity_up_cov"].as<holo::float64_t>());

            holo::bool_t position_valid_flag = node["status"]["position_valid_flag"].as<holo::bool_t>();
            holo::bool_t velocity_valid_flag = node["status"]["velocity_valid_flag"].as<holo::bool_t>();
            holo::bool_t position_cov_valid_flag = node["status"]["position_cov_valid_flag"].as<holo::bool_t>();
            holo::bool_t velocity_cov_valid_flag = node["status"]["velocity_cov_valid_flag"].as<holo::bool_t>();
            rhs.SetValidFlags(position_valid_flag, velocity_valid_flag, position_cov_valid_flag, velocity_cov_valid_flag);
            
            bool mode_flag = false;
            for (auto const& value : StringTypePairs())
            {
                if (value.first == node["status"]["mode"].as<std::string>())
                {
                    rhs.SetMode(value.second);
                    mode_flag = true;
                }
            }
            if(!mode_flag)
            {
                if (IsDigit(node["status"]["mode"].as<std::string>()))
                {
                    rhs.SetMode(static_cast<Mode>(node["status"]["mode"].as<std::uint16_t>()));
                }
                else
                {
                    return false;
                }
            }

            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};
}  // namespace YAML

#endif