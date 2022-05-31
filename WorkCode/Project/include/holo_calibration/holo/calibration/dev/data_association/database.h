/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file database.h
 * @brief this file defines database for calibration pattern
 * @author Shuaijie Li @ lishuaijie@holomatic.com
 * @date 2022-04-27
 */

#ifndef HOLO_CALIBRATION_DEV_DATA_ASSOCIATION_DATABASE_H_
#define HOLO_CALIBRATION_DEV_DATA_ASSOCIATION_DATABASE_H_

#include <unordered_map>
#include <unordered_set>

#include <holo/calibration/dev/common_types.h>

namespace holo
{
namespace calibration
{
/**
 *  @addtogroup camera
 *  @{
 *
 */

/**
 * @brief this class is a base type for pattern database. it stores corners in a general way.
 */
class Database
{
public:
    /**
     * @brief pattern category
     * @details 0x00-0x1F for chessboard pattern 0x20 - 0x3F for apriltag pattern
     */
    enum class PatternCategory : uint8_t
    {
        CHESSBOARD_4_3 = 0x00,  ///< chessboard pattern with internal corners rows = 4, cols = 3
        CHESSBOARD_4_4 = 0x01,  ///< chessboard pattern with internal corners rows = 4, cols = 4
        APRILTAG_36_9  = 0x20,  ///< apriltag pattern family tag36h9
        APRILTAG_36_11 = 0x21,  ///< apriltag pattern family tag36h11

    };  // PatternCategory

    /**
     * @brief the pattern location relative to the origin of the vehicle
     * @details for each pattern, its location contains three components: logitude(FRONT, MIDDLE, REAR),
     * latitude(LEFT, MIDDLE, RIGHT), altitude(TOP, MIDDLE, BOTTOM). for example, if a pattern is located at MIDDLE,
     * RIGHT, BOTTOM, its location might be 00100101, the hightest two bits are reserved with default value 00
     */
    enum class Location : uint8_t
    {
        FRONT  = 0x0,
        REAR   = 0x1,
        LEFT   = 0x0,
        RIGHT  = 0x1,
        TOP    = 0x0,
        BOTTOM = 0x1,
        MIDDLE = 0x2,

    };  // Location

    /**
     * @bireef 3d point container
     */
    struct Corner
    {
        bool_t is_on_plane;  ///< whether the point is on a plane pattern
        Point3 pt;           ///< the point coordinate in reference frame
        /**
         * @biref the id is consist of the high 16-bits construct from Pattern and Location, the low 48 bits is the
         * index the high 16 bits: the high 8 bits means location TOP/BOTTOM/MIDDLE/ + LEFT/RIGHT/MIDDLE +
         * FRONT/REAR/MIDDLE, the low 8 bits means PatternCategory
         * @details the pattern apriltag36h9 in place at top/left/rear, its high 16-bits is 00000001(highest 2 bits are
         * reserved now) 00100000
         * the low 48-bits is the id: for chessboard is the order which is detected by OpenCV
         * for apriltag, four corner point corresponding to each tag is tagID * 4 + 0, 1, 2, 3
         */
        uint64_t id;

    };  // Corner

    /**
     * @brief default constructor
     */
    Database();

    /**
     * @brief constructor
     *
     * @param[in] name the label of this database
     * @param[in] location_pattern_categories information of patterns which is stored in this database
     * @param[in] dataset corner and id that this database contains
     */
    Database(std::string const& name, std::unordered_set<uint16_t> const& location_pattern_categories,
             std::unordered_map<uint64_t, Corner> const& dataset);

    /**
     * @brief get database name
     *
     * @return database name
     */
    std::string GetName() const;

    /**
     * @brief set database name
     *
     * @param[in] name database name
     */
    void SetName(std::string const name);

    /**
     * @brief set a new pattern information
     *
     * @param[in] location_and_pattern_category new pattern information
     */
    void AddPattern(uint16_t const location_and_pattern_category);

