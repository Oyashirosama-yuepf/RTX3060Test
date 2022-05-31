/*!
 *  \brief implementation for data container for holo msgs, thread safe
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-01-16
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

namespace holo
{
namespace perception
{
template <typename T>
SafeMsgDataContainer<T>::SafeMsgDataContainer(holo::int32_t n)
{
    SetCapacity(n);
    max_timeout_ = 2;
}

template <typename T>
void SafeMsgDataContainer<T>::SetCapacity(holo::int32_t n)
{
    container_.set_capacity(n);
}

template <typename T>
void SafeMsgDataContainer<T>::SetMaxTimeout(holo::float32_t timeout)
{
    max_timeout_ = timeout;
}

template <typename T>
void SafeMsgDataContainer<T>::Pushback(const T& data, const holo::common::Timestamp& data_time,
                                       const holo::common::Timestamp& received_time)
{
    lock       lk(monitor_);
    value_type value = std::make_tuple(data, data_time, received_time);
    container_.push_back(value);
}

template <typename T>
void SafeMsgDataContainer<T>::Popback()
{
    lock lk(monitor_);
    container_.pop_back();
}

template <typename T>
typename SafeMsgDataContainer<T>::reference SafeMsgDataContainer<T>::Front()
{
    lock lk(monitor_);
    return container_.front();
}

template <typename T>
typename SafeMsgDataContainer<T>::reference SafeMsgDataContainer<T>::Back()
{
    lock lk(monitor_);
    return container_.back();
}

template <typename T>
typename SafeMsgDataContainer<T>::const_reference SafeMsgDataContainer<T>::Front() const
{
    lock lk(monitor_);
    return container_.fornt();
}

template <typename T>
typename SafeMsgDataContainer<T>::const_reference SafeMsgDataContainer<T>::Back() const
{
    lock lk(monitor_);
    return container_.back();
}

template <typename T>
void SafeMsgDataContainer<T>::Clear()
{
    lock lk(monitor_);
    container_.clear();
}

template <typename T>
typename SafeMsgDataContainer<T>::reference SafeMsgDataContainer<T>::operator[](size_t i)
{
    lock lk(monitor_);
    return container_[i];
}

template <typename T>
typename SafeMsgDataContainer<T>::reference SafeMsgDataContainer<T>::At(size_t i)
{
    lock lk(monitor_);
    return container_.at(i);
}

template <typename T>
typename SafeMsgDataContainer<T>::const_reference SafeMsgDataContainer<T>::operator[](size_t i) const
{
    lock lk(monitor_);
    return container_[i];
}

template <typename T>
typename SafeMsgDataContainer<T>::const_reference SafeMsgDataContainer<T>::At(size_t i) const
{
    lock lk(monitor_);
    return container_.at(i);
}

template <typename T>
bool SafeMsgDataContainer<T>::Empty()
{
    lock lk(monitor_);
    return container_.empty();
}

template <typename T>
void SafeMsgDataContainer<T>::SelfCheckByDataTimeStamp(const holo::common::Timestamp& base_time)
{
    lock lk(monitor_);

    if (container_.empty() == true)
    {
        return;
    }

    holo::common::Timestamp newest_time = std::get<1>(container_.back());
    if (fabs((base_time - newest_time).ToSec()) > max_timeout_)
    {
        container_.clear();
    }
}

template <typename T>
void SafeMsgDataContainer<T>::SelfCheckByReceivedTimeStamp(const holo::common::Timestamp& base_time)
{
    lock lk(monitor_);

    if (container_.empty() == true)
    {
        return;
    }

    holo::common::Timestamp newest_time = std::get<2>(container_.back());

    if (fabs((base_time - newest_time).ToSec()) > max_timeout_)
    {
        container_.clear();
    }
}

}  // namespace perception

}  // namespace holo
