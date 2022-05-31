/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file navigation.h
 * @brief lane level navigation
 * @author zhouhuishuang(zhouhuishuang@holomaitc.com)
 * @date "2022-02-25"
 */

#ifndef HOLO_MAP_NAVIGATION_H_
#define HOLO_MAP_NAVIGATION_H_

#include <holo/common/odometry.h>
#include <holo/common/road_category.h>
#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/geometry/point2.h>

namespace holo
{
namespace map
{
template <size_t LANE_PATH_SIZE, size_t LANE_ITEM_SIZE, size_t LANE_REGION_SIZE>
class NavigationT
{
public:
    using OdometryPrecisionType = holo::common::details::OdometryPrecision;
    enum class Status : uint8_t
    {
        UNKNOWN   = 0U,
        OK        = 1U,
        WAITING   = 2U,
        WARNING   = 3U,
        ERROR     = 4U,
        RESERVE_1 = 200U,
        RESERVE_2 = 201U,
        RESERVE_3 = 202U,
        RESERVE_4 = 203U,
        RESERVE_5 = 204U,
        OTHERS    = 255U,
    };

    enum class OperationMode : uint8_t
    {
        INVALID    = 0U,
        NAVIGATION = 1U,
        CRUISER    = 2U,
        YAWING     = 3U,
        RESERVE_1  = 200U,
        RESERVE_2  = 201U,
        RESERVE_3  = 202U,
        RESERVE_4  = 203U,
        RESERVE_5  = 204U,
        OTHERS     = 255U,
    };

    enum class RoutingMode : uint8_t
    {
        OUT_ROUTE      = 0U,
        ON_HD_ROUTE    = 1U,
        ON_SD_ROUTE    = 2U,
        ON_SD_HD_ROUTE = 3U,
        RESERVE_1      = 200U,
        RESERVE_2      = 201U,
        RESERVE_3      = 202U,
        RESERVE_4      = 203U,
        RESERVE_5      = 204U,
        OTHERS         = 255U,
    };

    enum class MapMode : uint8_t
    {
        NO_MAP    = 0U,
        HD_MAP    = 1U,
        SD_MAP    = 2U,
        SD_HD_MAP = 3U,
        RESERVE_1 = 200U,
        RESERVE_2 = 201U,
        RESERVE_3 = 202U,
        RESERVE_4 = 203U,
        RESERVE_5 = 204U,
        OTHERS    = 255U,
    };

    class LanePath
    {
    public:
        /**
         * @brief LaneItem is used to describe a lane of information
         */
        struct LaneItem
        {
            enum class IntersectionStatus : uint8_t
            {
                NO_INTERSECTION           = 0U,
                INTERSECTION_NO_TRAFFIC   = 1U,
                INTERSECTION_WITH_TRAFFIC = 2U,
                RESERVE_1                 = 200U,
                RESERVE_2                 = 201U,
                RESERVE_3                 = 202U,
                RESERVE_4                 = 203U,
                RESERVE_5                 = 204U,
                OTHERS                    = 255U,
            };

            /**
             * @brief default constructor
             */
            LaneItem()
              : lane_id{0U}
              , length{0.0f}
              , road_category{}
              , intersection_status{IntersectionStatus::NO_INTERSECTION}
              , effective_range_start_percent{0U}
              , effective_range_end_percent{100U}
            {
            }

            template <size_t ALIGN = 4U>
            size_t GetSerializedSize() const noexcept
            {
                return holo::serialization::SerializedSize<ALIGN>(
                    lane_id, length, static_cast<uint32_t>(road_category), static_cast<uint8_t>(intersection_status),
                    effective_range_start_percent, effective_range_end_percent);
            }

            template <typename S>
            void Serialize(S& serializer) const
            {
                serializer << holo::serialization::align << lane_id << length << road_category
                           << static_cast<uint8_t>(intersection_status) << effective_range_start_percent
                           << effective_range_end_percent << holo::serialization::align;
            }

            template <typename D>
            void Deserialize(D& deserializer)
            {
                uint8_t intersection_status_temp = 0U;
                deserializer >> holo::serialization::align >> lane_id >> length >> road_category >>
                    intersection_status_temp >> effective_range_start_percent >> effective_range_end_percent >>
                    holo::serialization::align;

                intersection_status = static_cast<IntersectionStatus>(intersection_status_temp);
            }

