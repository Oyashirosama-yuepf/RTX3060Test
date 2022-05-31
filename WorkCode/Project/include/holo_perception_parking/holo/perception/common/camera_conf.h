/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-08-13
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */
#ifndef HOLO_PERCEPTION_COMMON_CAMERA_CONF_H_
#define HOLO_PERCEPTION_COMMON_CAMERA_CONF_H_

#include "holo/common/intrinsic.h"
#include "holo/core/types.h"
#include "holo/geometry/angle.h"
#include "holo/numerics/matrix.h"
#include <holo/utils/yaml.h>

namespace holo
{
namespace perception
{

template<typename Scalar>
class CameraConf
{
public:
    CameraConf(const std::string& intrinsic_file,
               const std::string& extrinsic_file);
            //    const std::string& resolution_file);

    typedef holo::Matrix3T<Scalar> Matrix3;

    Scalar camera_height_;
    Scalar pitch_degree_;    // angle, not radian
    Scalar yaw_degree_;      // angle, not radian
    Scalar pitch_radian_;   // radian, not angle
    Scalar yaw_radian_;     // radian, not angle
    int32_t   resolution_x_;   // image width
    int32_t   resolution_y_;   // image height
    Matrix3   k_;              // k matirx of camera
    Matrix3   k_inv_;          // inverse k matrix of camera
    Scalar qw_;
    Scalar qx_;
    Scalar qy_;
    Scalar qz_;
    Scalar x_;
    Scalar y_;
    Scalar z_;
private:
    void load_intrinsic_params(const std::string& fn);

    // To-do: load_extrinsic_params only for current usage while extrinsic params class is not ready
    // void load_extrinsic_params();
    void load_extrinsic_params(const std::string& fn);

    // load resolution params of camera, params are in intrinsic file
    // void load_resolution_params(const std::string& fn);

};  // end class CameraConf

}   /// end namespace perception
}   /// end namespace holo

#endif  /// HOLO_PERCEPTION_COMMON_CAMERA_CONF_H_