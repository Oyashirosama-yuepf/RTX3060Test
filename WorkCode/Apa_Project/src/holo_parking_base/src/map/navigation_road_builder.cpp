/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_navi_road.h
 * @brief Define navi road info
 * @author wangminghui@holomatic.com
 * @date "2021-08-28"
 */
#include <glog/logging.h>
#include <holo/common/road_frame2.h>
#include <holo/parking/map/navigation_road_builder.h>
#include "geometry.h"

namespace holo
{
namespace map
{
    using ScalarType = holo::float64_t;
    using PointType = holo::geometry::Point3T<ScalarType>;
    using Distance = holo::float64_t;
    using CurveType = holo::geometry::CurveBezier<PointType, 1024U, 3U>;
    using RoadFrameType = holo::common::RoadFrame<CurveType, 1024>;
    struct DistanceParam
    {
        size_t lane_index;
        ScalarType     lane_start_distance;//unit:m
        ScalarType     lane_end_distance;//unit:m
        DistanceParam() : lane_index(0),
                            lane_start_distance(0.0),
                            lane_end_distance(0.0)
        {

        }
        ~DistanceParam() = default;
    };
    class NavigationRoadBuilder::NavigationRoadBuilderInner
    {
    public:
        NavigationRoadBuilderInner(RoadFrameType const &road_frame);
        holo::bool_t Process(Input const &input, Output &output);

    protected:
        holo::bool_t getNavigationRoadPointsByDistance(ScalarType const &start_distance, ScalarType const &length, ScalarType const &intervalconst, ScalarType const &tolerance, std::vector<NavigationRoadPoint> &navi_points);
         holo::bool_t  init();
        holo::bool_t initRoadDistances(RoadFrameType::const_iterator const &iterator, ScalarType &distance);
        holo::bool_t naviRoadPoints(RoadFrameType::const_iterator &lane, ScalarType const road_start_distance, ScalarType const intervalconst, ScalarType const tolerance, std::vector<NavigationRoadPoint> &navi_points);
        holo::bool_t naviBoundary(RoadFrameType::const_iterator &lane, std::vector<NavigationRoadPoint> &navi_points);
        holo::bool_t getUpSamplePointsByLane(RoadFrameType::const_iterator &lane, ScalarType const road_start_distance, std::vector<NavigationRoadPoint> &navi_points, ScalarType const intervalconst, ScalarType const tolerance);
        holo::bool_t getRoadIndexBydistance(ScalarType const distance, size_t &road_start, ScalarType &road_start_distance);
        holo::bool_t getDistanceByRoadFrame(const RoadFrameType::iterator &iterator, holo::int32_t &idx, ScalarType &distance);
        std::string formatToJsonString(Output const &output);
        void formatToPrint(Output const &output);
       

    private:
        std::vector<DistanceParam> road_distances_;
        RoadFrameType const &road_frame_; // navi  road raw data
    public:
        holo::bool_t verbose_ = true;
    }; // NavigationRoadBuilderInner

    std::string NavigationRoadBuilder::FormatToString(Input const &input)
    {
        std::stringstream stream;
        stream << "{\"start_distance\":" << input.start_distance
               << ", \"length\":" << input.length
               << ", \"intervalconst\":" << input.intervalconst
               << ", \"tolerance\":" << input.tolerance
               << "}";
        return stream.str();
    }

    std::string NavigationRoadBuilder::FormatToString(Output const &output)
    {
        std::string buffer = "\n";
        char buf[128] = {0};
        for (size_t j = 0; j < output.navigation_points.size(); j++)
        {
            const NavigationRoadPoint &point = output.navigation_points[j];
            snprintf(buf, sizeof(buf), "%lf,%lf,%lf,%lf,%lf\n", point.GetRefPoint().GetX(), point.GetRefPoint().GetY(),point.GetStartDistance(),point.GetLeftAvailableWidth(),point.GetRightAvailableWidth());
            buffer += buf;
        }
        std::stringstream stream;
        stream << "{\"size\":" << output.navigation_points.size()
               << ",\"array\":" << buffer
               << "}";
        return stream.str();
    }

