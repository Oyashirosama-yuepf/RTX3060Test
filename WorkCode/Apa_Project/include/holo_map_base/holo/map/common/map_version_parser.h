/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file map_version_parser.h
 * @brief This header file defines the version parser for holo map format, holo nds db, and holo map middleware.
 * @author lisong@holomatic.com
 * @date 2020-04-23
 */

#ifndef HOLO_MAP_COMMON_MAP_VERSION_PARSER_H_
#define HOLO_MAP_COMMON_MAP_VERSION_PARSER_H_

#ifndef MAPVERSION_BITSET_SIZE
#define MAPVERSION_BITSET_SIZE (std::size_t)64
#endif  // !MAPVERSION_BITSET_SIZE

#include <bitset>
#include <map>
#include <sstream>
#include <string>

#include <holo/log/hololog.h>


namespace holo
{
/**
 * @addtogroup holo
 *
 * @{
 */
namespace map
{
/**
 * @addtogroup map
 *
 * @{
 */

/**
 * @brief this class defines version parser of holo map format, holo nds db, and holo map middleware.
 *
 * @details An Version (of holo map format, holo nds db, holo map middleware, they share the same form) is consist of 7
 * parts.
 * @verbatim
 * |------------------    ---8 Bytes/64 Bits--------------------------|
 * | 28 Bits  | 8 Bits |  8 Bits | 8 Bits | 4 Bits  | 5 Bits | 3 Bits |
 * |  Reserve |  Major |  Patch  |  Year  |  Month  |   Day  | Code   |
 * @endverbatim
 *
 * Reserve: Reserved, always Zero for now
 *
 * Major: Major version number, valid range: [0, 255]
 *
 * Patch: Patch version number, valid range: [0, 255]
 *
 * Year: what year this version published, valid range: [20, 255], base on year of 2000, actual range is [2020, 2255]
 *
 * Month: what month this version published, valid range: [1, 12]
 *
 * Day: what day this version published, valid range: [1, 31]
 *
 * Code: Code, [1, 4]: 1 for Alpha, 2 for Beta, 3 for RC, 4 for Release
 */
class MapVersionParser
{
public:

    enum class VersionMonth : uint8_t
    {
        VERSION_MONTH_UNKNOWN = 0,   ///< Unknown 
        VERSION_MONTH_JAN     = 1,   ///< January
        VERSION_MONTH_FEB     = 2,   ///< February
        VERSION_MONTH_MAR     = 3,   ///< March
        VERSION_MONTH_APR     = 4,   ///< April
        VERSION_MONTH_MAY     = 5,   ///< May
        VERSION_MONTH_JUN     = 6,   ///< June
        VERSION_MONTH_JUL     = 7,   ///< July
        VERSION_MONTH_AUG     = 8,   ///< August
        VERSION_MONTH_SEPT    = 9,   ///< September
        VERSION_MONTH_OCT     = 10,  ///< October
        VERSION_MONTH_NOV     = 11,  ///< November
        VERSION_MONTH_DEC     = 12   ///< December
    };

    enum class VersionCode : uint8_t
    {
        VERSION_CODE_UNKNOWN = 0,  ///< Unknown
        VERSION_CODE_ALPHA   = 1,  ///< Alpha
        VERSION_CODE_BETA    = 2,  ///< Beta
        VERSION_CODE_RC      = 3,  ///< RC
        VERSION_CODE_RELEASE = 4   ///< Release
    };

public:
    /**
     * @brief Construct a new version parser, after this underlying Version object is Constructed.
     *
     */
    MapVersionParser() = default;

    /// Deconstructor
    ~MapVersionParser() = default;

    /**
     * @brief Construct a new version parser by parameters, after this underlying Version object is Constructed.
     * @note If input parameters are invalid (any of them), this object initialized to Zero of uint64 form.
     *
     * @param[in] major Major version number
     * @param[in] patch Patch version number
     * @param[in] year Year
     * @param[in] month Month
     * @param[in] day Day
     * @param[in] code Code
     */
    MapVersionParser(uint8_t const major, uint8_t const patch, uint8_t const year, VersionMonth const month,
                     uint8_t const day, VersionCode const code)
    {
        if (!isYearValueValid(year))
        {
            LOG(ERROR) << "MapVersionParser, invalid year value = " << static_cast<int>(year);
        }

        if (!isMonthValueValid(static_cast<uint8_t>(month)))
        {
            LOG(ERROR) << "MapVersionParser, invalid month value = " << static_cast<int>(month);
        }

        if (!isDayValueValid(day))
        {
            LOG(ERROR) << "MapVersionParser, invalid day value = " << static_cast<int>(day);
        }

        if (!isCodeValueValid(static_cast<uint8_t>(code)))
        {
            LOG(ERROR) << "MapVersionParser, invalid code value = " << static_cast<int>(code);
        }

        setPartialBits(major_start_pos_, major_length_, static_cast<uint64_t>(major), version_);
        setPartialBits(patch_start_pos_, patch_length_, static_cast<uint64_t>(patch), version_);
        setPartialBits(year_start_pos_, year_length_, static_cast<uint64_t>(year), version_);
        setPartialBits(month_start_pos_, month_length_, static_cast<uint64_t>(month), version_);
        setPartialBits(day_start_pos_, day_length_, static_cast<uint64_t>(day), version_);
        setPartialBits(code_start_pos_, code_length_, static_cast<uint64_t>(code), version_);
    }

