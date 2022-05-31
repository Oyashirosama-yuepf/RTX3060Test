#ifndef HOLO_PARKING_BASE_POINT_FEATURE_LIST_COMMON_TYPES_H_
#define HOLO_PARKING_BASE_POINT_FEATURE_LIST_COMMON_TYPES_H_
#include <holo/core/types.h>

#include <cstdint>
#include <cstdlib>
#include <exception>
#include <new>
namespace holo
{
namespace parking
{
namespace vision
{
template <typename T, uint32_t SIZE>
struct Sequence
{
    uint32_t size;
    T        data[SIZE];

    uint32_t length() const noexcept
    {
        return size;
    }

    void length(uint32_t l)
    {
        if (l <= SIZE)
        {
            size = l;
        }
        else
        {
            throw std::bad_alloc();
        }
    }

    T& operator[](uint32_t idx)
    {
        return data[idx];
    }

    T const& operator[](uint32_t idx) const
    {
        return data[idx];
    }
};
struct Timestamp
{
    uint32_t sec;
    uint32_t nsec;
};

template <typename T>
struct Point2T
{
    T x;
    T y;
};
using Point2f = Point2T<float>;
using Point2d = Point2T<double>;
using Point2i = Point2T<int32_t>;

struct PointFeaturef_ST
{
    Point2f  position;
    uint32_t dimension;
    float    descriptor[128U];
    float    confidence;
};
static_assert(sizeof(PointFeaturef_ST) == 528, "");

struct PointFeaturefList_ST
{
    Timestamp                        timestamp;
    uint32_t                         sensor_id;
    uint32_t                         size;
    Sequence<PointFeaturef_ST, 500U> point_features;
};
}  // namespace vision
}  // namespace parking
}  // namespace holo
#endif