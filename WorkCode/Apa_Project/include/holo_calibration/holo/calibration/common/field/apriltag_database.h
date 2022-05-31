/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file apriltag_database.h
 * @brief This header file defines the class of AprilTagDatabase
 * @author yanwei.du @ duyanwei@holomatic.com
 *         bin.chen  @ chenbin@holomatic.com
 * @date 2020-09-10
 */

#ifndef HOLO_CALIBRATION_COMMON_FIELD_APRILTAG_DATABASE_H_
#define HOLO_CALIBRATION_COMMON_FIELD_APRILTAG_DATABASE_H_

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <holo/log/hololog.h>
#include <holo/calibration/common/field/tag_database.h>
#include <holo/container/unordered_map.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/geometry/point3.h>

namespace holo
{
namespace calibration
{
/**
 * @addtogroup camera
 * @{
 *
 */

/*****************************************************************************
 * @brief this class aims at defining apriltag data structure in riegl frame
 *****************************************************************************/
class AprilTagDatabase : public TagDatabase
{
public:
    using Scalar   = holo::float64_t;
    using Point3   = holo::geometry::Point3T<Scalar>;
    using Ptr      = std::shared_ptr<AprilTagDatabase>;
    using ConstPtr = std::shared_ptr<const AprilTagDatabase>;
    using Base     = TagDatabase;

    /// @brief Define apriltag data structure in riegl frame
    struct AprilTag
    {
        /**
         * @brief Default constructor
         * @note id have the defult value(-1), which means invalid.
         */
        AprilTag() : id(-1)
        {
        }

        /**
         * @brief Constructor
         * @param[in] tag_id apriltag's id, check out AprilTAg's official documentation for details.
         * @param[in] tag_center the center of apriltag.
         * @param[in] tag_corner four corners of apriltag,
         * @note notice the internal storage order of the four corners: lower left, ll->lr->ur->ul.
         */
        AprilTag(holo::int32_t const& tag_id, Point3 const& tag_center, std::vector<Point3> const& tag_corner)
          : id(tag_id), center(tag_center), corner(tag_corner)
        {
        }

        holo::int32_t       id;      ///< tag id, -1 means invalid
        Point3              center;  ///< tag center
        std::vector<Point3> corner;  ///< tag corner --- counter-clockwise from
                                     ///< lower left, ll->lr->ur->ul

    };  /// Apriltag

    /**
     *  @brief Default constructor
     */
    AprilTagDatabase();

    /**
     * @brief Constructor
     * @param[in] family_name family of adpriltag, which may be (tag16h15 tag25h7 tag25h9 tag36h10
     *                        and tag36h11), check out AprilTAg's official documentation for details.
     * @param[in] apriltags storing the entire data set of apriltag database, use apriltag's id(holo::int32_t)
     *                      to index the corresponding apriltag,
     */
    AprilTagDatabase(std::string const family_name, std::unordered_map<holo::int32_t, AprilTag> const& apriltags);

    /**
     * @brief Destructor.
     */
    ~AprilTagDatabase();

    /**
     * @brief Get tag family name.
     * @return name(std::string) of apriltag family.
     */
    std::string const& GetTagFamilyName() const;

    /**
     * @brief Return size of apriltag.
     * @return size of apriltag in apriltag database.
     */
    virtual holo::uint32_t GetSize() const;

    /**
     * @brief Get apriltag data with its id
     * @param[in] id apriltag id which want to get.
     * @param[in/out] tag corresponding apriltag
     * @return return false if <tag_id> dose not exist in database; otherwaise true.
     */
    bool_t GetAprilTag(holo::int32_t const id, AprilTag& tag) const;

    /**
     * @brief Get all apriltags
     * @return returns all tags contained in apriltag database. Key is Apriltag's
     *         ID, Value is AprilTag.
     */
    std::unordered_map<holo::int32_t, AprilTag> const& GetAllAprilTags() const;

    /**
     * @brief Load function to load apriltag database
     * @param[in] file file path to load
     * @param[in] verbose whether output log information, default value: true
     */
    static AprilTagDatabase Load(std::string const& file, bool_t const verbose = true);

    /**
     * @brief Save function to save apriltag database
     * @param[in] file destination path where the apriltag database is stored.
     * @param[in] atdb aprilTag database.
     * @param[in] verbose whether output log information, default value: true
     * @return return true if save success, otherwise return false.
     */
    static bool_t Save(std::string const& file, AprilTagDatabase const& atdb, bool_t const verbose = true);

private:
    /**
     * @brief Apriltag family name, "unknown" means invalid database
     */
    std::string family_name_;

    /**
     * @brief Tags
     */
    std::unordered_map<int32_t, AprilTag> apriltags_;
};  // AprilTagDatabase

/**
 * @}
 *
 */

}  // namespace calibration

}  // namespace holo

#endif  // HOLO_CALIBRATION_COMMON_FIELD_APRILTAG_DATABASE_H_