            uint64_t                   lane_id;
            float64_t                  length;
            holo::common::RoadCategory road_category;
            IntersectionStatus         intersection_status;
            uint8_t                    effective_range_start_percent;
            uint8_t                    effective_range_end_percent;
        };

        struct RegionModelInfo
        {
            enum class RegionModel : uint8_t
            {
                NONE         = 0U,
                CHANGE_RIGHT = 1U,
                CHANGE_LEFT  = 2U,
                SPLIT_RIGHT  = 3U,
                SPLIT_LEFT   = 4U,
                MERGE_RIGHT  = 5U,
                MERGE_LEFT   = 6U,
                RESERVE_1    = 200U,
                RESERVE_2    = 201U,
                RESERVE_3    = 202U,
                RESERVE_4    = 203U,
                RESERVE_5    = 204U,
                OTHERS       = 255U,
            };
            /**
             * @brief default constructor
             */
            RegionModelInfo()
              : region_id{0U}
              , score{0U}
              , model{RegionModel::NONE}
              , prepare_location{0.0f}
              , dangerous_location{0.0f}
              , limit_location{0.0f}
              , link_lane_path_id{0U}
            {
            }

            template <size_t ALIGN = 4U>
            size_t GetSerializedSize() const noexcept
            {
                return holo::serialization::SerializedSize<ALIGN>(region_id, score, static_cast<uint8_t>(model),
                                                                  prepare_location, dangerous_location, limit_location,
                                                                  link_lane_path_id);
            }

            template <typename S>
            void Serialize(S& serializer) const
            {
                serializer << holo::serialization::align << region_id << score << static_cast<uint8_t>(model)
                           << prepare_location << dangerous_location << limit_location << link_lane_path_id
                           << holo::serialization::align;
            }

            template <typename D>
            void Deserialize(D& deserializer)
            {
                uint8_t model_temp = 0U;
                deserializer >> holo::serialization::align >> region_id >> score >> model_temp >> prepare_location >>
                    dangerous_location >> limit_location >> link_lane_path_id >> holo::serialization::align;
                model = static_cast<RegionModel>(model_temp);
            }

            uint64_t    region_id;
            uint32_t    score;
            RegionModel model;
            float64_t   prepare_location;
            float64_t   dangerous_location;
            float64_t   limit_location;
            uint64_t    link_lane_path_id;
        };

        struct RegionStateInfo
        {
            enum class DrivingStatus : uint8_t
            {
                NONE                   = 0x00,
                SPLIT_LEFT             = 0x10,
                SPLIT_RIGHT            = 0x11,
                MERGE_LEFT             = 0x12,
                MERGE_RIGHT            = 0x13,
                TURN_LEFT              = 0x14,
                TURN_RIGHT             = 0x15,
                TURN_AROUND_LEFT       = 0x16,
                TURN_AROUND_RIGHT      = 0x17,
                BREAKUP                = 0x18,
                ACCELERATE_MERGE_LEFT  = 0x19,
                ACCELERATE_MERGE_RIGHT = 0x1a,
                DECELERATE_SPLIT_LEFT  = 0x1b,
                DECELERATE_SPLIT_RIGHT = 0x1c,
                MERGE_PASS_BY_LEFT     = 0x1d,
                MERGE_PASS_BY_RIGHT    = 0x1e,
                SPLIT_PASS_BY_LEFT     = 0x1f,
                SPLIT_PASS_BY_RIGHT    = 0x20,
                TURN_LEFT_AREA         = 0x21,
                TURN_RIGHT_AREA        = 0x22,
                RESERVE_1              = 0xf0,
                RESERVE_2              = 0xf1,
                RESERVE_3              = 0xf2,
                RESERVE_4              = 0xf3,
                RESERVE_5              = 0xf4,
                OTHERS                 = 0xff,
            };
            enum class SectionForm : uint8_t
            {
                NONE       = 0x00,
                DIRECT     = 0x21,
                PARALLEL   = 0x22,
                CORRESPOND = 0x23,
                RESERVE_1  = 0x24,
                RESERVE_2  = 0x25,
                RESERVE_3  = 0x26,
                RESERVE_4  = 0x27,
                RESERVE_5  = 0x28,
                OTHERS     = 0xff,
            };

            /**
             * @brief default constructor
             */
            RegionStateInfo()
              : driving_status{DrivingStatus::NONE}
              , section_form{SectionForm::NONE}
              , id{0U}
              , start_distance{0.0f}
              , end_distance{0.0f}
            {
            }

