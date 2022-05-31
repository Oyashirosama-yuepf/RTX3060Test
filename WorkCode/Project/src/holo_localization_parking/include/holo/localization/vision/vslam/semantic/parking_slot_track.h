/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_slot_track.h
 * @brief this file defines common_types for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com), Heiko Yu (yuchangsong@holomatic.com), Changxi
 * Cheng(chengchangxi@holomatic.com)
 * @date 2021-02-25
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_TRACK_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_TRACK_H_

#include <holo/localization/vision/vslam/common_types.h>

namespace holo
{
namespace localization
{
namespace vision
{
namespace vslam
{
namespace semantic
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief define parking slot track
 *
 */
struct ParkingSlotTrack
{
    /**
     * @brief define state of track
     */
    enum class State
    {
        CANDIDATE = 0,  ///< be seen for the first time
        FRESH     = 1,  ///< can be add to factor graph with all its measurement
        LIVE      = 2,  ///< be tracked sequentially
    };

    /// @brief define single track measurment. key: frame id, value: timestamp and the slot in body frame
    // @todo make Measurement be a struct chengchangxi@holomatic.com
    using Measurement = std::pair<uint64_t, std::pair<common::Timestamp, ParkingSlotType>>;

    /**
     * @brief dfeine indexed vertex
     *
     */
    struct IndexedVertex
    {
        uint64_t id;
        Point3   point;

        /**
         * @brief Construct a new Indexed Vertex object
         *
         * @param _id
         * @param _point
         */
        IndexedVertex(uint64_t _id = 0, const Point3& _point = Point3::Zero()) : id(_id), point(_point)
        {
        }
    };

    /**
     * @brief define variables
     *
     */
    int64_t                  id        = -1;                         ///< track id
    common::Timestamp        timestamp = common::Timestamp(0u, 0u);  /// timestamp of the latest measurement in track
    int64_t                  frame_id  = -1;                         ///< frame id of the latest measurement in track
    int64_t                  plane_id  = -1;                         ///< plane id of the latest measurement in track
    ParkingSlotType          optimized_parking_slot;                 ///< the optimized parking slot in world frame
    std::vector<Measurement> measurements;                           ///< all measurement
    State                    state = State::CANDIDATE;               ///< state

    /**
     * @brief Construct a new Parking Slot Track object
     *
     */
    ParkingSlotTrack()
    {
    }

    /**
     * @brief Get the Vertices object
     *
     * @details this method assumes that the track has been initialized, i.e. id >= 0
     *
     * @param index index of the measurement vector
     * @return std::vector<IndexedVertex>
     */
    std::vector<IndexedVertex> GetIndexedVertices(size_t index) const
    {
        if (index > measurements.size())
        {
            throw std::runtime_error("GetIndexedVertices --- given index is out of measurements' range.");
        }
        std::vector<IndexedVertex> vertices;
        const auto&                parking_slot = measurements.at(index).second.second;

        // front vertices, index starts with [0]
        vertices.emplace_back(Utility::HashId(id, 0), parking_slot.vertices[0u]);
        vertices.emplace_back(Utility::HashId(id, 1), parking_slot.vertices[1u]);

        // rear vertices, index starts with [2]
        if (parking_slot.is_rear_vertex_available)
        {
            vertices.emplace_back(Utility::HashId(id, 2), parking_slot.vertices[2u]);
            vertices.emplace_back(Utility::HashId(id, 3), parking_slot.vertices[3u]);
        }

        // center vertex, index starts with [4]
        if (parking_slot.is_center_vertex_available)
        {
            vertices.emplace_back(Utility::HashId(id, 4), parking_slot.center_vertex);
        }

        return vertices;
    }

    /**
     * @brief Get the Optimized Parking Slot object
     *
     * @details the index of vertex should be consistent with the one used in `GetIndexedVertices(...)`
     *
     * @param values
     * @return boost::optional<ParkingSlotType>
     */
    boost::optional<ParkingSlotType> GetOptimizedParkingSlot(const Values& values) const
    {
        if (measurements.empty())
        {
            return boost::none;
        }

        ParkingSlotType out = measurements.back().second.second;

        out.id              = id;  // track id
        const auto vertices = GetIndexedVertices(0);

        bool_t updated = false;
        for (const auto& vertex : vertices)
        {
            if (values.exists(S(vertex.id)))
            {
                const Point3   point        = HoloGtsam::Convert(values.at<gtsam::Point3>(S(vertex.id)));
                const uint64_t vertex_index = Utility::UnHashId(vertex.id).second;
                if (vertex_index < 4u)
                {
                    out.vertices[vertex_index] = point;
                }
                else if (vertex_index == 4u)
                {
                    out.center_vertex = point;
                }
                else
                {
                    throw std::out_of_range("set vertex out of range");
                }
                updated = true;
            }
        }

        if (!updated)
        {
            LOG(WARNING) << "A track tries to update a parkingslot that is NOT optimized.";
            return boost::none;
        }
        return out;
    }

    /**
     * @brief Create a Track object
     *
     * @param _timestamp
     * @param _frame_id
     * @param _plane_id
     * @param _parking_slot
     * @return ParkingSlotTrack
     */
    static ParkingSlotTrack Create(const common::Timestamp& _timestamp, const int64_t _frame_id,
                                   const int64_t _plane_id, const ParkingSlotType& _parking_slot)
    {
        return ParkingSlotTrack(next_id++, _timestamp, _frame_id, _plane_id, _parking_slot, State::CANDIDATE);
    }

private:
    /**
     * @brief Construct a new Parking Slot Track object
     *
     * @details please be aware of and be responsible for what you're doing
     * @param _id
     * @param _timestamp
     * @param _frame_id
     * @param _plane_id
     * @param _parking_slot
     * @param _state
     */
    ParkingSlotTrack(const int64_t _id, const common::Timestamp& _timestamp, const int64_t _frame_id,
                     const int64_t _plane_id, const ParkingSlotType& _parking_slot, const State _state)
      : id(_id)
      , timestamp(_timestamp)
      , frame_id(_frame_id)
      , plane_id(_plane_id)
      , measurements({std::make_pair(static_cast<uint64_t>(frame_id), std::make_pair(timestamp, _parking_slot))})
      , state(_state)
    {
    }

    // @todo needs to be reset
    static int64_t next_id;
};

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_PARKING_SLOT_TRACK_H_
