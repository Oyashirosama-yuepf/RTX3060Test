#include <holo/vision/image_objects.h>
#include <holo/vision/keypoint2.h>
#include <holo/vision/object.h>

using PointType       = holo::vision::KeyPoint2T<::holo::float32_t>;
using ObjectType      = holo::vision::ObjectT<PointType>;
using ImageObjectType = holo::vision::ImageObjectsT<ObjectType>;
