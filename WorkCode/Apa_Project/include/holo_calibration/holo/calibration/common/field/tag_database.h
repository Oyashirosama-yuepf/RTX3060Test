/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tag_database.h
 * @brief This header file defines the class of TagDatabase
 * @author zhaojiaxing @ zhaojiaxing@holomatic.com
 * @date 2021-07-27
 */

#ifndef HOLO_CALIBRATION_COMMON_FIELD_TAG_DATABASE_H_
#define HOLO_CALIBRATION_COMMON_FIELD_TAG_DATABASE_H_

#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include <holo/log/hololog.h>
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
 * @brief this class aims at defining tag data structure in riegl frame
 *****************************************************************************/
class TagDatabase
{
public:
    using Scalar   = holo::float64_t;
    using Point3   = holo::geometry::Point3T<Scalar>;
    using Ptr      = std::shared_ptr<TagDatabase>;
    using ConstPtr = std::shared_ptr<const TagDatabase>;

    /**
     *  @brief Default constructor
     */
    TagDatabase();

    /**
     * @brief Destructor.
     */
    virtual ~TagDatabase()
    {
    }

    /**
     * @brief Return size of specified tag, such as apriltag, chessboard, charucob and so on.
     * @return size of tag in tag database.
     */
    virtual holo::uint32_t GetSize() const = 0;

protected:
    /**
     * @brief Load a point
     * @return a 3d point in specify coordinate, such as world coordinate.
     */
    static Point3 loadPoint(std::ifstream& is);

    /**
     * @brief Save a point
     */
    static void savePoint(std::ofstream& os, Point3 const& pt);

};  // TagDatabase

/**
 * @}
 *
 */

}  // namespace calibration

}  // namespace holo

#endif  // HOLO_CALIBRATION_COMMON_FIELD_APRILTAG_DATABASE_H_
