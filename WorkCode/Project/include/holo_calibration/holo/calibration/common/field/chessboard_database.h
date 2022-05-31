/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file chessboard_database.h
 * @brief This header file defines the class of chessboard Database
 * @author jiaxing.zhao @ zhaojiaxing@holomatic.com
 * @date 2021-05-28
 */

#ifndef HOLO_CALIBRATION_COMMON_FIELD_CHESSBOARD_DATABASE_H_
#define HOLO_CALIBRATION_COMMON_FIELD_CHESSBOARD_DATABASE_H_

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
 * @brief this class aims at defining chessboard data structure in world frame
 *****************************************************************************/
class ChessboardDatabase : public TagDatabase
{
public:
    using Scalar   = holo::float64_t;
    using Point3   = holo::geometry::Point3T<Scalar>;
    using Ptr      = std::shared_ptr<ChessboardDatabase>;
    using ConstPtr = std::shared_ptr<const ChessboardDatabase>;
    using Base     = TagDatabase;

    /**
     * @brief Define chessboard data structure in specific coordinate such as world frame
     * @details each corner corresponds to an id, as follows
     *          0   1    2    3   ... n
     *          n+1 n+2  n+3  n+4 ...
     */
    struct ChessboardCorner
    {
        /**
         * @brief Default constructor
         * @note id have the defult value(-1), which means invalid.
         */
        ChessboardCorner() : id(-1)
        {
        }

        /**
         * @brief Constructor
         *
         * @param[in] chessboard_id chessboardcorner's id, check out chessboard's official documentation for details.
         * @param[in] chessboard_corner one corner
         */
        ChessboardCorner(holo::int32_t const& chessboardcorner_id, Point3 const& chessboard_corner)
          : id(chessboardcorner_id), corner(chessboard_corner)
        {
        }

        holo::int32_t id;      ///< chessboard id, -1 means invalid
        Point3        corner;  ///< chessboard: one corner

    };  /// ChessboardCorner

    /**
     *  @brief Default constructor
     */
    ChessboardDatabase();

    /**
     * @brief Constructor
     * @param[in] chessboard_corners storing the entire data set of chessboard database, use chessboardcorner's
     * id(holo::int32_t) to index the corresponding chessboard corners
     */
    ChessboardDatabase(uint16_t const chessboard_rows, uint16_t const chessboard_cols,
                       std::unordered_map<holo::int32_t, ChessboardCorner> const& chessboard_corners);

    /**
     * @brief Destructor.
     */
    ~ChessboardDatabase();

    /**
     * @brief Return size of chessboard corners.
     * @return size of chessboard corners in chessboard database.
     */
    holo::uint32_t GetSize() const;

    /**
     * @brief Return rows and cols of chessboard.
     * @return size of chessboard in chessboard database.
     */
    void GetChessboardSize(uint16_t& chessboard_rows, uint16_t& chessboard_cols) const;

    /**
     * @brief Get ChessboardCorner data with its id
     * @param[in] id chessboardcorner id which want to get.
     * @param[in/out] chessboard_corner corresponding chessboardcorner
     * @return return false if <chessboardcorner_id> dose not exist in database; otherwaise true.
     */
    bool_t GetChessboardCorner(holo::int32_t const id, ChessboardCorner& chessboard_corner) const;

    /**
     * @brief Get all chessboardcorners
     * @return returns all chessboardcorners contained in chessboard database. Key is chessboardcorner's
     *         ID, Value is chessboardcorner.
     */
    std::unordered_map<holo::int32_t, ChessboardCorner> const& GetAllChessboardCorners() const;

    /**
     * @brief Load function to load chessboard database
     * @param[in] file file path to load
     * @param[in] verbose whether output log information, default value: true
     */
    static ChessboardDatabase Load(std::string const& file, bool_t const verbose = true);

    /**
     * @brief Save function to save chessboard database
     * @param[in] file destination path where the chessboard database is stored.
     * @param[in] cbdb chessboard database.
     * @param[in] verbose whether output log information, default value: true
     * @return return true if save success, otherwise return false.
     */
    static bool_t Save(std::string const& file, ChessboardDatabase const& cbdb, bool_t const verbose = true);

private:
    /**
     * @brief chessboard rows
     */
    uint16_t chessboard_rows_;

    /**
     * @brief chessboard cols
     */
    uint16_t chessboard_cols_;
    /**
     * @brief chessboard corners
     */
    std::unordered_map<int32_t, ChessboardCorner> chessboard_corners_;

};  // ChessboardDatabase

/**
 * @}
 *
 */

}  // namespace calibration

}  // namespace holo

#endif  // HOLO_CALIBRATION_COMMON_FIELD_CHESSBOARD_DATABASE_H_
