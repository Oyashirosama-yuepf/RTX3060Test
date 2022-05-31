/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file local_map_graph_builder.h
 * @brief Build local map graph.
 * @author Liu Qikang(liuqikang@holomaitc.com)
 * @date 2020-10-25
 */

#ifndef HOLO_MAP_LOCAL_MAP_GRAPH_LOCAL_MAP_GRAPH_BUILDER_H_
#define HOLO_MAP_LOCAL_MAP_GRAPH_LOCAL_MAP_GRAPH_BUILDER_H_

#include <holo/common/odometry.h>
#include <holo/map/common/common_define.h>
#include <holo/map/feature/local_map_graph/local_map_graph.h>
#include <holo/map/service/client/engine/helper.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
/**
 * @addtogroup graph
 *
 * @{
 */

/**
 * @brief Provide local map graph builder.
 */
class LocalMapGraphBuilder
{
public:
    using RetrieverSPtrType     = holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType;
    using FeatureId             = holo::map::service::client::engine::Retriever::ProfileIdType;
    using LocalMapOdometrydType = holo::common::LocalMapOdometryd;
    using FeatureMapType        = holo::map::navigator::graph::LocalMapGraphType::FeatureMapType;
    using FeatureIdVectorType   = holo::map::MapFeatureIdVectorType;
    using DistanceMeterType     = holo::map::Distance;

    LocalMapGraphBuilder();
    ~LocalMapGraphBuilder();

    LocalMapGraphBuilder(const LocalMapGraphBuilder&) = delete;
    LocalMapGraphBuilder(LocalMapGraphBuilder&&)      = delete;
    LocalMapGraphBuilder& operator=(const LocalMapGraphBuilder&) = delete;
    LocalMapGraphBuilder& operator=(LocalMapGraphBuilder&&) = delete;

    /**
     * @brief Define input info for local map graph builder.
     */
    struct Input
    {
        LocalMapOdometrydType odometry;
        DistanceMeterType     front_distance = 0.0;
        DistanceMeterType     rear_distance  = 0.0;
    };

    /**
     * @brief Define output info for local map graph builder.
     */
    struct Output
    {
        LocalMapGraphSPtrType   local_map_graph = nullptr;
        holo::common::Timestamp start_time;
        holo::common::Timestamp end_time;
    };

    /**
     * @brief Marshal the links to a JSON string.
     *
     * @param[in] link Links parameters.
     * @return A Json string.
     */
    static std::string FormatToString(navigator::graph::LinkSPtrType const& link);

    /**
     * @brief Marshal the lanes to a JSON string.
     *
     * @param[in] lane Lane parameters.
     * @return A Json string.
     */
    static std::string FormatToString(navigator::graph::LaneSPtrType const& lane);

    /**
     * @brief Marshal the boundaries to a JSON string.
     *
     * @param[in] boundary Boundary parameters.
     * @return A Json string.
     */
    static std::string FormatToString(navigator::graph::BoundarySPtrType const& boundary);

    /**
     * @brief Marshal the output to a JSON string.
     *
     * @param[in] ouput Output parameters.
     * @return A Json string.
     */
    static std::string FormatToString(LocalMapGraphBuilder::Output const& output);

    /**
     * @brief Initializer
     *
     * @param [in] ret Pointer of retriever
     * @return true: init successful, false: init failed.
     */
    bool_t Init(RetrieverSPtrType const& ret);

    /**
     * @brief Access verbose flag.
     *
     * @return Verbose flag.
     */
    holo::bool_t GetVerbose() const noexcept;

    /**
     * @brief Assign verbose flag.
     *
     * @param[in] true: Print detail debug logs.
     *            false: Close detail debug logs(default value).
     */
    void SetVerbose(holo::bool_t const v) noexcept;

    /**
     * @brief Whether or not enable clip local map graph.
     *
     * @param t True, enable; false, disable
     */
    void EnableClipLMG(holo::bool_t const c) noexcept;

    /**
     * @brief build local map graph
     *
     * @param [in] input input info
     * @param [out] putput output info
     * @return true: Build successful, false: Build failed.
     */
    holo::bool_t Build(Input const& input, Output& output);

private:
    class LocalMapGraphBuilderInner;
    std::unique_ptr<LocalMapGraphBuilderInner> inner_;
};

using LocalMapGraphBuilderSPtr = std::shared_ptr<LocalMapGraphBuilder>;

/**
 * @}
 */
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_SERVICE_LOCAL_MAP_GRAPH_BUILDER_H_ */