    /**
     * @brief Construct a new version parser by an uint64-form version object value, underlying Version object
     * is Constructed.
     * @note If input parameter is invalid, this object initialized to Zero of uint64 form.
     *
     * @param[in] version_value Value of version object of uint64 form
     */
    explicit MapVersionParser(uint64_t const version_value)
    {
        if (!isVersionValueValid(version_value))
        {
            LOG(ERROR) << "MapVersionParser, invalid uint64-form version value = " << version_value;
        }
        version_ = version_value;
    }

    /// Object of this class is Copyable
    MapVersionParser(MapVersionParser const& other) = default;

    /**
     * @brief Copy assign operator
     * 
     * @param[in] other Other MapVersionParser object
     * @return MapVersionParser&
     */
    MapVersionParser& operator=(MapVersionParser const& other)
    {
        if (this != &other)
        {
            this->version_ = other.version_;
        }
        return *this;
    }

    /// Move constructor and assignment operator is meaningless
    MapVersionParser(MapVersionParser&& other) = delete;
    MapVersionParser& operator=(MapVersionParser&& other) = delete;

public:

    /**
     * @brief Format an uint64-form version object to string
     * @details Result form like "1.2.2020-7-30_Alpha"
     * 
     * @param[in] version_value Value of version object of uint64 form
     * @return Formatted string of version object
     */
    static std::string FormatToString(uint64_t const version_value)
    {
        return FormatToString(MapVersionParser(version_value));
    }

    /**
     * @brief Format a MapVersionParser object to string
     * @details Result form like "1.2.2020-7-30_Alpha"
     * 
     * @param[in] version Object of MapVersionParser
     * @return Format string of MapVersionParser object
     */
    static std::string FormatToString(MapVersionParser const& version)
    {
        std::map<holo::map::MapVersionParser::VersionCode, std::string> const version_code_map{
            {holo::map::MapVersionParser::VersionCode::VERSION_CODE_UNKNOWN, "Unknown"},
            {holo::map::MapVersionParser::VersionCode::VERSION_CODE_ALPHA, "Alpha"},
            {holo::map::MapVersionParser::VersionCode::VERSION_CODE_BETA, "Beta"},
            {holo::map::MapVersionParser::VersionCode::VERSION_CODE_RC, "RC"},
            {holo::map::MapVersionParser::VersionCode::VERSION_CODE_RELEASE, "Release"}
        };
        
        std::stringstream stream;
        stream << static_cast<int>(version.GetMajor()) << "."
               << static_cast<int>(version.GetPatch()) << "."
               << std::to_string(2000 + static_cast<int>(version.GetYear())) << "-"
               << static_cast<int>(version.GetMonth()) << "-"
               << static_cast<int>(version.GetDay()) << "_"
               << version_code_map.at(version.GetCode());
        return stream.str();
    }

    /**
     * @brief Check if given two version objects(objects are in uint64 form) are matching or not.
     *
     * @details If the major version numbers from those two version objects are equal,
     * those two version objects are match.
     *
     * @param[in] version_value_a One version object(in uint64 form)
     * @param[in] version_value_b Anthor version object(in uint64 form)
     * @return True if they are match,
     *         False if they not.
     */
    static bool IsVersionMatch(uint64_t const version_value_a, uint64_t const version_value_b)
    {
        return IsVersionMatch(MapVersionParser(version_value_a), MapVersionParser(version_value_b));
    }

    /**
     * @brief Check if given two version objects of MapVersionParser objects are matching or not.
     *
     * @details If the major version numbers from those two version objects are equal,
     * those two version objects are match.
     *
     * @param[in] version_parser_a One version parser
     * @param[in] version_parser_b Anthor version parser
     * @return True if they are match,
     *         False if they not.
     */
    static bool IsVersionMatch(MapVersionParser const& version_parser_a, MapVersionParser const& version_parser_b)
    {
        return (version_parser_a.GetMajor() == version_parser_b.GetMajor());
    }

public:

    /**
     * @brief Get major version number
     *
     * @return Major version number
     */
    uint8_t GetMajor() const
    {
        return readPartialBits(major_start_pos_, major_length_, version_);
    }

