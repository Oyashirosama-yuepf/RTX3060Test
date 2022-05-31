/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file segment.h
 * @brief segment.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-10-11"
 */

#ifndef HOLO_MAP_SERVICE_CLIENT_PROFILE_SEGMENT_H_
#define HOLO_MAP_SERVICE_CLIENT_PROFILE_SEGMENT_H_

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace profile
{
/**
 * @addtogroup profile
 * @{
 *
 */

/**
 * @brief Define a base class for segments.
 */
class SegmentInfo
{
public:
    /**
     * @brief Defien segment type.
     */
    enum class SegmentType : holo::uint8_t
    {
        kUNKNOWN    = 0,    ///< Placeholder.
        kINDEX,             ///< Segment by index.
        kPERCENT,           ///< Segment by precent.
        kDISTANCE,          ///< Segment by distance.
    }; ///< End of enum SegmentType.

    /**
     * @brief Constructor.
     * 
     * @param[in] t Segment type.
     */
    explicit SegmentInfo(SegmentType const t) : type_(t)
    {}

    /**
     * @brief Default destructor.
     */
    virtual ~SegmentInfo()
    {}

    /**
     * @brief Access segment type.
     * 
     * @return Segment type.
     */
    SegmentType GetType() const noexcept
    {
        return this->type_;
    }

protected:
    /// Segment type.
    SegmentType type_ = SegmentType::kUNKNOWN;
}; ///< End of class SegmentInfo.

/**
 * @brief Defile an object to describe a segmented attribute.
 * 
 * @tparam K Segment description.
 * @tparam V An attribute object.
 * @tparam T Segment type.
 */
template <typename K, typename V, SegmentInfo::SegmentType T = SegmentInfo::SegmentType::kUNKNOWN>
class SimpleSegmentInfo : public SegmentInfo
{
public:
    /// Redefine K type for inner members.
    using KeyType   = K;
    /// Redefine V type for inner members.
    using ValueType = V;

    /// Redefine SimpleSegmentInfo type for member functions.
    using SimpleSegmentInfoType         = SimpleSegmentInfo<K, V, T>;
    /// Redefine SimpleSegmentInfo vector type for member functions.
    using SimpleSegmentInfoVectorType   = std::vector<SimpleSegmentInfoType>;

    /**
     * @brief Default constructor.
     */
    SimpleSegmentInfo() : SegmentInfo(T)
    {}

    /**
     * @brief Default desconstructor.
     */
    virtual ~SimpleSegmentInfo()
    {}

    /**
     * @brief Access start value.
     * 
     * @return Start value.
     */
    KeyType const& GetStart() const noexcept
    {
        return this->start_;
    }

    /**
     * @brief Assign start value.
     * 
     * @param[in] t A start value.
     */
    void SetStart(KeyType const& t)
    {
        this->start_ = t;
    }

    /**
     * @brief Access end value.
     * 
     * @return End value.
     */
    KeyType const& GetEnd() const noexcept
    {
        return this->end_;
    }

    /**
     * @brief Assign end value.
     * 
     * @param[in] t End value.
     */
    void SetEnd(KeyType const& t)
    {
        this->end_ = t;
    }

    /**
     * @brief Access attribute value.
     * 
     * @return Attribute value.
     */
    ValueType const& GetValue() const noexcept
    {
        return this->value_;
    }

    /**
     * @brief Assign attribute value.
     * 
     * @param[in] v Attribtue value.
     */
    void SetValue(ValueType const& v)
    {
        this->value_ = v;
    }

    /**
     * @brief Format a SimpleSegmentInfo to a JSON string.
     * 
     * @param[in] segment A SimpleSegmentInfo object.
     * @param[in] f Format function for attribute value.
     * @return A JSON string.
     */
    static std::string FormatToString(SimpleSegmentInfo<K, V, T> const& segment, std::function<std::string (V const&)> f)
    {
        std::stringstream stream;
        stream << "{\"start\":" << segment.start_
               << ",\"end\":" << segment.end_
               << ",\"value\":" << f(segment.value_)
               << "}";
        return stream.str();
    }

    /**
     * @brief Reverse a SimpleSegmentInfo vector.
     * 
     * @param[in,out] segments An array of SimpleSegmentInfos.
     */
    static void Reverse(SimpleSegmentInfoVectorType& segments)
    {
        if (segments.empty())
        {
            return;
        }

        std::reverse(segments.begin(), segments.end());

        KeyType const border = segments.front().GetEnd();

        std::for_each(segments.begin(), segments.end(), [border](SimpleSegmentInfoType& s) -> void {
            s.SetEnd(border - s.GetEnd());
            s.SetStart(border - s.GetStart());
        });
    }

protected:
    KeyType     start_; ///< Segment start.
    KeyType     end_;   ///< Segment end.
    ValueType   value_; ///< Segment attribute.
}; ///< End of class SimpleSegmentInfo.

/// Define segment info with kINDEX type.
template <typename K, typename V, SegmentInfo::SegmentType T = SegmentInfo::SegmentType::kINDEX>
using IndexSegment = SimpleSegmentInfo<K, V, T>;

/// Define segment info with kPERCENT type.
template <typename K, typename V, SegmentInfo::SegmentType T = SegmentInfo::SegmentType::kPERCENT>
using PersentSegment = SimpleSegmentInfo<K, V, T>;

/// Define segment info with kDISTANCE type.
template <typename K, typename V, SegmentInfo::SegmentType T = SegmentInfo::SegmentType::kDISTANCE>
using DistanceSegment = SimpleSegmentInfo<K, V, T>;

/**
 * @}
 */
} ///< namespace profile
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_CLIENT_PROFILE_SEGMENT_H_ */