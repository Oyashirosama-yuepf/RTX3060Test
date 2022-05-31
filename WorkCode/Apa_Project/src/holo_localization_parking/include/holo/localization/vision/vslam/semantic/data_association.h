/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file data_association.h
 * @brief this file defines data association for semantic slam
 * @author Yanwei Du (duyanwei@holomatic.com)
 * @author Changxi Cheng (chengchangxi@holomatic.com)
 * @date 2021-02-25
 */

#ifndef HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_DATA_ASSOCIATION_H_
#define HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_DATA_ASSOCIATION_H_

#include <holo/geometry/box2.h>
#include <holo/localization/vision/common/holo_gtsam.h>
#include <holo/localization/vision/vslam/semantic/associator.h>
#include <holo/localization/vision/vslam/semantic/common_types.h>

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
/**
 * @addtogroup semantic
 * @{
 *
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Data association main class
 * @details associate plane and associate tracks
 * @todo make it functional
 *
 */

class DataAssociation
{
public:
    using Ptr      = std::shared_ptr<DataAssociation>;
    using ConstPtr = std::shared_ptr<const DataAssociation>;

    /**
     * @brief define parameters
     *
     */
    struct Parameters
    {
        // @todo need more parameters in future (chengchangxi@holomatic.com)
        Scalar             plane_distance_threshold = 3.0;                                    ///< meter
        BirdviewParameters birdview_parameters      = BirdviewParameters::GenerateExample();  ///< birdview parameters
        bool_t             show_tracking            = false;
        bool_t             show_matching            = false;
        bool_t             enable_step              = false;
        Scalar             avm_visible_range        = 12.0;  ///< meter
        Scalar             avm_image_width          = 640;   ///< pixel
        Scalar             avm_image_height         = 640;   ///< pixel

        /**
         * @brief Construct a new Parameters object
         *
         */
        Parameters()
        {
        }

        /**
         * @brief output stream for Parameters
         *
         * @param os std::ostream&
         * @param params parameters
         * @return std::ostream&
         */
        friend std::ostream& operator<<(std::ostream& os, const Parameters& params)
        {
            os << "DataAssociationParameters:"
               << "\n plane_distance_threshold = " << params.plane_distance_threshold
               << "\n birdview_parameters = " << params.birdview_parameters
               << "\n show_tracking = " << params.show_tracking << "\n show_matching = " << params.show_matching
               << "\n enable_step = " << params.enable_step << "\n avm_visible_range = " << params.avm_visible_range
               << "\n avm_image_width = " << params.avm_image_width
               << "\n avm_image_height = " << params.avm_image_height << std::endl;
            return os;
        }

        /**
         * @brief generate parameter example
         *
         * @return Parameters
         */
        static Parameters GenerateExample();

        /**
         * @brief load parameters from yaml
         *
         * @param node
         * @return Parameters
         */
        static Parameters LoadFromYaml(const yaml::Node& node);
    };

    /**
     * @brief semantic measurements
     *
     */
    struct State
    {
        std::vector<ParkingSlotTrack>      tracks;             ///< all parking slot tracks
        std::unordered_map<int64_t, Plane> plane_id_to_plane;  ///< all plane in navigation coordinate
        int64_t current_plane_id;   ///< newest associated plane id, less than zero means no plane estimated for current
                                    ///< state
        uint64_t current_frame_id;  ///< current frame id

        State(const std::vector<ParkingSlotTrack>&      _tracks            = {},
              const std::unordered_map<int64_t, Plane>& _plane_id_to_plane = {}, int64_t _current_plane_id = 0,
              int64_t _current_frame_id = 0)
          : tracks(_tracks)
          , plane_id_to_plane(_plane_id_to_plane)
          , current_plane_id(_current_plane_id)
          , current_frame_id(_current_frame_id)
        {
        }
        // @todo the definitions are slightly ambiguous, can we define them all in body coordiante ???
    };

    /**
     * @brief Construct a new Data Association object
     *
     * @param parameters
     */
    DataAssociation(const Parameters& parameters = Parameters());

    /**
     * @brief core algorithm happens here
     *
     * @param[in, out] state the old semantic track state
     * @param parking_slot_frame parking slot frame in image plane coordinate
     * @param wTb body pose in navigation coordinate
     * @param frame_id frame id
     */
    void Run(State& state, const ParkingSlotFrameType& parking_slot_frame, const Pose3& wTb, int64_t frame_id);

    /**
     * @brief Matches the current frame with the visible slot map
     *
     * @param slot_map visible slot map
     * @param parking_slot_frame parking slot frame in image plane coordinate
     * @param wTb body pose in navigation coordinate
     * @param frame_id frame id
     */
    SlotMapFactorMeasurement RunParkingSlotGlobalMatching(const SlotMapPtr&           slot_map,
                                                          const ParkingSlotFrameType& parking_slot_frame,
                                                          const Pose3& wTb, int64_t frame_id);

private:
    /**
     * @brief convert ParkingSlotFrame from image plane to body coordinate
     *
     * @param in ParkingSlotFrame in image plane
     * @return ParkingSlotFrameType in body cooridinate
     */
    ParkingSlotFrameType convertToBody(const ParkingSlotFrameType& in) const;

    /**
     * @brief Determine whether a parking slot is in a avm image
     *
     * @param parking_slot parking slot in avm frame
     * @return bool
     */
    bool_t isParkingSlotInAVM(const holo::common::ParkingSlotd& parking_slot) const;

    /**
     * @brief associate plane
     *
     * @param parking_slot_frame parking slot frame in body coordinate
     * @param wTb body pose in navigation coordinate
     * @return boost::optional<Plane>
     */
    void associatePlane(State& state, const ParkingSlotFrameType& parking_slot_frame, const Pose3& wTb) const;

    /**
     * @brief compute plane in navigation frame
     *
     * @param parking_slot_frame parking slot frame in body coordinate
     * @param wTb body pose in navigation coordinate
     * @return gtsam::OrientedPlane3
     */
    boost::optional<gtsam::OrientedPlane3> estimatePlane(const ParkingSlotFrameType& parking_slot_frame,
                                                         const Pose3&                wTb) const;

    /**
     * @brief associate tracks
     *
     * @param[in, out] state the old semantic track state
     * @param parking_slot_frame parking slot in body coordinate
     * @param wTb body pose in navigation coordinate
     * @param frame_id frame id
     * @param plane_id plane id
     */
    void associateTracks(State& state, const ParkingSlotFrameType& parking_slot_frame, const Pose3& wTb,
                         int64_t frame_id, int64_t plane_id) const;

    Parameters      parameters_;
    Visualizer      visualizer_;
    Associator::Ptr associator_;
    // @todo move following variable to sliding_window_state, make this class FP (chengchangxi@holomatic.com)
};

/**
 * @}
 *
 */

}  // namespace semantic

}  // namespace vslam

}  // namespace vision

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_VISION_VSLAM_SEMANTIC_DATA_ASSOCIATION_H_
