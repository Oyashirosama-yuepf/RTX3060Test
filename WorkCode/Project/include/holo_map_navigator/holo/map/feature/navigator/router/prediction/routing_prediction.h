/*
 *  \brief routing prediction: predict the route when user is not specified
 *  \author Pang Yibo(pangyibo@holomaitc.com)
 *  \date 2018-11-20
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_PREDICTION_ROUTING_PREDICTION_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_PREDICTION_ROUTING_PREDICTION_H_

#include <holo/map/common/access.h>
#include <holo/map/common/common_define.h>

#include <holo/map/common/match_info.h>
namespace holo
{
namespace map
{
class RouterConfig;
class RoutingPrediction
{
public:
    // Constructor
    RoutingPrediction();
    // Destructor
    ~RoutingPrediction() = default;

public:
    /**
     * @brief Initializer
     *
     * @param [in] _ptr_ret pointer of retriever
     * @param [in] _ptr_config pointer of config
     * @return true
     * @return false
     */

    bool Init2(const RetrieverSPType& _ptr_ret, const std::shared_ptr<RouterConfig>& _ptr_router_config);
    /**
     * @brief Start predict
     *
     * @param [in] _match_info match info
     * @param [out] _ver_links predict links
     * @return true
     * @return false
     */
    bool StartPredict(const MapMatchInfo& _match_info, std::vector<IdType>& _ver_links);
    /**
     * @brief Update predict
     *
     * @param [in] _match_info match info
     * @return true
     * @return false
     */
    bool UpdatePredict(const MapMatchInfo& _match_info);
    /// stop predict
    void StopPredict();
    /// is work status
    bool IsWorking() const;

private:
    /// init data
    bool InitData();
    /**
     * @brief get referene point of matched link
     *
     * @param [in] _match_info match info
     * @param [out] _points vector of link points
     * @return true
     * @return false
     */
    bool GetRefPoint(const MapMatchInfo& _match_info, std::vector<format::GeoPoint>& _points) const;
    /**
     * @brief Calculate the projection of a point to a line and return the
     * distance from the projection point to the end of the line
     *
     * @param [in] _match_info match info
     * @param [in] _points vector of line points
     * @param [out] _distance distance from the projection
     *              point to the end of the line
     * @return true
     * @return false
     */
    bool CalcDistancePointToLineEnd(const MapMatchInfo& _match_info, const std::vector<format::GeoPoint>& _points,
                                    Distance& _distance);
    /**
     * @brief Infer links of predict route
     *
     * @param [in] _match_info match info
     * @param [in] _distance distance from the projection
     *              point to the end of the matched link
     * @param [out] _links links
     * @return true
     * @return false
     */
    bool InferPredictLinks(const MapMatchInfo& _match_info, const Distance _distance,
                           std::vector<IdType>& _links);
    /**
     * @brief select one link that user most likely to drive
     *
     * @param [in] _links links can be selected
     * @return the link has been selected
     */

    IdType SelectPredictLink(const std::vector<IdType>& _links);
    /**
     * @brief judge whether it is off route
     *
     * @param [in] _match_info match info
     * @return true
     * @return false
     */
    bool IsOffRoute(const MapMatchInfo& _match_info);
    /**
     * @brief calc the distance from the current position to the end of route and check if near to toll booth
     *
     * @param [in] _match_info match info
     * @param [out] _distance distance info
     * @param [out] _near_toll_booth near to toll booth: true; otherwise: false
     * @return true
     * @return false
     */
    bool CalcDistanceCurPosToRouteEnd(const MapMatchInfo& _match_info, Distance& _distance,
                                      bool& _near_toll_booth);
    /**
     * @brief delete the passed links
     *
     * @param [in] _match_info match info
     * @return true
     * @return false
     */
    bool DeletePassedLinks(const MapMatchInfo& _match_info);

    /**
     * @brief predict route
     *
     * @param [in] _match_info match info
     * @param [out] _ver_links predict links
     * @return true
     * @return false
     */
    bool PredictRoute(const MapMatchInfo& _match_info, std::vector<IdType>& _ver_links);
    /**
     * @brief  Re predict route
     *
     * @param [in] _match_info match info
     * @return true
     * @return false
     */
    bool RePredictRoute(const MapMatchInfo& _match_info);
    /**
     * @brief  extend route
     *
     * @param [in] _distance extend length
     * @return true
     * @return false
     */
    bool ExtendPredictRoute(const Distance _distance);

private:
    /// Pointer of retriever
    RetrieverSPType ptr_ret_;
    /// Pointer of config
    // PtrConfig ptr_config_;
    std::shared_ptr<RouterConfig> ptr_router_config_;
    /// links of predict route
    std::vector<IdType> ver_links_;
    /// predict flag
    bool start_work_flag_;
    /// routing prediction distance
    Distance prediction_distance_;
};
typedef std::shared_ptr<RoutingPrediction> PtrRoutingPredict;
}  // namespace map
}  // namespace holo
#endif  // HOLO_MAP_FEATURE_NAVIGATOR_ROUTER_PREDICTION_ROUTING_PREDICTION_H_
