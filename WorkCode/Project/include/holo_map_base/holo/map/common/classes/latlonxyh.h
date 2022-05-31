/*!
*  \brief Convert latitude longitude height to x y h.
*  \author Hao Wentian(haowentian@holomaitc.com)
*  \date 2017-09-29
*  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
*  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
*/
#ifndef HOLO_MAP_COMMON_CLASSES_LATLONXYH_H_
#define HOLO_MAP_COMMON_CLASSES_LATLONXYH_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/classes/latlon.h>

namespace holo
{
namespace map
{

class LLXYH;
typedef std::vector<LLXYH>  VecLLXYH;
typedef const std::vector<LLXYH>*  CPtrVecLLXYH;

class LLH;
typedef std::vector<LLH>  VecLLH;

class LLXYH
{
public:
    LLXYH():
        latlon_(0.0, 0.0),
        xy_(0.0, 0.0),
        h_(0.0)
    {

    };

    LLXYH(const LL& _latlon, const Distance _h):
        latlon_(_latlon),
        xy_(0.0, 0.0),
        h_(_h)
    {
        xy_ = _latlon.ToXY();
    };

    LLXYH(const MapPoint& _xy, const Distance _h):
        latlon_(0.0, 0.0),
        xy_(_xy),
        h_(_h)
    {
        latlon_.SetByXY(_xy);
    };

    LLXYH(const map::MapPoint3& _xyh):
        xy_(_xyh.GetPointXY()),
        h_(_xyh.GetZ())
    {
        latlon_.SetByXY(xy_);
    };

    // Copy constructor
    LLXYH(const LLXYH& _other)
    {
        latlon_ = _other.latlon_;
        xy_ = _other.xy_;
        h_ = _other.h_;
    };

    LLXYH& operator=(const LLXYH& _other)
    {
        if (this != &_other)
        {
            this->latlon_ = _other.latlon_;
            this->xy_ = _other.xy_;
            this->h_ = _other.h_;
        }
        return *this;
    };

    // Deconstructor
    ~LLXYH() noexcept
    {

    };

    // Getter
    LL GetLatLon() const
    {
        return latlon_;
    };

    MapDegree GetLat() const
    {
        return latlon_.Latitude();
    };

    MapDegree GetLon() const
    {
        return latlon_.Longitude();
    };

    MapPoint GetXY() const
    {
        return xy_;
    };

    MapPoint GetPointXY() const
    {
        return xy_;
    };

    Distance GetX() const
    {
        return xy_.GetX();
    };

    Distance GetY() const
    {
        return xy_.GetY();
    };

    Distance GetH() const
    {
        return h_;
    };

    Distance GetZ() const
    {
        return h_;
    };

    // Setter
    void SetLatLon(const LL& _latlon)
    {
        latlon_ = _latlon;
        xy_ = _latlon.ToXY();
    }

    void SetLatLon(const MapDegree _lat, const MapDegree _lon)
    {
        latlon_.SetByLatLon(_lat, _lon);
        xy_ = latlon_.ToXY();
    }

    void SetLatLonH(const MapDegree _lat, const MapDegree _lon, const Distance _h)
    {
        latlon_.SetByLatLon(_lat, _lon);
        xy_ = latlon_.ToXY();
        h_ = _h;
    }

    void SetLatLonH(const LL& _latlon, const Distance _h)
    {
        latlon_ = _latlon;
        xy_ = _latlon.ToXY();
        h_ = _h;
    }

    void SetXY(const MapPoint& _xy)
    {
        latlon_.SetByXY(_xy);
        xy_ = _xy;
    }

    void SetX(const MapDegree& _input)
    {
        xy_.SetX(_input);
    }

    void SetY(const MapDegree& _input)
    {
        xy_.SetY(_input);
    }

    void SetZ(const Distance& _input)
    {
        h_ = _input;
    }

    void SetXYH(const MapPoint& _xy, const Distance _h)
    {
        latlon_.SetByXY(_xy);
        xy_ = _xy;
        h_ = _h;
    }

    void SetXYH(const Distance _x, const Distance _y, const Distance _h)
    {
        xy_.SetX(_x);
        xy_.SetY(_y);
        latlon_.SetByXY(xy_);
        h_ = _h;
    }

    void SetH(const Distance _h)
    {
        h_ = _h;
    }

    void SetLatLonXY(const LL& _latlon, const MapPoint& _xy)
    {
        latlon_ = _latlon;
        xy_ = _xy;
    }

    void SetLatLonXYH(const LL& _latlon,
                     const MapPoint& _xy,
                     const Distance _h)
    {
        latlon_ = _latlon;
        xy_ = _xy;
        h_ = _h;
    }

    // For purpose of compatability is supported
    operator LL() const
    {
        return latlon_;
    }

    operator MapPoint3() const
    {
        MapPoint3 _other;
        _other.Set(xy_.GetX(), xy_.GetY(), h_);
        return _other;
    }

    MapPoint3 GetPointXYH() const
    {
        MapPoint3 _other;
        _other.Set(xy_.GetX(), xy_.GetY(), h_);
        return _other;
    }

    operator MapPoint() const
    {
        MapPoint _other;
        _other.Set(xy_.GetX(), xy_.GetY());
        return _other;
    }

    bool operator==(const LLXYH& rhs)
    {
        float64_t epsilon = 1e-8;
        const bool is_equal_x = std::fabs(this->GetX()-rhs.GetX()) < epsilon;
        const bool is_equal_y = std::fabs(this->GetY()-rhs.GetY()) < epsilon;
        const bool is_equal_h = std::fabs(this->GetH()-rhs.GetH()) < epsilon;
        return  is_equal_x && is_equal_y && is_equal_h;
    }

    bool operator!=(const LLXYH& rhs)
    {
        return !(*this == rhs);
    }

    void Set(MapDegree x, MapDegree y, Distance z)
    {
        xy_.SetX(x);
        xy_.SetY(y);
        h_ = z;
        latlon_.SetByXY(xy_);
    }
private:
    // Latitude/Longitude in degree
    LL latlon_;
    // X/Y in UTM coordinate in meter,
    // which are transformed from Longitude/Latitude
    MapPoint xy_;
    // Height
    Distance h_;
};

} // namespace map
} // namespace holo

#endif /* HOLO_MAP_COLLXYHMMON_CLASSES_LATLONXYH_H_ */
