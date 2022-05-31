/*!
 * @file stamped.h
 * @brief a class which stamp the data structure with Timestamp.
 * @author lichao@holomatic.com
 * @date Oct 07, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_LOCALIZATION_COMMON_STAMPED_H_
#define HOLO_LOCALIZATION_COMMON_STAMPED_H_

#include <holo/common/timestamp.h>

namespace holo
{
namespace localization
{
/**
 * @brief define a compare functor for stamped data which need to be sorted in time order
 *
 * @tparam T a stamped data structure
 */
template <typename T>
struct StampedTimeCompareT
{
    using Timestamp = holo::common::Timestamp;
    /**
     * @brief the compare operator for sorting data in ascending time order.
     *
     * @param ls the left Timestamp
     *
     * @param rs the right Timestamp
     *
     * @return is right order
     */
    bool_t operator()(const T& ls, const T& rs) const
    {
        return ls.GetTimestamp() < rs.GetTimestamp();
    }

    /**
     * @brief the compare operator for sorting data in ascending time order.
     *
     * @param ls the left Timestamp
     *
     * @param rs the right data which contains Timestamp
     *
     * @return is right order
     */
    bool_t operator()(const Timestamp& ls, const T& rs) const
    {
        return ls < rs.GetTimestamp();
    }

    /**
     * @brief the compare operator for sorting data in ascending time order.
     *
     * @param ls the left data which contains Timestamp
     *
     * @param rs the right Timestamp
     *
     * @return is right order
     */
    bool_t operator()(const T& ls, const Timestamp& rs) const
    {
        return ls.GetTimestamp() < rs;
    }
}; /* struct StampedTimeCompareT */

/**
 * @brief This class can stamp the data structure with a holo Timestamp.
 *
 * @tparam T a data structure
 */
template <class T>
class StampedT
{
public:
    using Timestamp = holo::common::Timestamp;

    /**
     * @brief default constructor
     */
    StampedT() : timestamp_(0, 0), data_()
    {
    }

    /**
     * @brief Construct a new Stamped T object from another one
     *
     * @param rhs right hand side Stamped T object
     */
    StampedT(const StampedT& rhs) : timestamp_(rhs.timestamp_), data_(rhs.data_)
    {
    }

    /**
     * @brief copy assignment operator oveloading
     *
     * @param rhs right hand side Stamped T object
     * @return StampedT&
     */
    StampedT& operator=(const StampedT& rhs)
    {
        timestamp_ = rhs.timestamp_;
        data_      = rhs.data_;
        return *this;
    }

    /**
     * @brief constructor from Timestamp and data
     */
    StampedT(const Timestamp& Timestamp, const T& data) : timestamp_(Timestamp), data_(data)
    {
    }

    /**
     * @brief set Timestamp
     *
     * @param Timestamp Timestamp of object
     */
    void SetTimestamp(const Timestamp& Timestamp)
    {
        timestamp_ = Timestamp;
    }

    /**
     * @brief get const Timestamp
     *
     * @return const Timestamp
     */
    const Timestamp& GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    /**
     * @brief get Timestamp
     *
     * @return Timestamp
     */
    Timestamp& GetTimestamp() noexcept
    {
        return timestamp_;
    }
    /**
     * @brief set data
     *
     * @param data the data
     */
    void SetData(const T& data)
    {
        data_ = data;
    }

    /**
     * @brief get const data
     *
     * @return const data
     */
    const T& GetData() const
    {
        return data_;
    }

    /**
     * @brief get date
     *
     * @return data
     */
    T& GetData()
    {
        return data_;
    }

private:
    Timestamp timestamp_;  ///< the Timestamp of stamped data.

    T data_;  ///< the content data of stamped data.

}; /* StampedT */

} /* namespace localization */

} /* namespace holo */

#endif /* HOLO_LOCALIZATION_COMMON_STAMPED_H_ */
