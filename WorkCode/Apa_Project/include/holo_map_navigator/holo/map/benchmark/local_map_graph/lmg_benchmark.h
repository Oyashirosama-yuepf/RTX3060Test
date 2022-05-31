/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file lmg_benchmark.h
 * @brief define benchmark for local map graph.
 * @author liuqikang(liuqikang@holomaitc.com)
 * @date 2022-02-23
 */

#ifndef HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_BENCHMARK_H_
#define HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_BENCHMARK_H_

#include "holo/map/feature/local_map_graph/local_map_graph_builder.h"

namespace holo
{
namespace map
{
namespace navigator
{
namespace graph
{
class LmgBenchmark
{
public:
    using RetrieverSPtrType     = holo::map::service::client::engine::helper::raw::RawRetrieverSPtrType;
    using LocalMapGraphType     = holo::map::navigator::graph::LocalMapGraphType;
    using LocalMapGraphSPtrType = holo::map::navigator::graph::LocalMapGraphSPtrType;
    using FeatureIdType         = LocalMapGraphType::FeatureIdType;
    using FeatureBaseSPtrType   = LocalMapGraphType::FeatureBaseSPtrType;
    using PairFeatureType       = std::pair<FeatureIdType, FeatureBaseSPtrType>;

    enum class FeatureType : holo::uint8_t
    {
        FEATURE_LINK                = 0,
        FEATURE_LANE                = 1,
        FEATURE_BOUNDARY            = 2,
        FEATURE_LIGHT               = 3,
        FEATURE_STOPLINE            = 4,
        FEATURE_MARKING             = 5,
        FEATURE_SIGN                = 6,
        FEATURE_PEDESTRIAN_CROSSING = 7
    };

    LmgBenchmark();
    virtual ~LmgBenchmark();

    LmgBenchmark(LmgBenchmark const&) = delete;
    LmgBenchmark(LmgBenchmark&&)      = delete;
    LmgBenchmark& operator=(LmgBenchmark const&) = delete;
    LmgBenchmark& operator=(LmgBenchmark&&) = delete;

    /**
     * @brief Initializer
     *
     * @param [in] ret Pointer of retriever
     * @return true: init successful, false: init failed.
     */
    holo::bool_t Init(RetrieverSPtrType const& ret);

    void Process(LocalMapGraphSPtrType const& lmg);

private:
    class LmgBenchmarkInner;
    std::unique_ptr<LmgBenchmarkInner> inner_;
};
}  // namespace graph
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif  // HOLO_MAP_FEATURE_LOCAL_MAP_GRAPH_LMG_BENCHMARK_H_