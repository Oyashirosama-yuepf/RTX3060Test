/*!
 *  \brief
 *  \author Hao Wentian(haowentian@holomaitc.com)
 *  \date 2018-08-04
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */
#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_ADVISOR_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ADVICE2_ADVISOR_H_

#include <memory>

#include <holo/common/timestamp.h>

#include <holo/map/common/common_define.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/feature/navigator/advice/advice.h>
#include <holo/map/feature/navigator/advice/lane_navigator/lane_navigator.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_analysis/lane_path_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator/scene_analyzer/scene_analyzer_controller.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_evaluation/evaluator_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/lane_path_expector/expector_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/region_model_info/region_model_manager.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/scene_analysis/scene_analyzer_manager.h>
#include <holo/map/feature/navigator/advice/lane_path_expector.h>
#include <holo/map/feature/navigator/advice/lane_navigator_v2/state_region_info/state_region_extractor.h>

namespace holo
{
namespace map
{
namespace navigator
{
namespace advice
{
/**
 * @brief Class advisor for advice related service
 *
 */
class Advisor2 : public std::enable_shared_from_this<Advisor2>
{
public:
    using Ptr                    = std::shared_ptr<Advisor2>;
    using RegionModelInfoType    = holo::map::navigator::advice::RegionModelInfo;
    using RegionModelInfoVecType = std::vector<RegionModelInfoType>;
    using LanePathSPtrType       = std::shared_ptr<LanePath>;
    using LanePathSPtrVecType    = std::vector<LanePathSPtrType>;
    using Advice2SPtrType        = std::shared_ptr<Advice2>;
    using IdDistancePairType     = std::pair<holo::uint64_t, holo::float64_t>;
    using SceneSketchSPtrType    = std::shared_ptr<scene::SceneSketch>;
    using SceneSketchSPtrVecType = std::vector<SceneSketchSPtrType>;
    using SceneAnalyzerOutput2 = holo::map::navigator::advice::scene::SceneAnalyzerManager::Output;
    using LanePathManagerType    = holo::map::navigator::advice::lanepath::LanePathManager;
    using StateRegionExtractorType = holo::map::navigator::advice::StateRegionExtractor;
    using StateRegionExtractorSPtrType = std::shared_ptr<StateRegionExtractorType>;
    using MapMatchingInfoType = holo::map::MapMatchInfo;

    struct Input
    {
        RouteInfo2::Ptr         route_info = nullptr;
        holo::map::MapMatchInfo matching_info;
        holo::common::Timestamp timestamp;
        holo::common::Odometryd odometry;
        holo::bool_t            enable_reparing = false;
    };
    /**
     * @brief Definition for output of advisor
     *
     */
    struct Output
    {
        Advice2SPtrType advice = nullptr;
    };

public:
    /**
     * @brief Constructor
     *
     */
    Advisor2()  = default;
    ~Advisor2() = default;

    /**
     * @brief Initializer
     *
     * @param [in] _ptr_ret pointer of retriever
     * @param [in] _ptr_config pointer of config
     * @return true if all input arguments are valid
     */
    bool Init(const RetrieverSPType& ret);

    /**
     * @brief
     *
     * @param match_info
     * @param route_info
     * @param out
     * @return true
     * @return false
     */
    bool Run(Advisor2::Input in, Advisor2::Output& out);

    /**
     * @brief Run advisor to generate navigtion info
     *
     * @param in Input of advice
     * @param out Output of advice
     * @return holo::bool_t True, succeed; false, otherwise;
     */
    holo::bool_t Run2(Advisor2::Input in, Advisor2::Output& out);

    /**
     * @brief Set the Verbose for debuging information
     *
     * @param v Whether or not set verbose
     */
    void SetVerbose(holo::bool_t v);

private:
    /**
     * @brief Calculate scene via route path
     *
     * @param in Input of advice, especaiily route info
     * @param scene_sketchs Scene sketch array
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t runSceneAnalyzer(Advisor2::Input const& in, std::vector<SceneSketch>& scene_sketchs);

    /**
     * @brief Calcuate scene via route path
     *
     * @param in Input of advice, especially route info
     * @param scene_sketchs Scene sketch array
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t runSceneAnalyzerV2(Advisor2::Input const& in, SceneAnalyzerOutput2& output);

    /**
     * @brief Run lane navigator
     *
     * @param in
     * @param out
     * @return holo::bool_t
     */
    holo::bool_t runLaneNavigator(Advisor2::Input const& in, std::vector<SceneSketch>const& scene_sketchs, Advice2::Ptr advice);

    /**
     * @brief Run lane navigator
     *
     * @param in
     * @param out
     * @return holo::bool_t
     */
    //holo::bool_t runLaneNavigator2(Advisor2::Input const& in, SceneSketchSPtrVecType const& scene_sketchs,
    //                               Advice2::Ptr advice);

