/*!
 *  \brief common type definition
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */
#ifndef HOLO_MAP_COMMON_COMMON_TYPE_DEFINE_H_
#define HOLO_MAP_COMMON_COMMON_TYPE_DEFINE_H_

#include <cstddef>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <holo/core/types.h>
#include <holo/geometry/line_segment2.h>
#include <holo/geometry/box2.h>
#include <holo/geometry/line2.h>
#include <holo/geometry/point2.h>
#include <holo/geometry/point3.h>
#include <holo/geometry/pose3.h>
#include <holo/geometry/rot2.h>
#include <holo/utils/holo_root.h>
#include <holo/numerics/vector.h>
#include <holo/common/road_frame2.h>
#include <holo/geometry/curve.h>

/////////////////////////////////////////////////////////////////
/// Macro directives to define enum class with print function
/// Example,
///
///
///
///
///
#define HOLOMAP_MAKE_ENUM_CLASS(name, ...) \
enum class name {__VA_ARGS__, __COUNT}; \
inline std::ostream& operator<<(std::ostream& os, name value) \
{ \
std::string enumName = #name; \
std::string str = #__VA_ARGS__; \
size_t len = str.length(); \
std::vector<std::string> strings; \
std::ostringstream temp; \
for(size_t i = 0; i < len; i ++) { \
if(std::isspace(str[i])) continue; \
        else if(str[i] == ',') { \
        strings.push_back(temp.str()); \
        temp.str(std::string());\
        } \
        else temp<< str[i]; \
} \
strings.push_back(temp.str()); \
os << strings[static_cast<uint>(value)]; \
return os;} \
///////////////////////////////////

