/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file camera_group.hpp
 * @brief This header file defines .
 * @author zhoushengjie(zhoushengjie@holomatic.com)
 * @date "2021-11-12"
 */

#ifndef HOLO_PERCEPTION_UTILS_CAMERA_GROUP_HPP_
#define HOLO_PERCEPTION_UTILS_CAMERA_GROUP_HPP_

#include <holo/perception/utils/camera_group.h>

#include <algorithm>

namespace holo
{
namespace perception
{
template <typename ScalarType, int N>
bool_t CameraGroup::ProjectToCamera(Jet<ScalarType, N> const& x, Jet<ScalarType, N> const& y,
                                    Jet<ScalarType, N> const& z, Jet<ScalarType, N> const& length,
                                    Jet<ScalarType, N> const& width, Jet<ScalarType, N> const& height,
                                    Jet<ScalarType, N> const& yaw, SensorId sid,
                                    std::array<Jet<ScalarType, N>, 4U>& result_box2)
{
    auto         cps          = genBox3d(x, y, z, length, width, height, yaw);
    auto         camera_param = GetCameraParamsBySensorid(sid);
    auto         frustum      = GetFrustumBySensorid(sid);
    auto const&  T            = camera_param.second.ToMatrix();
    IntrinsicPtr intrinsic    = camera_param.first;

    for (size_t i = 0U; i < cps.size(); ++i)
    {
        // LOG(INFO) << "p" << i << "=" << cps[i][0].a << " " << cps[i][1].a << " " << cps[i][2].a;
        auto tx    = cps[i][0U];
        auto ty    = cps[i][1U];
        auto tz    = cps[i][2U];
        cps[i][0U] = T(0U, 0U) * tx + T(0U, 1U) * ty + T(0U, 2U) * tz + T(0U, 3U);
        cps[i][1U] = T(1U, 0U) * tx + T(1U, 1U) * ty + T(1U, 2U) * tz + T(1U, 3U);
        cps[i][2U] = T(2U, 0U) * tx + T(2U, 1U) * ty + T(2U, 2U) * tz + T(2U, 3U);
        // LOG(INFO) << "p" << i << "=" << cps[i][0].a << " " << cps[i][1].a << " " << cps[i][2].a;
    }
    using Index = std::array<size_t, 2U>;
    std::array<Index, 12U> cps_index({
        Index({0, 1}),
        Index({1, 2}),
        Index({2, 3}),
        Index({3, 0}),
        Index({4, 5}),
        Index({5, 6}),
        Index({6, 7}),
        Index({7, 4}),
        Index({0, 5}),
        Index({1, 6}),
        Index({2, 7}),
        Index({3, 4}),
    });

    std::vector<std::array<Jet<ScalarType, N>, 3U>> ret;
    ret.reserve(20U);
    for (size_t i = 0U; i < cps_index.size(); ++i)
    {
        auto        idx    = cps_index[i];
        auto const& p1     = cps[idx[0U]];
        auto const& p2     = cps[idx[1U]];
        auto        flag_1 = inFrustum(Point3f(p1[0U].a, p1[1U].a, p1[2U].a), frustum);
        auto        flag_2 = inFrustum(Point3f(p2[0U].a, p2[1U].a, p2[2U].a), frustum);
        if (flag_1 && flag_2)
        {
            ret.push_back(p1);
            ret.push_back(p2);
        }
        else if (flag_1 || flag_2)
        {
            addIntersection(p1, p2, frustum, ret);
        }
    }

    // for (size_t i = 0U; i < ret.size(); ++i)
    // {
    //      LOG(INFO) << ret[i][0].a << " " << ret[i][1].a << " " << ret[i][2].a;
    // }

    Jet<ScalarType, N> min_x, max_x, min_y, max_y;
    min_x.a = 1e8f;
    max_x.a = -1e8f;
    min_y.a = 1e8f;
    max_y.a = -1e8f;

    ScalarType intrinsic_width  = 0.0f;
    ScalarType intrinsic_height = 0.0f;
    if (sid.GetModel() == SensorId::Model::CAMERA_UNKNOWN)
    {
        std::shared_ptr<FisheyeIntrinsicf> curr_intrinsic = std::static_pointer_cast<FisheyeIntrinsicf>(intrinsic);

        intrinsic_width  = curr_intrinsic->GetWidth();
        intrinsic_height = curr_intrinsic->GetHeight();
        for (auto p : ret)
        {
            Jet<ScalarType, N> u, v;
            if (project(*curr_intrinsic, p, u, v))
            {
                if (u.a < min_x.a)
                {
                    min_x = u;
                }
                if (u.a > max_x.a)
                {
                    max_x = u;
                }
                if (v.a < min_y.a)
                {
                    min_y = v;
                }
                if (v.a > max_y.a)
                {
                    max_y = v;
                }
            }
        }
    }
    else
    {
        std::shared_ptr<OmnidirectionalIntrinsicf> curr_intrinsic =
            std::static_pointer_cast<OmnidirectionalIntrinsicf>(intrinsic);

        intrinsic_width  = curr_intrinsic->GetWidth();
        intrinsic_height = curr_intrinsic->GetHeight();
        for (auto p : ret)
        {
            Jet<ScalarType, N> u, v;
            if (project(*curr_intrinsic, p, u, v))
            {
                if (u.a < min_x.a)
                {
                    min_x = u;
                }
                if (u.a > max_x.a)
                {
                    max_x = u;
                }
                if (v.a < min_y.a)
                {
                    min_y = v;
                }
                if (v.a > max_y.a)
                {
                    max_y = v;
                }
            }
        }
    }

    if (ret.size() > 0U && min_x.a < intrinsic_width && min_y.a < intrinsic_height && max_x.a > 0.0f && max_y.a > 0.0f)
    {
        result_box2[0U] = min_x;
        result_box2[1U] = min_y;
        result_box2[2U] = max_x;
        result_box2[3U] = max_y;

        return true;
    }

    return false;
}

template <typename ScalarType, int N>
std::vector<std::array<Jet<ScalarType, N>, 3U>>
CameraGroup::genBox3d(Jet<ScalarType, N> const& x, Jet<ScalarType, N> const& y, Jet<ScalarType, N> const& z,
                      Jet<ScalarType, N> const& length, Jet<ScalarType, N> const& width,
                      Jet<ScalarType, N> const& height, Jet<ScalarType, N> const& yaw)
{
    std::vector<std::array<Jet<ScalarType, N>, 3U>> ret;
    auto                                            l = 0.5f * length;
    auto                                            w = 0.5f * width;
    auto                                            h = 0.5f * height;
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({-l, -w, -h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({+l, -w, -h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({+l, +w, -h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({-l, +w, -h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({-l, +w, +h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({-l, -w, +h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({+l, -w, +h}));
    ret.push_back(std::array<Jet<ScalarType, N>, 3U>({+l, +w, +h}));
    auto s = sin(yaw);
    auto c = cos(yaw);
    for (size_t i = 0U; i < ret.size(); ++i)
    {
        auto tx    = ret[i][0U];
        auto ty    = ret[i][1U];
        ret[i][0U] = x + c * tx - s * ty;
        ret[i][1U] = y + s * tx + c * ty;
        ret[i][2U] = z + ret[i][2U];
    }
    return ret;
}

template <typename ScalarType, int N>
bool_t CameraGroup::project(FisheyeIntrinsicf const& intrinsic, std::array<Jet<ScalarType, N>, 3U> const& p3,
                            Jet<ScalarType, N>& u, Jet<ScalarType, N>& v)
{
    auto const& x  = p3[0U];
    auto const& y  = p3[1U];
    auto const& oz = p3[2U];
    auto const& D  = intrinsic.GetD();
    auto const& K  = intrinsic.GetK();

    auto z = oz;
    if (oz.a < holo::EpsilonT<ScalarType>::value)
    {
        z.a = holo::EpsilonT<ScalarType>::value;
        // return false;
    }
    auto a = x / z;
    auto b = y / z;

    auto r2 = a * a + b * b;

    auto r = sqrt(r2);

    if (r.a < holo::EpsilonT<ScalarType>::value)
    {
        r = sqrt(r2) + holo::EpsilonT<ScalarType>::value;
    }

    auto theta  = atan(r);
    auto theta2 = theta * theta;
    auto theta4 = theta2 * theta2;
    auto theta6 = theta2 * theta4;
    auto theta8 = theta4 * theta4;
    auto rd     = theta * (1.0f + D(0U) * theta2 + D(1U) * theta4 + D(2U) * theta6 + D(3U) * theta8);
    auto xd     = rd * (a / r);
    auto yd     = rd * (b / r);
    u           = xd * K(0U, 0U) + yd * K(0U, 1U) + K(0U, 2U);
    v           = yd * K(1U, 1U) + K(1U, 2U);

    return true;
}

template <typename ScalarType, int N>
bool_t CameraGroup::project(OmnidirectionalIntrinsicf const& intrinsic, std::array<Jet<ScalarType, N>, 3U> const& p3,
                            Jet<ScalarType, N>& u, Jet<ScalarType, N>& v)
{
    auto const&        x  = p3[0U];
    auto const&        y  = p3[1U];
    Jet<ScalarType, N> oz = p3[2U];

    auto const& cx_ = intrinsic.GetCX();
    auto const& cy_ = intrinsic.GetCY();
    auto const& c_  = intrinsic.GetC();
    auto const& d_  = intrinsic.GetD();
    auto const& e_  = intrinsic.GetE();

    std::array<ScalarType, 15U> proj_poly_ = intrinsic.GetProjectPolynomial();

    auto       norm    = sqrt(x * x + y * y);
    ScalarType theta   = atan2(-oz.a, norm.a);
    ScalarType rho     = 0.0f;
    ScalarType theta_i = 1.0f;

    for (size_t i = 0; i < proj_poly_.size(); ++i)
    {
        rho += theta_i * proj_poly_[i];
        theta_i *= theta;
    }

    auto p0 = x / norm * rho;
    auto p1 = y / norm * rho;

    u = p0 * c_ + p1 * d_ + cx_;
    v = p0 * e_ + p1 + cy_;

    return true;
}

template <typename ScalarType, int N>
bool_t CameraGroup::intersection(std::array<Jet<ScalarType, N>, 3U> const& x,
                                 std::array<Jet<ScalarType, N>, 3U> const& y, Plane const& plane,
                                 std::array<Jet<ScalarType, N>, 3U>& z)
{
    auto dx   = y[0U].a - x[0U].a;
    auto dy   = y[1U].a - x[1U].a;
    auto dz   = y[2U].a - x[2U].a;
    auto deno = plane[0U] * dx + plane[1U] * dy + plane[2U] * dz;
    auto no   = plane[0U] * x[0U].a + plane[1U] * x[1U].a + plane[2U] * x[2U].a;
    if (fabsf(deno) > 1e-3f)
    {
        auto t = -no / deno;
        z      = {x[0U] + dx * t, x[1U] + dy * t, x[2U] + dz * t};
        return true;
    }
    return false;
}

template <typename ScalarType, int N>
void CameraGroup::addIntersection(std::array<Jet<ScalarType, N>, 3U> const& x,
                                  std::array<Jet<ScalarType, N>, 3U> const& y, Frustum const& frustum,
                                  std::vector<std::array<Jet<ScalarType, N>, 3U>>& ret)
{
    for (size_t i = 0U; i < frustum.size(); ++i)
    {
        auto const& plane  = frustum[i];
        auto        check1 = x[0U].a * plane[0U] + x[1U].a * plane[1U] + x[2U].a * plane[2U];
        auto        check2 = y[0U].a * plane[0U] + y[1U].a * plane[1U] + y[2U].a * plane[2U];
        if (check1 * check2 < 0)
        {
            std::array<Jet<ScalarType, N>, 3U> z;
            if (intersection(x, y, plane, z))
            {
                bool_t valid = true;
                for (size_t j = 0U; j < frustum.size(); ++j)
                {
                    auto pj    = frustum[j];
                    auto check = z[0U].a * pj[0U] + z[1U].a * pj[1U] + z[2U].a * pj[2U];
                    if ((check < -1e-3f && pj[2] > 1e-3f) || (check > 1e-3f && pj[2] < -1e-3f))
                    {
                        valid = false;
                        break;
                    }
                }
                if (valid)
                {
                    ret.push_back(z);
                }
            }
        }
    }
}

}  // namespace perception
}  // namespace holo

#endif