    /**
     * @brief get all the patterns information in this database
     *
     * @return all the patterns information
     */
    std::unordered_set<uint16_t> const& GetPatterns() const;

    /**
     * @brief check whether the given pattern information is exist in this database
     *
     * @param[in] location_and_pattern_category pattern information
     *
     * @return true -> the pattern is already in this database, false -> otherwise
     */
    bool_t IsPatternExist(uint16_t const location_and_pattern_category) const;

    /**
     * @brief get the number of patterns in this database
     *
     * @return number of patterns
     */
    uint64_t GetPatternNum() const;

    /**
     * @brief add a new corner
     *
     * @param[in] corner corner information
     *
     * @return true -> success, false -> otherwise
     */
    bool_t AddCornerPoint(Corner const& corner);

    /**
     * @brief add multi corners into the database
     *
     * @param[in] multi_corners multi corners information
     *
     * @return true -> success, false -> otherwise
     */
    bool_t AddCornerPoints(std::vector<Corner> const& multi_corners);

    /**
     * @brief get corners corresponding to the given ids
     *
     * @param[in] multi_ids the given ids
     * @param[in] multi_corners the corresponding corners
     *
     * @return true -> success, false -> otherwise
     */
    bool_t GetCornerPoints(std::vector<uint64_t> const& multi_ids, std::vector<Corner>& multi_corners) const;

    /**
     * @brief get all the corners
     *
     * @return corners with ids
     */
    std::unordered_map<uint64_t, Corner> const& GetCornerPointsSet() const;

    /**
     * @brief the number of corners in this database
     *
     * @return number of corners
     */
    uint64_t GetCornerPointsNum() const;

    /**
     * @brief check whether the database is valid
     *
     * @return true -> valid, false -> otherwise
     */
    virtual bool_t IsValid() const;

    /**
     * @brief convert a corner index from local pattern to the index of the database
     * @details it is a interface and will be inplemented in the derived class. for example, if a corner index 1 is in a
     * MIDDLE, RIGHT, BOTTOM, CHESSBOARD_4_3 pattern, its location might be 0x2500000000000001
     *
     * @param[in] index index of the corner in the pattern
     *
     * @return the index in the database
     */
    virtual std::vector<uint64_t> ConvertId(uint64_t const index) const;

    /**
     * @brief load database from a file
     *
     * @param[in] file_name the file which will be loaded
     * @param[in][out] db the database loaded from  ${file_name}
     *
     * @return true -> success, false -> otherwise
     */
    static bool_t Load(std::string const& file_name, Database& db);

    /**
     * @brief save to file
     *
     * @param[in] file_name file name
     * @param[in] db database that will be saved
     *
     * @return true -> success, false -> otherwise
     */
    static bool_t Save(std::string const& file_name, Database const& db);

    /**
     * @brief generate pattern information from given loacation and category
     *
     * @param[in] logitude longitudinal location: FRONT, MIDDLE, REAR
     * @param[in] latitude latitudinal location: LEFT, MIDDLE, RIGHT
     * @param[in] altitude vertical location: TOP, MIDDLE, BOTTOM
     * @param[in] pattern_category pattern category
     *
     * @return pattern information encoded in a uint16_t
     */
    static uint16_t GenerateLocationAndPatternCategory(Location const logitude, Location const latitude,
                                                       Location const altitude, PatternCategory const pattern_category);

protected:
    std::string                          name_;  ///< the name indicates which project this database belongs to
    std::unordered_set<uint16_t>         location_pattern_categories_;  ///< all the patterns information
    std::unordered_map<uint64_t, Corner> dataset_;                     ///< corners of all the patterns

};  // Database

/**
 * @}
 */
};  // namespace calibration
};  // namespace holo

#endif  // HOLO_CALIBRATION_DEV_DATA_ASSOCIATION_DATABASE_H_

