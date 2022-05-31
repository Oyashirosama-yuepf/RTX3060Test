/*!
 *  \brief data container for holo msgs, thread safe
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-01-16
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_COMMON_SAFE_MSG_DATA_CONTAINER_H_
#define HOLO_PERCEPTION_COMMON_SAFE_MSG_DATA_CONTAINER_H_

#include <holo/common/timestamp.h>

#include <boost/circular_buffer.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/thread.hpp>

namespace holo
{
namespace perception
{
template <typename T>
class SafeMsgDataContainer : private boost::noncopyable
{
public:
    /// format: (data, data_time_stamp, received_time_stamp)
    typedef typename std::tuple<T, holo::common::Timestamp, holo::common::Timestamp> value_type;
    typedef boost::recursive_mutex::scoped_lock                                      lock;
    typedef value_type&                                                              reference;
    typedef const value_type&                                                        const_reference;

public:
    /**
     * brief contructor
     */
    SafeMsgDataContainer()
    {
    }
    SafeMsgDataContainer(holo::int32_t n);

    /**
     * set container capacity
     */
    void SetCapacity(holo::int32_t n);

    /**
     * set max time for data container
     */
    void SetMaxTimeout(holo::float32_t timeout);

    /**
     * push latest data in container
     */
    void Pushback(const T& data, const holo::common::Timestamp& data_time,
                  const holo::common::Timestamp& received_time);

    void Popback();

    /**
     * get data from container
     */
    reference       Back();
    reference       Front();
    const_reference Back() const;
    const_reference Front() const;

    reference       operator[](size_t i);
    reference       At(size_t i);
    const_reference operator[](size_t i) const;
    const_reference At(size_t i) const;

    /**
     * clear container
     */
    void Clear();

    /**
     * get container property
     */
    bool Empty();

    /**
     * slef check with data time stamp
     */
    void SelfCheckByDataTimeStamp(const holo::common::Timestamp& base_time);

    /**
     * self check with received data time stamp
     */
    void SelfCheckByReceivedTimeStamp(const holo::common::Timestamp& base_time);

private:
    boost::circular_buffer<value_type> container_;
    boost::recursive_mutex             monitor_;
    holo::float32_t                    max_timeout_;
};

}  // namespace perception

}  // namespace holo

#include "impl/safe_msg_data_container.tpp"

#endif  /// HOLO_PERCEPTION_COMMON_SAFE_MSG_DATA_CONTAINER_H_