    NavigationRoadBuilder::NavigationRoadBuilder()
    {
    }

    NavigationRoadBuilder::~NavigationRoadBuilder()
    {
        this->inner_ = nullptr;
    }
    void NavigationRoadBuilder::SetRoadFrame(RoadFrameType const &road_frame)
    {
        this->inner_ = std::unique_ptr<NavigationRoadBuilderInner>(new NavigationRoadBuilderInner(road_frame));
    }

    holo::bool_t NavigationRoadBuilder::GetVerbose() const noexcept
    {
        return this->inner_->verbose_;
    }

    void NavigationRoadBuilder::SetVerbose(holo::bool_t const v) const
    {
        this->inner_->verbose_ = v;
    }

    holo::bool_t NavigationRoadBuilder::Process(Input const &input, Output &output)
    {
        return this->inner_->Process(input, output);
    }

    holo::bool_t NavigationRoadBuilder::operator()(Input const &input, Output &output)
    {
        return this->inner_->Process(input, output);
    }

    NavigationRoadBuilder::NavigationRoadBuilderInner::NavigationRoadBuilderInner(RoadFrameType const &road_frame) : road_frame_(road_frame)
    {
        init();
    }
    std::string NavigationRoadBuilder::NavigationRoadBuilderInner::formatToJsonString(Output const &output)
    {
        std::string buffer = "\n";
        char buf[128] = {0};
        for (size_t j = 0; j < output.navigation_points.size(); j++)
        {
            const NavigationRoadPoint &point = output.navigation_points[j];
            snprintf(buf, sizeof(buf), "[%lf,%lf],", point.GetRefPoint().GetX(), point.GetRefPoint().GetY());
            buffer += buf;
        }
        std::stringstream stream;
        stream << "{\"size\":" << output.navigation_points.size()
               << ",\"geojson\"\n:" << buffer
               << "}";
        return stream.str();
    }
    void NavigationRoadBuilder::NavigationRoadBuilderInner::formatToPrint(Output const &output)
    {
        char buf[256] = {0};
        for (size_t i = 0; i < output.navigation_points.size(); i++)
        {
            const NavigationRoadPoint &point = output.navigation_points[i];
            snprintf(buf, sizeof(buf), "%lf,%lf,%lf,%lf,%lf\n", point.GetRefPoint().GetX(), point.GetRefPoint().GetY(), point.GetStartDistance(), point.GetLeftAvailableWidth(), point.GetRightAvailableWidth());
            LOG(INFO) << "[" << i << "]" << buf;
        }
    }
    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::Process(Input const &input, Output &output)
    {
        if (this->verbose_)
        {
            LOG(INFO) << "Process debug, input=" << NavigationRoadBuilder::FormatToString(input);
        }

        holo::bool_t const ok = this->getNavigationRoadPointsByDistance(input.start_distance, input.length, input.intervalconst, input.tolerance, output.navigation_points);
        if (!ok)
        {
            LOG(ERROR) << "Process fail, makeSpecialRoadBoundaries fail, input="
                       << NavigationRoadBuilder::FormatToString(input);
        }

        if (ok && this->verbose_)
        {
            LOG(INFO) << "Process debug, ouput=" << NavigationRoadBuilder::FormatToString(output);
        }
        return ok;
    }

    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::getNavigationRoadPointsByDistance(ScalarType const & start_distance, ScalarType const & length, ScalarType const & intervalconst, ScalarType const & tolerance, std::vector<NavigationRoadPoint> &navi_points)
    {
        if (length <=0 || start_distance < 0 || intervalconst < 0)
        {
            return false;
        }
        holo::bool_t ok = true;
        ScalarType end_distance = start_distance + length;
        size_t road_start_index = 0;
        ScalarType road_start_distance = 0.0;
        size_t road_end_index = 0;
        navi_points.clear();
        ok = ok && getRoadIndexBydistance(start_distance, road_start_index, road_start_distance);
        ok = ok && getRoadIndexBydistance(end_distance, road_end_index, road_start_distance);
        if (ok)
        {
            for (size_t i = road_start_index; i <= road_end_index; i++)
            {
                size_t lane_index = road_distances_[i].lane_index;
                road_start_distance = road_distances_[i].lane_start_distance;
                RoadFrameType::const_iterator lane = road_frame_.GetLane(lane_index);
                naviRoadPoints(lane, road_start_distance, intervalconst, tolerance, navi_points);
            }
        }
        return true;
    }

    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::naviRoadPoints(RoadFrameType::const_iterator &lane, ScalarType const road_start_distance, ScalarType const intervalconst, ScalarType const tolerance, std::vector<NavigationRoadPoint> &navi_points)
    {
        holo::bool_t ret = false;
        std::vector<NavigationRoadPoint> navi_lane_points;
        if (getUpSamplePointsByLane(lane, road_start_distance, navi_lane_points, intervalconst, tolerance))
        {
            ret = naviBoundary(lane, navi_lane_points);
            if (ret)
            {
                navi_points.insert(navi_points.end(), navi_lane_points.begin(), navi_lane_points.end());
            }
        }
        return ret;
    }

    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::getUpSamplePointsByLane(RoadFrameType::const_iterator &lane, ScalarType const road_start_distance, std::vector<NavigationRoadPoint> &navi_points, ScalarType const intervalconst, ScalarType const tolerance)
    {
        std::vector<holo::float32_t> distances;
        std::vector<PointType> lane_points;
        holo::container::Vector<PointType, 65536> temp_lane_points = lane->GetMapAttributes().center_points;
        if (temp_lane_points.empty())
        {
            LOG(ERROR) << "lane_points size = " << temp_lane_points.size();
        }
        for (size_t i = 0; i < temp_lane_points.size(); i++)
        {
            lane_points.push_back(temp_lane_points[i]);
        }
        holo::bool_t ret = ::holo::map::geometry::UpSampleRefPointsByIntervalconst(lane_points, intervalconst, distances, tolerance);
        if (ret == false || lane_points.size() != distances.size())
        {
            LOG(ERROR) << "UpSampleRefPointsByIntervalconst ret = "<< ret <<", points.size =" << lane_points.size()<< "distances.size = :"<< distances.size();
            return false;
        }
        for (size_t i = 0; i < lane_points.size(); i++)
        {
            NavigationRoadPoint navi_point;
            navi_point.SetRefPoint(lane_points[i]);
            ScalarType distance = road_start_distance + distances[i];
            navi_point.SetStartDistance(distance);
            if (ret)
            {
                navi_points.push_back(navi_point);
            }
            else
            {
                break;
            }
        }
        return ret;
    }

    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::naviBoundary(RoadFrameType::const_iterator &lane, std::vector<NavigationRoadPoint> &navi_points)
    {
        holo::bool_t ret = true;
        auto const &left_boundary = lane->GetLeftBoundaryPtr();
        auto const &right_boundary = lane->GetRightBoundaryPtr();
        std::vector<PointType> left_boundary_points;
        std::vector<PointType> right_boundary_points;

        if (left_boundary && left_boundary->IsValid())
        {
            const CurveType &left_curve_type = left_boundary->GetCurve();
            for (size_t i = 0; i < left_curve_type.size(); i++)
            {
                left_boundary_points.push_back(left_curve_type[i]);
            }
        }
        else 
        {
             LOG(ERROR) << "id = "<<lane.GetId()<<",left_boundary is empty";
        }
        if (right_boundary && right_boundary->IsValid())
        {
            const CurveType &right_curve_type = right_boundary->GetCurve();
            for (size_t i = 0; i < right_curve_type.size(); i++)
            {
                right_boundary_points.push_back(right_curve_type[i]);
            }
        }
        else 
        {
            LOG(ERROR) << "id = "<<lane.GetId()<< ",right_boundary is empty";
        }
        
        for (size_t i = 0; i < navi_points.size(); i++)
        {
            NavigationRoadPoint &road_point = navi_points[i];
            std::size_t first_id = 0;
            std::size_t second_id = 0;
            PointType project_point;
            ScalarType left_min_distance = 0.0;
            ScalarType right_min_distance = 0.0;
            bool is_outside = false;
            if(left_boundary_points.size()>0)
            {
                ret = ret && holo::map::geometry::CalculateDistanceToPoints2D(road_point.GetRefPoint(), left_boundary_points, first_id, second_id, project_point, left_min_distance, is_outside);
            }
            if (right_boundary_points.size() > 0)
            {
                ret = ret && holo::map::geometry::CalculateDistanceToPoints2D(road_point.GetRefPoint(), right_boundary_points, first_id, second_id, project_point, right_min_distance, is_outside);
            }
            if (ret)
            {
                road_point.SetLeftAvailableWidth(left_min_distance);
                road_point.SetRightAvailableWidth(right_min_distance);
            }
            else
            {
                LOG(ERROR) << "naviBoundary ret = "<<ret<<","<<left_boundary_points.size()<<","<<right_boundary_points.size() <<","<<left_min_distance<<","<<right_min_distance;
                return false;
            }
        }
        return true;
    }

    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::init()
    {
        ScalarType distance = 0.0;
        return initRoadDistances(road_frame_.GetDefaultLane(),distance);
    }
    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::initRoadDistances(const RoadFrameType::const_iterator& iterator,ScalarType& distance)
    {
        if (iterator.IsValid())
        {
            DistanceParam param;
            param.lane_index = iterator.GetId();
            param.lane_start_distance = distance;
            param.lane_end_distance = distance + iterator->GetLength();
            distance += iterator->GetLength();
            road_distances_.push_back(param);
            if (this->verbose_)
            {
                char buf[128] = {0};
                std::string buffer;
                snprintf(buf, sizeof(buf),"%lf,%lf,pointSize = %lu,",param.lane_start_distance,param.lane_end_distance,iterator->GetMapAttributes().center_points.size());
                buffer += buf;
                for (size_t i = 0; i < iterator->GetMapAttributes().center_points.size(); i++)
                {
                    snprintf(buf, sizeof(buf),"%lf,%lf",iterator->GetMapAttributes().center_points[i].GetX(),iterator->GetMapAttributes().center_points[i].GetY());
                    buffer += buf;
                }
                LOG(INFO) << " lane_index:"<<param.lane_index<<",ExternalId: "<<iterator->GetExternalId()<<",road_distances[" << road_distances_.size()-1 << "] = " <<param.lane_start_distance <<","<< param.lane_end_distance;
            }
            initRoadDistances(iterator.GetNext(),distance);
            return true;
        }
        return true;
    }