            template <size_t ALIGN = 4U>
            size_t GetSerializedSize() const noexcept
            {
                return holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(driving_status),
                                                                  static_cast<uint8_t>(section_form), id,
                                                                  start_distance, end_distance);
            }

            template <typename S>
            void Serialize(S& serializer) const
            {
                serializer << holo::serialization::align << static_cast<uint8_t>(driving_status)
                           << static_cast<uint8_t>(section_form) << id << start_distance << end_distance
                           << holo::serialization::align;
            }

            template <typename D>
            void Deserialize(D& deserializer)
            {
                uint8_t driving_status_temp = 0U;
                uint8_t section_form_temp   = 0U;

                deserializer >> holo::serialization::align >> driving_status_temp >> section_form_temp >> id >>
                    start_distance >> end_distance >> holo::serialization::align;

                driving_status = static_cast<DrivingStatus>(driving_status_temp);
                section_form   = static_cast<SectionForm>(section_form_temp);
            }

            DrivingStatus driving_status;  ///< status function description
            SectionForm   section_form;    ///< status action
            uint64_t      id;              ///< region state info id
            float64_t     start_distance;  ///< distance from region start point to the position point, unit: meter
            float64_t     end_distance;    ///< distance from region end point to the position point, unit: meter
        };

        /**
         * @brief default constructor
         */
        LanePath()
          : id_{0U}
          , sequence_number_{0}
          , description_{}
          , lane_items_{}
          , region_model_infos_{}
          , region_state_infos_{}
          , tracked_path_ids_{}
        {
        }

        /**
         * @brief Construct a new LanePath object
         *
         * @param id path id
         * @param sequence_number path sequence number
         */
        LanePath(uint64_t const id, int8_t const sequence_number)
          : id_{id}
          , sequence_number_{sequence_number}
          , description_{}
          , lane_items_{}
          , region_model_infos_{}
          , region_state_infos_{}
          , tracked_path_ids_{}
        {
        }

        /**
         * @brief Set id
         *
         * @param id
         */
        void SetId(uint64_t const id) noexcept
        {
            id_ = id;
        }

        /**
         * @brief Get id
         *
         * @return uint64_t
         */
        uint64_t GetId() const noexcept
        {
            return id_;
        }

        /**
         * @brief Set path sequence number
         *
         * @param seq
         */
        void SetSequenceNumber(int8_t const seq) noexcept
        {
            sequence_number_ = seq;
        }

        /**
         * @brief Get path sequence number
         *
         * @return int8_t
         */
        int8_t GetSequenceNumber() const noexcept
        {
            return sequence_number_;
        }

        /**
         * @brief Get description
         *
         * @return description
         */
        uint16_t GetDescription() const noexcept
        {
            return static_cast<uint16_t>(description_.is_to_destination) | static_cast<uint16_t>(static_cast<uint16_t>(description_.is_lane_level_path) << 1);
        }

        /**
         * @brief Set description
         *
         * @param value description
         */
        void SetDescription(uint16_t description) noexcept
        {
            description_.is_to_destination  = description >> 0;
            description_.is_lane_level_path = description >> 1;
        }

        /**
         * @brief Checkif Whether it leads to the destination
         *
         * @return true for leads to the destination.
         * @return false for not leads to the destination.
         */
        bool_t IsToDestination() const noexcept
        {
            return description_.is_to_destination;
        }

        /**
         * @brief Set to destination status
         *
         * @param status whether it leads to the destination
         */
        void SetToDestinationStatus(bool_t status) noexcept
        {
            description_.is_to_destination = status;
        }

        /**
         * @brief Checkif whether path is lane-level path
         *
         * @return true for path is lane-level path
         * @return false for path is not lane-level path
         */
        bool_t IsLaneLevelPath() const noexcept
        {
            return description_.is_lane_level_path;
        }

        /**
         * @brief Set whether path is lane-level path
         *
         * @param status whether it is lane-level path
         */
        void SetLaneLevelPathStatus(bool_t status) noexcept
        {
            description_.is_lane_level_path = status;
        }

        /**
         * @brief Get lane items
         *
         * @return Reference of lane items
         */
        holo::container::Vector<LaneItem, LANE_ITEM_SIZE>& GetLaneItems() noexcept
        {
            return lane_items_;
        }

        /**
         * @brief Get lane items
         *
         * @return Const reference of lane items
         */
        holo::container::Vector<LaneItem, LANE_ITEM_SIZE> const& GetLaneItems() const noexcept
        {
            return lane_items_;
        }