    /**
     * @brief Set major version number
     *
     * @param[in] major Given major version number
     */
    void SetMajor(uint8_t const major)
    {
        setPartialBits(major_start_pos_, major_length_, static_cast<uint64_t>(major), version_);
    }

    /**
     * @brief Get patch version number
     *
     * @return Patch version number
     */
    uint8_t GetPatch() const
    {
        return readPartialBits(patch_start_pos_, patch_length_, version_);
    }

    /**
     * @brief Set patch version number
     *
     * @param[in] patch Given patch version number
     */
    void SetPatch(uint8_t const patch)
    {
        setPartialBits(patch_start_pos_, patch_length_, static_cast<uint64_t>(patch), version_);
    }

    /**
     * @brief Get year of version
     *
     * @return Year of version
     */
    uint8_t GetYear() const
    {
        return readPartialBits(year_start_pos_, year_length_, version_);
    }

    /**
     * @brief Set year of version
     *
     * @param[in] year Given year value
     */
    void SetYear(uint8_t const year)
    {
        if (!isYearValueValid(year))
        {
            LOG(ERROR) << "MapVersionParser::SetYear, invalid year value = " << static_cast<int>(year);
        }
        setPartialBits(year_start_pos_, year_length_, static_cast<uint64_t>(year), version_);
    }

    /**
     * @brief Get month of version
     *
     * @return Month of version
     */
    VersionMonth GetMonth() const
    {
        return static_cast<VersionMonth>(readPartialBits(month_start_pos_, month_length_, version_));
    }

    /**
     * @brief Set month of version
     *
     * @param[in] month Given month value
     */
    void SetMonth(VersionMonth const month)
    {
        if (!isMonthValueValid(static_cast<uint8_t>(month)))
        {
            LOG(ERROR) << "MapVersionParser::SetYear, invalid month value = " << static_cast<int>(month);
        }
        setPartialBits(month_start_pos_, month_length_, static_cast<uint64_t>(month), version_);
    }

    /**
     * @brief Get day of version
     *
     * @return Day of version
     */
    uint8_t GetDay() const
    {
        return readPartialBits(day_start_pos_, day_length_, version_);
    }

    /**
     * @brief Set day of version
     *
     * @param[in] day Given day value
     */
    void SetDay(uint8_t const day)
    {
        if (!isDayValueValid(day))
        {
            LOG(ERROR) << "MapVersionParser::SetDay, invalid day value = " << static_cast<int>(day);
        }
        setPartialBits(day_start_pos_, day_length_, static_cast<uint64_t>(day), version_);
    }

    /**
     * @brief Get code of version
     *
     * @return Code of version
     */
    VersionCode GetCode() const
    {
        return static_cast<VersionCode>(readPartialBits(code_start_pos_, code_length_, version_));
    }

    /**
     * @brief Set code of version
     *
     * @param[in] code Given code value
     */
    void SetCode(VersionCode const code)
    {
        if (!isCodeValueValid(static_cast<uint8_t>(code)))
        {
            LOG(ERROR) << "MapVersionParser::SetYear, invalid code value = " << static_cast<int>(code);
        }
        setPartialBits(code_start_pos_, code_length_, static_cast<uint64_t>(code), version_);
    }

    /**
     * @brief Get uint64-form value of version
     *
     * @return uint64 form value of version
     */
    uint64_t GetVersionValue() const
    {
        return version_.to_ullong();
    }

private:

    /**
     * @brief Set value of a bit segment of one bit set which defined by its start position in bit set
     * @details
     *       low bits                 high bits
     *          |<------Bit Set---------->|
     *          |0101010000101010101010100|
     *               | bit segment |
     *               |
     *          start position
     *
     * @param[in] start_pos Start position of bit segment
     * @param[in] length Length of bit segment
     * @param[in] value Given value for bit segment
     * @param[out] bit_set Bit set to be modified
     */
    static void setPartialBits(uint8_t const start_pos, uint8_t const length, uint64_t const value,
                               std::bitset<MAPVERSION_BITSET_SIZE>& bit_set)
    {
        const uint64_t old_value = readPartialBits(start_pos, length, bit_set);
        if (value == old_value)
        {
            return;
        }
        std::bitset<MAPVERSION_BITSET_SIZE> temp_bitset{0};
        temp_bitset |= (old_value << start_pos);
        temp_bitset.flip();
        bit_set &= temp_bitset;
        bit_set |= (value << start_pos);
    }

