/*!
*  \brief Convert latitude longitude height to x y h.
*  \author Hao Wentian(haowentian@holomaitc.com)
*  \date 2017-09-29
*  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
*  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
*/
#ifndef HOLO_MAP_COMMON_CLASSES_LATLONH_H_
#define HOLO_MAP_COMMON_CLASSES_LATLONH_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/classes/latlonxyh.h>

namespace holo
{
namespace map
{

struct LLH
{
public:
    /// latitude in units of degrees
    MapDegree lat_;
    /// longitude in units of degrees
    MapDegree lon_;
    /// height in units of meters
    MapDegree height_;

    /// Default Constructor
    LLH():
        lat_(0.0),
        lon_(0.0),
        height_(0.0)
    {};
    /// constructor
    LLH(const MapDegree lat, const MapDegree lon, const MapDegree height):
        lat_(lat),
        lon_(lon),
        height_(height)
    {};
    /// Transform LL to LLH according to the corresponding height
    void ToLLH(const LL& _latlon, const MapDegree _height)
    {
        lat_ = _latlon.Latitude();
        lon_ = _latlon.Longitude();
        height_ = _height;
    };

    /// Destructor
    ~LLH() noexcept {};

    /// Translate LLH into XYH
    void ToXYH()
    {
        LL latlon(lat_, lon_);
        holo::geometry::Point2T<MapDegree> pointXY = latlon.ToXY();
        lat_ = pointXY.GetX();
        lon_ = pointXY.GetY();
    }

    /// Translate LLH into LLXYH
    operator LLXYH() const
    {
        LLXYH _other;
        _other.SetLatLonH(lat_, lon_, height_);
        return _other;
    }
};

} // namespace map
} // namespace holo

#endif /* HOLO_MAP_COMMON_CLASSES_LATLONH_H_ */