        /**
         * @brief Set lane items
         *
         * @param lane_items
         */
        void SetLaneItems(holo::container::Vector<LaneItem, LANE_ITEM_SIZE> const& lane_items) noexcept
        {
            lane_items_ = lane_items;
        }

        /**
         * @brief Get region model infos
         *
         * @return Reference of region model infos
         */
        holo::container::Vector<RegionModelInfo, LANE_REGION_SIZE>& GetRegionModelInfos() noexcept
        {
            return region_model_infos_;
        }

        /**
         * @brief Get region model infos
         *
         * @return Const reference of region model infos
         */
        holo::container::Vector<RegionModelInfo, LANE_REGION_SIZE> const& GetRegionModelInfos() const noexcept
        {
            return region_model_infos_;
        }

        /**
         * @brief Set region model infos
         *
         * @param region_model_infos
         */
        void SetRegionModelInfos(
            holo::container::Vector<RegionModelInfo, LANE_REGION_SIZE> const& region_model_infos) noexcept
        {
            region_model_infos_ = region_model_infos;
        }

        /**
         * @brief Get tracked path ids
         *
         * @return Reference of tracked path ids
         */
        holo::container::Vector<uint64_t, 8U>& GetTrackedPathIds() noexcept
        {
            return tracked_path_ids_;
        }

        /**
         * @brief Get tracked path ids
         *
         * @return Const reference of tracked path ids
         */
        holo::container::Vector<uint64_t, 8U> const& GetTrackedPathIds() const noexcept
        {
            return tracked_path_ids_;
        }

        /**
         * @brief Set tracked path ids
         *
         * @param tracked_path_ids
         */
        void SetTrackedPathIds(holo::container::Vector<uint64_t, 8U> const& tracked_path_ids) noexcept
        {
            tracked_path_ids_ = tracked_path_ids;
        }

        /**
         * @brief Get region state infos
         *
         * @return Reference of region state infos
         */
        holo::container::Vector<RegionStateInfo, LANE_REGION_SIZE>& GetRegionStateInfos() noexcept
        {
            return region_state_infos_;
        }

        /**
         * @brief Get region state infos
         *
         * @return Const reference of region state infos
         */
        holo::container::Vector<RegionStateInfo, LANE_REGION_SIZE> const& GetRegionStateInfos() const noexcept
        {
            return region_state_infos_;
        }

        /**
         * @brief Set region state infos
         *
         * @param region_state_infos
         */
        void SetRegionStateInfos(
            holo::container::Vector<RegionStateInfo, LANE_REGION_SIZE> const& region_state_infos) noexcept
        {
            region_state_infos_ = region_state_infos;
        }

        /**
         * @brief Get serialized size at give byte alignment value
         *
         * @tparam ALIGN Byte alignment value
         *
         * @return Serialized size
         */
        template <size_t ALIGN = 4U>
        size_t GetSerializedSize() const noexcept
        {
            return holo::serialization::SerializedSize<ALIGN>(id_, sequence_number_, GetDescription()) +
                   lane_items_.template GetSerializedSize<ALIGN>() +
                   region_model_infos_.template GetSerializedSize<ALIGN>() +
                   region_state_infos_.template GetSerializedSize<ALIGN>() +
                   tracked_path_ids_.template GetSerializedSize<ALIGN>();
        }

        /**
         * @brief Serialize this object into buffer through serializer.
         *
         * @param serializer The buffer to serializer.
         *
         * @return none.
         *
         * @throws holo::serialization::SerializationBufferOverflowException if buffer
         * size < serialized size.
         *
         * @exceptsafe Basic
         */
        template <typename S>
        void Serialize(S& serializer) const
        {
            serializer << holo::serialization::align << id_ << sequence_number_ << GetDescription() << lane_items_
                       << region_model_infos_ << region_state_infos_ << tracked_path_ids_;
        }

        /**
         * @brief Deserialize this object from buffer through deserializer.
         *
         * @param deserializer The buffer to deserialize from.
         *
         * @return none.
         *
         * @throws holo::serialization::DeserializationBufferUnderflowException if
         * buffer size < deserialized size.
         *
         * @exceptsafe Basic
         */
        template <typename D>
        void Deserialize(D& deserializer)
        {
            uint16_t description = 0;
            deserializer >> holo::serialization::align >> id_ >> sequence_number_ >> description >> lane_items_ >>
                region_model_infos_ >> region_state_infos_ >> tracked_path_ids_;
            SetDescription(description);
        }