    /**
     * @brief Run lane path generator
     *
     * @param in
     * @param out
     * @return holo::bool_t
     */
    holo::bool_t runLanePathGenerator(Advisor2::Input const& in, SceneSketchSPtrVecType const& scene_sketchs,
                                   Advice2::Ptr advice);
    
    /**
     * @brief Run generating state region
     * 
     * @param in 
     * @param scene_sketchs 
     * @param advice 
     * @return holo::bool_t 
     */
    holo::bool_t runStateRegionExtractor(Advisor2::Input const& in, SceneSketchSPtrVecType const& scene_sketchs,
                                   Advice2::Ptr advice);

    /**
     * @brief Run generating region model
     * 
     * @param in 
     * @param scene_sketchs 
     * @param advice 
     * @return holo::bool_t 
     */
    holo::bool_t runRegionModel(Advisor2::Input const& in, SceneSketchSPtrVecType const& scene_sketchs,
                                Advice2::Ptr advice);

    /**
     * @brief Calcualte the Odometry Status
     *
     * @return holo::bool_t
     */
    holo::bool_t setOdometryStatus(Advice2::Ptr advice);

    /**
     * @brief Calcualte the Expected Lane Sequence
     *
     * @return holo::bool_t
     */
    holo::bool_t calculateExpectedLaneSequence(Advice2::Ptr advice);

    /**
     * @brief Calcualte expected lane paths
     *
     * @param advice
     * @return holo::bool_t
     */
    holo::bool_t calculateExpectedLanePaths(Advisor2::Input const& in, std::vector<SceneSketch> const& scene_sketchs, Advice2::Ptr advice);

    /**
     * @brief Calcualte expected lane paths version 2
     *
     * @param in Advisor input
     * @param scene_sketchs Scene sketchs array
     * @param advice Calcualted expected lane paths ids in advice
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t calculateExpectedLanePathsV2(Advisor2::Input const&                 in,
                                              std::vector<SceneSketchSPtrType> const& scene_sketchs,
                                              Advice2::Ptr                           advice);

    /**
     * @brief Set the whether or not on HD map
     *
     * @return holo::bool_t
     */
    holo::bool_t calculateIsOnHDMap(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief
     *
     * @param advice
     * @return holo::bool_t
     */
    holo::bool_t calculateOnRouteStatus(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief
     *
     * @return holo::bool_t
     */
    holo::bool_t calculateDistanceToDestination(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief
     *
     * @return holo::bool_t
     */
    holo::bool_t calculateDistanceOutHDMap(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief Calculate position statues from odometry
     *
     * @param in
     * @param advice
     * @return holo::bool_t
     */
    holo::bool_t calculatePostionStatus(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief Calculate history trace
     *
     * @param in
     * @param advice
     * @return holo::bool_t
     */
    holo::bool_t calculateHistoryTrace(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief Calculate navigation distance attributes
     *
     * @param in
     * @param advice
     * @return holo::bool_t
     */
    holo::bool_t calculateDistanceAttribute(Advisor2::Input const& in, Advice2::Ptr advice);

    /**
     * @brief
     *
     * @param link_ids
     * @param link
     * @return holo::bool_t
     */
    holo::bool_t makeValidLaneGroup(RouteInfo2::Ptr route_info, VecLinkIdType link_ids, format::PtrLaneGroup& link);

    /**
     * @brief Make hard state regions
     * 
     * @param paths 
     * @return holo::bool_t 
     */
    holo::bool_t makeHardStateRegions(LanePathSPtrVecType& paths);

    /**
     * @brief Reset expectr manager via scene sketchs
     *
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t resetExpectManager(std::vector<SceneSketchSPtrType> const& scene_sketchs);

    /**
     * @brief Reset evaluators manager via scenes
     *
     * @param scenes Scenes
     * @return holo::bool_t True, succeed; false, otherwise
     */
    holo::bool_t resetEvaluatorManager(std::vector<SceneSketchSPtrType> const& scenes);

private:
    LaneNavigator::Ptr    lane_navigator_ = nullptr;
    holo::bool_t           verbose_        = false;
    RetrieverSPType        retriever_      = nullptr;
    std::deque<LaneIdType> history_lane_ids_;
    
    LanePathManagerType lane_path_manager_;
    LanePathExpector       lane_path_expector_;
    SceneAnalyzerController scene_analyzer_controller;

    ExpectorManager             expector_manager_;
    EvaluatorManager            evaluator_manager_;
    scene::SceneAnalyzerManager scene_analzyer_manager_;

    StateRegionExtractorSPtrType state_region_extractor_ = nullptr;

    /// State region harder
    StateRegionHarder state_region_harder_;

    ///
    RegionModelManager region_model_manager_;
};

typedef std::shared_ptr<Advisor2> PtrAdvisor;

}  // namespace advice
}  // namespace navigator
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_ADVISOR_ADVISOR_H_ */