    holo::bool_t NavigationRoadBuilder::NavigationRoadBuilderInner::getRoadIndexBydistance(ScalarType const distance, size_t &road_index, ScalarType &road_start_distance)
    {
        road_index = 0;
        road_start_distance = 0;
        if(road_distances_.empty() || distance < 0)
        {
             LOG(ERROR) << " getRoadIndexBydistance error: road_distances_.size:"<<road_distances_.size();
            return false;
        }
        for (std::size_t i = 0; i < road_distances_.size(); i++)
        {
            if (distance < (road_distances_[i].lane_end_distance - 0.1))
            {
                road_index = i;
                road_start_distance = road_distances_[road_index].lane_start_distance;
                if (this->verbose_)
                {
                    LOG(INFO) << " distance:" << distance <<",road_index = "<<road_index<< ",road_distances[" << road_distances_[road_index].lane_start_distance<<","<< road_distances_[road_index].lane_end_distance<<"]";
                }
                return true;
            }
        }
        road_index = road_distances_.size() - 1;
        road_start_distance = road_distances_[road_index].lane_start_distance;
        if (this->verbose_)
        {
             LOG(INFO) << " distance:" << distance <<",road_index = "<<road_index<< ",road_distances[" << road_distances_[road_index].lane_start_distance<<","<< road_distances_[road_index].lane_end_distance<<"]";
        }
        return true;
    }
}  // namespace parking
}  // namespace holo