namespace holo
{
namespace map
{
enum MapIndicator
{
	NOT_APPLICABLE = 0 //!< NOT_APPLICABLE
};

//TODO :: move to holo_base !!!
enum class Feedback : holo::uint8_t
{
    FAILED,                     /// Map matching fails
    OK,                         /// Map matching succeeds
    MEMORY_ALLOCATION_FAILED,   /// Fail to allocate memory
    INPUT_INVALID,              /// The input data is invalid
    FETCH_FAILED,               /// Fail to fetch data.
    DATA_UNMATCH,               /// Fail to match for whether one element is within another boundary
    MATCHING_RESULT_UNRELIABLE  /// Map matching result is unreliable, especially for one situation
                                /// where a car is runing under a bridge not stored in map
};

//*********************************************************************
enum class Direction : uint8_t
{
    DIR_LEFT = 0,
    DIR_RIGHT = 1,
    DIR_PRECEDING = 20,
	DIR_SUCCEEDING = 21,
	UNKNOWN = 98,
    DIR_ERROR = 99
};

/// Road direction
enum class RoadDirection : uint8_t
{
    /// Both directions are allowed in this road
    ROAD_DIR_BI = 1,
    /// Road direction is from first node to last node
    ROAD_DIR_POSITIVE = 2,
    /// Road direction is from last node to first node
    ROAD_DIR_NEGATIVE = 3
};

/// Driving direction
enum class DrivingDirection : uint8_t
{
    /// None.
    DRIVING_DIR_NONE = 0,
    /// Left-hand traffic directon, like UK, Japan.
    DRIVING_DIR_LEFT_HAND = 1,
    /// Right-hand traffic direction, like China, USA.
    DRIVING_DIR_RIGHT_HAND = 2,
};

/// In or out of the  geographical entity
enum class InOrOutEntity : uint8_t
{
    /// In the entity
    IN_THE_ENTITY = 2,
    /// on the border of entity
    ON_THE_ENTITY_BORDER = 1,
    /// outside of entity
    OUTSIDE_ENTITY = 0
};

/*
enum class LaneMarkType
{
	INVALID,
	SINGLE_DASHED,
	SHORT_THICK_DASHED,
	DOUBLE_DASHED,
	SINGLE_SOLID,
	DOUBLE_SOLID,
	LEFT_SOLID_RIGHT_DASHED,
	LEFT_DASHED_RIGHT_SOLID,
	VIRTUAL_MARK
};
*/

HOLOMAP_MAKE_ENUM_CLASS(LaneMarkType,
	INVALID,
	SINGLE_DASHED,
	SHORT_THICK_DASHED,
	DOUBLE_DASHED,
	SINGLE_SOLID,
	DOUBLE_SOLID,
	LEFT_SOLID_RIGHT_DASHED,
	LEFT_DASHED_RIGHT_SOLID,
	VIRTUAL_MARK);

HOLOMAP_MAKE_ENUM_CLASS(LaneMarkColor,
	OTHERS,
	INVALID,
	WHITE,
	YELLOW,
	LEFT_YELLOW_RIGHT_WHITE,
	LEFT_WHITE_RIGHT_YELLOW);

HOLOMAP_MAKE_ENUM_CLASS(LaneMarkMaterial,
	INVALID,
	PAINTED,
	RAISED_PAVEMENT,
	PAINTED_RAISED_PAVEMENT);

/********************************************************
 * Basic types for MID MIF files
 ********************************************************/
/// an integer number with maximal 30 bit digits
typedef ::std::uint64_t       Char30;
/// an integer number with maximal 20 bit digits
typedef ::std::uint64_t       Char20;
/// an integer number with maximal 13 digits
typedef ::std::uint64_t       Char13;
/// an integer number with maximal 12 digits
typedef ::std::uint64_t       Char12;
/// an integer number with maximal 10 digits
typedef ::std::uint64_t       Char10;
/// an integer number with 1 digit
typedef ::std::uint8_t        Char1;
/// an integer number with maximal 2 digits
typedef ::std::uint8_t        Char2;
/// an integer number with maximal 7 digits
typedef ::std::uint32_t       Char7;
/// an integer number with maximal 6 digits
typedef ::std::uint32_t       Char6;
/// an integer number with maximal 4 digits
typedef ::std::uint16_t       Char4;
/// an integer number with maximal 3 digits
typedef ::std::uint16_t       Char3;
//bitmask with 30 bits
typedef ::std::uint32_t       BitChar30;

// a float value with maximal 13 digits. the float part shall be accurate to 8 digits.
typedef float64_t  FloatChar13;
// a float value with maximal 22 digits. the float part shall be accurate to 13 digits.
typedef float64_t  FloatChar22;

typedef std::pair<Char13, long int> PairKeyAndInt;
typedef std::pair<Char13, double>   PairKeyAndFloat;
typedef std::vector<uint64_t>       VecKeyValue;
typedef std::vector<uint64_t>       MapFeatureIdVectorType;
typedef std::vector<Char13>         VecNodeId;
/********************************************************
 * Frequently used data types for map related processing
 ********************************************************/
/// data type for geometric distance in terms of length
typedef float64_t  Distance;
/*
 * precision of lat/lon vs distance
places   degrees          distance
-------  -------          --------
0        1                111  km
1        0.1              11.1 km
2        0.01             1.11 km
3        0.001            111  m
4        0.0001           11.1 m
5        0.00001          1.11 m
6        0.000001         11.1 cm
7        0.0000001        1.11 cm
8        0.00000001       1.11 mm
 * */
/// data type for angle in terms of degrees, ranging from e.g. -180 to 180, or 0 to 360
typedef float64_t  MapDegree;
/// data type for angle in terms of radian, ranging from e.g. -pi to pi, or 0 to 2*pi
typedef float64_t  MapRadian;
/// data type for intermediate angular calculation results.
typedef float64_t  NumResult;
/// data type for data size, usually the size of an iterator in a for-loop or an index of a vector
typedef ::std::size_t         Size;
/// data type for data id, which is in NavInfo data in terms of 13-digit-char
typedef ::std::uint64_t   MapFeatureIdType;
typedef ::std::uint64_t   KeyValue;
typedef ::std::int8_t     SeqValue;
typedef std::vector<MapFeatureIdType>*        PtrMapFeatureIdVectorType;
typedef std::vector<KeyValue>*                PtrVecKeyValue;
typedef const std::vector<MapFeatureIdType>*  CPtrMapFeatureIdVectorType;
typedef const std::vector<KeyValue>*          CPtrVecKeyValue;
typedef holo::geometry::LineSegment2d         MapLineSegment;
// typedef LineSegment3d MapLineSegment3;
typedef holo::numerics::Vector2T<FloatChar13> MapVector;
typedef holo::geometry::Box2d MapBox;
typedef holo::geometry::Point2d MapPoint;
typedef holo::geometry::Point3d MapPoint3;
typedef holo::geometry::Point2d::Vector2Type MapVector2;
typedef holo::geometry::Point3d::Vector3Type MapVector3;
// typedef Ellipse2d MapEllipse;
// typedef Circle2d MapCircle;
typedef holo::geometry::Line2d MapLine;
typedef holo::geometry::Pose2d MapPose;
typedef holo::geometry::Pose3 MapPose3;
typedef holo::geometry::Rot2d MapRotationMatrix;
// typedef Pathd MapPath;
// typedef PathPointd MapPathPoint;
typedef std::unordered_map<MapFeatureIdType, std::vector<MapPoint3>> HashmapLine3D;
/********************************************************
 * MAX values used to initialize the variables
 ********************************************************/
const float64_t    MAX_FLOAT64 =
    std::numeric_limits<float64_t>::max();
const float64_t    LOWEST_FLOAT64 =
    std::numeric_limits<float64_t>::lowest();
const uint64_t     MAX_UINT64 =
    std::numeric_limits<uint64_t>::max();
const uint32_t     MAX_UINT32 =
    std::numeric_limits<uint32_t>::max();
const uint16_t     MAX_UINT16 =
    std::numeric_limits<uint16_t>::max();
const uint8_t      MAX_UINT8  =
    std::numeric_limits<uint8_t>::max();
const Distance         MAX_DISTANCE =  std::numeric_limits<Distance>::max();
const Distance		   MAX_VALID_DISTANCE = 5; // to do ; unit is metre
const MapDegree        MAX_DEGREE   =  std::numeric_limits<MapDegree>::max();
const MapRadian        MAX_RADIAN  =  std::numeric_limits<MapRadian>::max();
const Char13           MAX_CHAR13 =   9999999999999;
const Char12           MAX_CHAR12 =   999999999999;
const Char10           MAX_CHAR10 =   9999999999;
const Size             MAX_SIZE   =   std::numeric_limits<Size>::max();
const MapFeatureIdType MAX_MapFeatureIdType = MAX_CHAR13;
const Char13           DEFAULT_TILE_ID = 1;
const double           ALMOST_ZERO = 0.000001;
typedef std::pair<MapFeatureIdType, MapFeatureIdType> PairId;
typedef std::vector<MapPoint3> VecXYH;

/********************************************************
 * Some frequently used constant values
 ********************************************************/
/// Radius of the earth in meters.
const Distance           EARTH_RADIUS_IN_METERS = 6371000.0;
/// Output precision: 3 integer + 8 digits
const int8_t       MAP_DATA_OUTPUT_DIGITS_PRECISION = 11;
/// Delimeter used for map data output
const std::string           MDR = ",";

/********************************************************
 * constant values used for calculation
 ********************************************************/
// centimeter accuracy
static constexpr Distance  TOLERANCE_SAME_DISTANCE = 0.01;
// centi-degree accuracy
static constexpr MapDegree  TOLERANCE_SAME_DEGREE = 0.0000001;
//default tile level
const Char1 DEFAULT_TILE_LEVEL = 15;
//tile length
#define TILE_LENGTH(_level) (1UL << (31 - _level))
//config path
static const std::string HOLO_MAP_CONFIG_PATH =
        ::holo::GetHoloConfigRootDirectory() + "/holo_map/";
//log path
static const std::string HOLO_MAP_LOG_DIR =
        ::holo::GetHoloLogRootDirectory() + "/holo_map/";

const MapFeatureIdType  INVALID_KEY = 0UL;
const Distance          INVALID_DISTANCE = 0.00;
const MapFeatureIdType  INVALID_INDEX = 9999UL;
const Distance          INVALID_Z = 99999.99;
const ::std::int64_t    INVALID_Z_CM = 9999999;
const SeqValue          INVALID_SEQ = 99;
const Size              INVALID_SIZE = 0;
const ::holo::uint8_t   INVALID_ZONE_ID = 199U;

// Defined for coordinate.

#define COORDINATE_UTM_ZONE_3 3
#define COORDINATE_UTM_ZONE_6 6

#ifndef COORDINATE_UTM_ZONE_VALUE
    #define COORDINATE_UTM_ZONE_VALUE COORDINATE_UTM_ZONE_6
#endif /* COORDINATE_UTM_ZONE_VALUE */

typedef holo::uint8_t CoordinateUtmZoneType;

#if COORDINATE_UTM_ZONE_VALUE == COORDINATE_UTM_ZONE_6
    CoordinateUtmZoneType const COORDINATE_UTM_ZONE_ID_MAX = 60;
    CoordinateUtmZoneType const COORDINATE_UTM_ZONE_ID_MIN = 1;
#elif COORDINATE_UTM_ZONE_VALUE == COORDINATE_UTM_ZONE_3
    CoordinateUtmZoneType const COORDINATE_UTM_ZONE_ID_MAX = 120;
    CoordinateUtmZoneType const COORDINATE_UTM_ZONE_ID_MIN = 1;
#else
    #pragma warning(COORDINATE_UTM_ZONE_VALUE, "invalid COORDINATE_UTM_ZONE_VALUE")
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RoadFrame
using ScalarTypeSensor    = float32_t;
using CurveTypeSensor     = holo::numerics::Polynomial<ScalarTypeSensor, 3U>;
using BoundaryTypeSensor  = holo::common::LaneBoundary<CurveTypeSensor>;
using LaneTypeSensor      = holo::common::Lane<CurveTypeSensor>;
using RoadFrameTypeSensor = holo::common::RoadFrame<CurveTypeSensor, 4U>;

using CurveTypeFused     = holo::geometry::CurvePolynomial<holo::geometry::Point2d, 64U, 3U>;
using BoundaryTypeFused  = holo::common::LaneBoundary<CurveTypeFused>;
using LaneTypeFused      = holo::common::Lane<CurveTypeFused>;
using RoadFrameTypeFused = holo::common::RoadFrame<CurveTypeFused>;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // namespace map
} // namespace holo

#endif /* HOLO_MAP_COMMON_COMMON_TYPE_DEFINE_H_ */