    /**
     * @brief Read value of a bit segment of one bit set which defined by its length(how many bits this segment have)
     *        and it's starting position in bit set
     * @details
     *       low bits                 high bits
     *          |<------Bit Set---------->|
     *          |0101010000101010101010100|
     *               | bit segment |
     *               |
     *          start position (+ length = end position)
     *
     * @param[in] start_pos Start position of bit segment
     * @param[in] length Length of bit segment
     * @param[in] bit_set Bit set to be read
     * @return Value of bit segment in uint64 from
     */
    static uint64_t readPartialBits(uint8_t const start_pos, uint8_t const length,
                                    std::bitset<MAPVERSION_BITSET_SIZE> const& bit_set)
    {
        std::bitset<MAPVERSION_BITSET_SIZE> temp = bit_set << (MAPVERSION_BITSET_SIZE - static_cast<std::size_t>(start_pos + length));
        temp >>= (MAPVERSION_BITSET_SIZE - length);
        return temp.to_ullong();
    }

    /**
     * @brief Check if a year value is valid.
     * @details Valid year value should be in range of [20, 255]
     *
     * @param[in] year_value Given year value
     * @return True if this year value is valid
     *         False if not.
     */
    bool isYearValueValid(uint8_t const year_value)
    {
        if (year_value_max_ < year_value || year_value < year_value_min_)
        {
            return false;
        }
        return true;
    }

    /**
     * @brief Check if a month value is valid.
     * @details Valid month value should be in range of [1, 12]
     *
     * @param[in] month_value Given month value
     * @return True if this month value is valid
     *         False if not.
     */
    bool isMonthValueValid(uint8_t const month_value)
    {
        if (static_cast<uint8_t>(VersionMonth::VERSION_MONTH_DEC) < month_value ||
            month_value < static_cast<uint8_t>(VersionMonth::VERSION_MONTH_JAN))
        {
            return false;
        }
        return true;
    }

    /**
     * @brief Check if a day value is valid.
     * @details Valid day value should be in range of [1, 31]
     *
     * @param[in] day_value Given day value
     * @return True if this day value is valid
     *         False if not.
     */
    bool isDayValueValid(uint8_t const day_value)
    {
        if (day_value_max_ < day_value || day_value < day_value_min_)
        {
            return false;
        }
        return true;
    }

    /**
     * @brief Check if a code of version value is valid.
     * @details Valid code of version value should be in range of [1, 4]
     *
     * @param[in] code_value Given code of version value
     * @return True if this code of version value is valid
     *         False if not.
     */
    bool isCodeValueValid(uint8_t const code_value)
    {
        if (static_cast<uint8_t>(VersionCode::VERSION_CODE_RELEASE) < code_value ||
            code_value < static_cast<uint8_t>(VersionCode::VERSION_CODE_ALPHA))
        {
            return false;
        }
        return true;
    }

    /**
     * @brief Check if uint64-form version value is valid.
     *
     * @param[in] version_value Given version value in uint64-from
     * @return True if this uint64-form version value is valid
     *         False if not.
     */
    bool isVersionValueValid(uint64_t const version_value)
    {
        std::bitset<MAPVERSION_BITSET_SIZE> temp_bit_set = version_value;

        return isYearValueValid(readPartialBits(year_start_pos_, year_length_, temp_bit_set)) &&
               isMonthValueValid(readPartialBits(month_start_pos_, month_length_, temp_bit_set)) &&
               isDayValueValid(readPartialBits(day_start_pos_, day_length_, temp_bit_set)) &&
               isCodeValueValid(readPartialBits(code_start_pos_, code_length_, temp_bit_set));
    }

private:
    /// Version value in bitset form.
    std::bitset<MAPVERSION_BITSET_SIZE> version_{0};

    /// Static const variables
    /// xxx_start_pos is where the bit field start in bit set
    /// xxx_length is the length of the bit field

    /// Reserve bit field start at position 0, length is 20
    uint8_t const reserve_start_pos_ = 0;
    uint8_t const reserve_length_    = 28;

    uint8_t const major_start_pos_ = reserve_start_pos_ + reserve_length_;
    uint8_t const major_length_    = 8;

    uint8_t const patch_start_pos_ = major_start_pos_ + major_length_;
    uint8_t const patch_length_    = 8;

    uint8_t const year_start_pos_ = patch_start_pos_ + patch_length_;
    uint8_t const year_length_    = 8;

    uint8_t const month_start_pos_ = year_start_pos_ + year_length_;
    uint8_t const month_length_    = 4;

    uint8_t const day_start_pos_ = month_start_pos_ + month_length_;
    uint8_t const day_length_    = 5;

    uint8_t const code_start_pos_ = day_start_pos_ + day_length_;
    uint8_t const code_length_    = 3;

    uint8_t const year_value_min_ = 20;
    uint8_t const year_value_max_ = 255;

    uint8_t const day_value_min_ = 1;
    uint8_t const day_value_max_ = 31;

};  // Class MapVersionParser
/**
 * @}
 */
}  // namespace map
/**
 * @}
 */
}  // namespace holo

#endif /* HOLO_MAP_COMMON_MAP_VERSION_PARSER_H_ */
