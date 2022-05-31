/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file special_road_boundary_builder.h
 * @brief special_road_boundary_builder.h
 * @author wanghaiyang@holomatic.com
 * @date "2021-03-18"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_APPLICATION_SPECIAL_ROAD_BOUNDARY_BUILDER_H_
#define HOLO_MAP_SERVICE_CLIENT_APPLICATION_SPECIAL_ROAD_BOUNDARY_BUILDER_H_

#include <memory>

#include <holo/map/service/client/application/road_boundary_v2.h>
#include <holo/map/service/client/common/geometry.h>
#include <holo/map/service/client/engine/retriever.h>
#include <holo/map/service/client/profile/base.h>
#include <holo/map/service/client/profile/lane.h>
#include <holo/map/service/client/profile/segment.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace application
{
namespace algorithm
{
/**
 * @addtogroup algorithm
 * @{
 *
 */

/**
 * @brief Extract special road boundaries(Barrier and Curb) by target point from
 *        left and right boundaries.
 * 
 * @details Instruction of this algorithm.
 *     |------------B1----------------|            |--------B2- -------|Left barrier boundary of current road.
 *        |-----C1--------|                   |--------C2---------|     Left curb boundary of current road.
 * |-------------------------------------------------------------------|Left lane boundary of most left lane.
 * |                                                                   |
 * |>>>>>>>>>> P1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> P2 >>>>>>>>>|Road direction.
 * |                                                                   |
 * |-------------------------------------------------------------------|Right lane boundary of most right lane.
 * 
 * This algorithm is used to extract left and right barrier or curb which are closest to target point
 * (Like: P1 or P2). Base on raw HD map data, left and right lane boundary are continuous, but left
 * and right barrier boundaries or curbs are non-continuous. Therefore the result of left or right
 * barrier(curb) boundary is not non-continuouts.
 * 
 * Target point P1:
 * Left barrier boundary: Geometry   -> A range points of B1(Trimmed by target point,
 *                                      front and rear detection distance).
 *                        Attributes -> [0, 20] (Index range of point array).
 * Left curb boundary: Geometry -> A range point of C1 and C2(Trimmed by target point,
 *                                 front and rear detection distance).
 *                     Attributes -> [0, 16] [17, 25].
 */
class SpecialRoadBoundaryBuilder
{
public:
    /// Define point type.
    using Point3dType = holo::geometry::Point3d;

    /// Define retriever type for inner members.
    using RetrieverType     = holo::map::service::client::engine::Retriever;
    using RetrieverSPtrType = holo::map::service::client::engine::RetrieverSPtrType;

    /// Define road boundary type for inner members.
    using SpecialRoadBoundaryType = holo::map::service::client::application::SpecialRoadBoundaryType;
    using SpecialRoadBoundarySPtrType = holo::map::service::client::application::SpecialRoadBoundarySPtrType;

    /**
     * @brief Input paramters for current algorithm.
     */
    struct Input
    {
        /// Define types for inner members.
        using ProfileIdType = SpecialRoadBoundaryType::RoadBoundaryIdType;
        using DistanceType  = SpecialRoadBoundaryType::LengthType;
        using BoundaryType  = SpecialRoadBoundaryType::BoundaryType;

        /// Target point.
        Point3dType point;

        /// Lane group close to target point.
        ProfileIdType lane_group_id = 0;

        /// Special road boundary type, only support kBOUNDARY_TYPE_BARRIER,
        /// and kBOUNDARY_TYPE_CURB now.
        BoundaryType boundary_type = BoundaryType::kBOUNDARY_TYPE_UNKNOWN;

        /// Front distance of target point.
        DistanceType front_detection_distance = 0.0;
        /// Rear distance of target point.
        DistanceType rear_detection_distance = 0.0;
    };

    /**
     * @brief Output parameters for current algorithm.
     */
    struct Output
    {
        /// Left special road boundary of target point, if no special type road boundary,
        /// it should be nullptr(Notice).
        SpecialRoadBoundarySPtrType left_road_boundary = nullptr;
        /// Right special road boundary of target point, if no special type road boundary,
        /// it should be nullptr(Notice).
        SpecialRoadBoundarySPtrType right_road_boundary = nullptr;
    };

    /**
     * @brief Mashal the input to a JSON string.
     * 
     * @param[in] input Input parameters.
     * @return A Json string.
     */
    static std::string FormatToString(Input const& input);

    /**
     * @brief Mashal the input to a JSON string.
     * 
     * @param[in] ouput Output parameters.
     * @return A Json string.
     */
    static std::string FormatToString(Output const& output);

    /**
     * @brief Default Constructor.
     */
    SpecialRoadBoundaryBuilder();

    /**
     * @brief Default Destructor.
     */
    virtual ~SpecialRoadBoundaryBuilder();

    /**
     * @brief Access inner parameter.
     * 
     * @return A smart pointer of Retriever.
     */
    RetrieverSPtrType GetRetriever() const;

    /**
     * @brief Assign inner parameter.
     * 
     * @param[in] ret A smart pointer of Retriever.
     */
    void SetRetriever(RetrieverSPtrType ret);

    /**
     * @brief Access verbose flag.
     * 
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assing verbose flag.
     * 
     * @param[in] true: Print detail debug logs.
     *            false: Close detail debug logs(default value).
     */
    void SetVerbose(holo::bool_t const v) const;
    
    /**
     * @brief Extract left and right special road boundaries close to
     *        target point.
     * 
     * @param[in] input Input parameters.
     * @param[out] output Output paramters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs for
     *                for more details.
     */
    holo::bool_t Process(Input const& input, Output& output);

    /**
     * @brief Extract left and right special road boundaries close to
     *        target point.
     * 
     * @param[in] input Input parameters.
     * @param[out] output Output paramters.
     * @return true: No error.
     *         false: An error occurs in this function, refer to logs for
     *                for more details.
     */
    holo::bool_t operator () (Input const& input, Output& output);

private:
    /// Implemention of SpecialRoadBoundaryBuilder.
    class SpecialRoadBoundaryBuilderInner;
    /// A smart pointer of SpecialRoadBoundaryBuilderInner.
    std::unique_ptr<SpecialRoadBoundaryBuilderInner> inner_;
};

/**
 * @}
 */
} ///< namespace algorithm
} ///< namespace application
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_APPLICATION_SPECIAL_ROAD_BOUNDARY_BUILDER_H_ */