    private:
        uint64_t id_;
        int8_t   sequence_number_;

        struct
        {
            uint16_t is_to_destination : 1;
            uint16_t is_lane_level_path : 1;
            uint16_t reserved : 14;
        } description_;

        holo::container::Vector<LaneItem, LANE_ITEM_SIZE>          lane_items_;
        holo::container::Vector<RegionModelInfo, LANE_REGION_SIZE> region_model_infos_;
        holo::container::Vector<RegionStateInfo, LANE_REGION_SIZE> region_state_infos_;
        holo::container::Vector<uint64_t, 8U>                      tracked_path_ids_;
    };

    /**
     * @brief default constructor
     */
    NavigationT()
      : timestamp_{}
      , status_{Status::UNKNOWN}
      , operation_mode_{OperationMode::INVALID}
      , routing_mode_{RoutingMode::OUT_ROUTE}
      , map_mode_{MapMode::NO_MAP}
      , odometry_precision_{}
      , distance_to_available_hd_area_entry_{0.0f}
      , distance_to_available_hd_area_exit_{0.0f}
      , distance_to_hd_area_entry_{0.0f}
      , distance_to_hd_area_exit_{0.0f}
      , distance_to_sd_destination_{0.0f}
      , distance_to_hd_destination_{0.0f}
      , lane_paths_{}
      , current_lanes_{}
      , recommended_lanes_{}
    {
    }

    /**
     * @brief Set timestamp
     *
     * @param timestamp
     */
    void SetTimestamp(Timestamp const timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get timestamp
     *
     * @return Timestamp
     */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief Set navigation status
     *
     * @param navigation status
     */
    void SetStatus(Status const status) noexcept
    {
        status_ = status;
    }

    /**
     * @brief Get navigation status
     *
     * @return navigation status
     */
    Status GetStatus() const noexcept
    {
        return status_;
    }

    /**
     * @brief Set operation mode
     *
     * @param mode operation mode
     */
    void SetOperationMode(OperationMode const mode) noexcept
    {
        operation_mode_ = mode;
    }

    /**
     * @brief Get operation mode
     *
     * @return operation mode
     */
    OperationMode GetOperationMode() const noexcept
    {
        return operation_mode_;
    }

    /**
     * @brief Set routing mode
     *
     * @param routing_mode
     */
    void SetRoutingMode(RoutingMode const routing_mode) noexcept
    {
        routing_mode_ = routing_mode;
    }

    /**
     * @brief Get routing mode
     *
     * @return routing mode
     */
    RoutingMode GetRoutingMode() const noexcept
    {
        return routing_mode_;
    }

    /**
     * @brief Set map mode
     *
     * @param map_mode
     */
    void SetMapMode(MapMode const map_mode) noexcept
    {
        map_mode_ = map_mode;
    }

    /**
     * @brief Get map mode
     *
     * @return map mode
     */
    MapMode GetMapMode() const noexcept
    {
        return map_mode_;
    }

    /**
     * @brief Set odometry precision
     *
     * @param precision
     */
    void SetOdometryPrecision(OdometryPrecisionType const precision) noexcept
    {
        odometry_precision_ = precision;
    }

    /**
     * @brief Get odometry precision
     *
     * @return odometry precision
     */
    OdometryPrecisionType GetOdometryPrecision() const noexcept
    {
        return odometry_precision_;
    }

    /**
     * @brief Set distance to available hd area entry
     *
     * @param distance
     */
    void SetDistanceToAvailableHdAreaEntry(float64_t const distance) noexcept
    {
        distance_to_available_hd_area_entry_ = distance;
    }

    /**
     * @brief Get distance to available hd area entry
     *
     * @return distance
     */
    float64_t GetDistanceToAvailableHdAreaEntry() const noexcept
    {
        return distance_to_available_hd_area_entry_;
    }

    /**
     * @brief Set distance to available hd area exit
     *
     * @param distance
     */
    void SetDistanceToAvailableHdAreaExit(float64_t const distance) noexcept
    {
        distance_to_available_hd_area_exit_ = distance;
    }

    /**
     * @brief Get distance to available hd area exit
     *
     * @return distance
     */
    float64_t GetDistanceToAvailableHdAreaExit() const noexcept
    {
        return distance_to_available_hd_area_exit_;
    }

    /**
     * @brief Set distance to hd area entry
     *
     * @param distance
     */
    void SetDistanceToHdAreaEntry(float64_t const distance) noexcept
    {
        distance_to_hd_area_entry_ = distance;
    }

    /**
     * @brief Get distance to hd area entry
     *
     * @return distance
     */
    float64_t GetDistanceToHdAreaEntry() const noexcept
    {
        return distance_to_hd_area_entry_;
    }

    /**
     * @brief Set distance to hd area exit
     *
     * @param distance
     */
    void SetDistanceToHdAreaExit(float64_t const distance) noexcept
    {
        distance_to_hd_area_exit_ = distance;
    }

    /**
     * @brief Get distance to hd area exit
     *
     * @return distance
     */
    float64_t GetDistanceToHdAreaExit() const noexcept
    {
        return distance_to_hd_area_exit_;
    }

    /**
     * @brief Set distance to sd destination
     *
     * @param distance
     */
    void SetDistanceToSdDestination(float64_t const distance) noexcept
    {
        distance_to_sd_destination_ = distance;
    }

    /**
     * @brief Get distance to sd destination
     *
     * @return distance
     */
    float64_t GetDistanceToSdDestination() const noexcept
    {
        return distance_to_sd_destination_;
    }

    /**
     * @brief Set distance to hd destination
     *
     * @param distance
     */
    void SetDistanceToHdDestination(float64_t const distance) noexcept
    {
        distance_to_hd_destination_ = distance;
    }

    /**
     * @brief Get distance to hd destination
     *
     * @return distance
     */
    float64_t GetDistanceToHdDestination() const noexcept
    {
        return distance_to_hd_destination_;
    }

    /**
     * @brief Get lane paths
     *
     * @return Reference of lane paths
     */
    holo::container::Vector<LanePath, LANE_PATH_SIZE>& GetLanePaths() noexcept
    {
        return lane_paths_;
    }

    /**
     * @brief Get lane paths
     *
     * @return Const reference of lane paths
     */
    holo::container::Vector<LanePath, LANE_PATH_SIZE> const& GetLanePaths() const noexcept
    {
        return lane_paths_;
    }

    /**
     * @brief Set lane paths
     *
     * @param lane_paths
     */
    void SetLanePaths(holo::container::Vector<LanePath, LANE_PATH_SIZE> const& lane_paths) noexcept
    {
        lane_paths_ = lane_paths;
    }

    /**
     * @brief Get current lanes
     *
     * @return Reference of current lanes
     */
    holo::container::Vector<int32_t, 16U>& GetCurrentLanes() noexcept
    {
        return current_lanes_;
    }

    /**
     * @brief Get current lanes
     *
     * @return Const reference of current lanes
     */
    holo::container::Vector<int32_t, 16U> const& GetCurrentLanes() const noexcept
    {
        return current_lanes_;
    }

    /**
     * @brief Set current lanes
     *
     * @param current_lanes
     */
    void SetCurrentLanes(holo::container::Vector<int32_t, 16U> const& current_lanes) noexcept
    {
        current_lanes_ = current_lanes;
    }

    /**
     * @brief Get recommended lanes
     *
     * @return Reference of recommended lanes
     */
    holo::container::Vector<int32_t, 16U>& GetRecommendedLanes() noexcept
    {
        return recommended_lanes_;
    }

    /**
     * @brief Get recommended lanes
     *
     * @return Const reference of recommended lanes
     */
    holo::container::Vector<int32_t, 16U> const& GetRecommendedLanes() const noexcept
    {
        return recommended_lanes_;
    }

    /**
     * @brief Set recommended lanes
     *
     * @param recommended_lanes
     */
    void SetRecommendedLanes(holo::container::Vector<int32_t, 16U> const& recommended_lanes) noexcept
    {
        recommended_lanes_ = recommended_lanes;
    }

    /**
     * @brief Get the Expected Lane Path ids
     *
     * @return expected lane paths
     */
    holo::container::Vector<uint64_t, 16U>& GetExpectedLanePaths() noexcept
    {
        return expected_lane_paths_;
    }

    /**
     * @brief Get the expected lane path ids
     *
     * @return expected lane paths
     */
    holo::container::Vector<uint64_t, 16U> const& GetExpectedLanePaths() const noexcept
    {
        return expected_lane_paths_;
    }

    /**
     * @brief Set expected lane paths
     *
     * @param expected_lane_paths expected lane paths
     */
    void SetExpectedLanePaths(holo::container::Vector<uint64_t, 16U> const& expected_lane_paths) noexcept
    {
        expected_lane_paths_ = expected_lane_paths;
    }

    /**
     * @brief Get history trace
     *
     * @return Reference of history trace
     */
    holo::container::Vector<uint64_t, 16U>& GetHistoryTrace() noexcept
    {
        return history_trace_;
    }

    /**
     * @brief Get history trace
     *
     * @return Const reference of history trace
     */
    holo::container::Vector<uint64_t, 16U> const& GetHistoryTrace() const noexcept
    {
        return history_trace_;
    }

    /**
     * @brief Set history trace
     *
     * @param history_trace
     */
    void SetHistoryTrace(holo::container::Vector<uint64_t, 16U> const& history_trace) noexcept
    {
        history_trace_ = history_trace;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::SerializedSize<ALIGN>(
                   static_cast<uint8_t>(status_), static_cast<uint8_t>(operation_mode_),
                   static_cast<uint8_t>(routing_mode_), static_cast<uint8_t>(map_mode_),
                   static_cast<uint32_t>(odometry_precision_), distance_to_available_hd_area_entry_,
                   distance_to_available_hd_area_exit_, distance_to_hd_area_entry_, distance_to_hd_area_exit_,
                   distance_to_sd_destination_, distance_to_hd_destination_) +
               lane_paths_.template GetSerializedSize<ALIGN>() + current_lanes_.template GetSerializedSize<ALIGN>() +
               recommended_lanes_.template GetSerializedSize<ALIGN>() +
               expected_lane_paths_.template GetSerializedSize<ALIGN>() +
               history_trace_.template GetSerializedSize<ALIGN>();
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer
     * size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << static_cast<uint8_t>(status_) << static_cast<uint8_t>(operation_mode_)
                   << static_cast<uint8_t>(routing_mode_) << static_cast<uint8_t>(map_mode_)
                   << static_cast<uint32_t>(odometry_precision_) << distance_to_available_hd_area_entry_
                   << distance_to_available_hd_area_exit_ << distance_to_hd_area_entry_ << distance_to_hd_area_exit_
                   << distance_to_sd_destination_ << distance_to_hd_destination_ << lane_paths_ << current_lanes_
                   << recommended_lanes_ << expected_lane_paths_ << history_trace_;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if
     * buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint8_t  status;
        uint8_t  operation_mode;
        uint8_t  routing_mode;
        uint8_t  map_mode;
        uint32_t odometry_precision;

        deserializer >> timestamp_ >> status >> operation_mode >> routing_mode >> map_mode >> odometry_precision >>
            distance_to_available_hd_area_entry_ >> distance_to_available_hd_area_exit_ >> distance_to_hd_area_entry_ >>
            distance_to_hd_area_exit_ >> distance_to_sd_destination_ >> distance_to_hd_destination_ >> lane_paths_ >>
            current_lanes_ >> recommended_lanes_ >> expected_lane_paths_ >> history_trace_;

        status_             = static_cast<Status>(status);
        operation_mode_     = static_cast<OperationMode>(operation_mode);
        routing_mode_       = static_cast<RoutingMode>(routing_mode);
        map_mode_           = static_cast<MapMode>(map_mode);
        odometry_precision_ = odometry_precision;
    }

private:
    Timestamp                                         timestamp_;
    Status                                            status_;
    OperationMode                                     operation_mode_;
    RoutingMode                                       routing_mode_;
    MapMode                                           map_mode_;
    OdometryPrecisionType                             odometry_precision_;
    float64_t                                         distance_to_available_hd_area_entry_;
    float64_t                                         distance_to_available_hd_area_exit_;
    float64_t                                         distance_to_hd_area_entry_;
    float64_t                                         distance_to_hd_area_exit_;
    float64_t                                         distance_to_sd_destination_;
    float64_t                                         distance_to_hd_destination_;
    holo::container::Vector<LanePath, LANE_PATH_SIZE> lane_paths_;
    holo::container::Vector<int32_t, 16U>             current_lanes_;
    holo::container::Vector<int32_t, 16U>             recommended_lanes_;
    holo::container::Vector<uint64_t, 16U>            expected_lane_paths_;
    holo::container::Vector<uint64_t, 16U>            history_trace_;
};

}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_NAVIGATION_H_ */
