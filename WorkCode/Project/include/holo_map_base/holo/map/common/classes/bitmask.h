/*!
*  \brief
*  \author Hao Wentian(haowentian@holomaitc.com)
*  \date 2018-08-04
*  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
*  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
*/
#ifndef HOLO_MAP_COMMON_CLASSES_BITMASK_H_
#define HOLO_MAP_COMMON_CLASSES_BITMASK_H_

#include <bitset>
#include <type_traits>

#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{
/**
 * @brief Definition of bitset with enum class
 *
 * @tparam TYPE_ENUM_CLASS type of enum class
 * @tparam N size of bitset
 * @tparam T type of value
 */
template<typename TYPE_ENUM_CLASS, size_t N = 64U, typename T = holo::uint64_t>
class EnumClassBitset
{
public:
    /**
     * @brief Constructor
     *
     */
    EnumClassBitset()
    {

    }

    EnumClassBitset(const std::string& _value):
        value_(_value)
    {

    }

    EnumClassBitset(const T _value):
        value_(std::bitset<N>(_value))
    {

    }

    /**
     * @brief Destructor
     *
     */
    ~EnumClassBitset() noexcept
    {

    }

    /**
     * @brief Check if a specific item in enum class is set
     * @param[in] _id item of enum class
     * @return true if this item is set (this bit is 1)
     */
    bool Test(const TYPE_ENUM_CLASS _id) const
    {
        if (GetItem(_id) < 0)
        {
            return false;
        }
        return value_.test(static_cast<::std::size_t>(GetItem(_id)));
    }

    /**
     * @brief Set specific bit to be 1
     * @param[in] _id item of enum class. This bit will be set 1
     */
    void Set(const TYPE_ENUM_CLASS _id)
    {
        if (GetItem(_id) < 0)
        {
            return;
        }
        value_.set(static_cast<::std::size_t>(GetItem(_id)));
    }

    /**
     * @brief Assignment of an enum class
     * @param[in] _action the whole bitset of enum class
     */
    void Set(const std::bitset<N>& _value)
    {
        value_ = _value;
    }

    /**
     * @brief Assignment of an enum class
     * @param[in] _action the whole bitset of enum class
     */
    void Set(const T _value)
    {
        value_ = std::bitset<N>(_value);
    }

    /**
     * @brief Set specific bit to be 0
     * @param[in] _action_idx item of enum class. This bit will be set 0
     */
    void Clear(const TYPE_ENUM_CLASS _id)
    {
        if (GetItem(_id) < 0)
        {
            return;
        }
        value_.reset(static_cast<::std::size_t>(GetItem(_id)));
    }

    /**
     * @brief Clear all bits
     *
     */
    void Clear()
    {
        value_.reset();
    }

    /**
     * @brief Get the whole bitmask (all bits included)
     * @return an integer-formed action value
     */
    T GetValue() const
    {
        return value_.to_ulong();
    }

private:
    /**
     * @brief Get item from enum class
     *
     * @param v
     * @return std::underlying_type<TYPE_ENUM_CLASS>::type
     */
    typename std::underlying_type<
        TYPE_ENUM_CLASS>::type GetItem(TYPE_ENUM_CLASS _v) const
    {
        return static_cast<typename std::underlying_type<
            TYPE_ENUM_CLASS>::type>(_v);
    }

private:
    std::bitset<N> value_;
};

} // namespace map
} // namespace holo

#endif /* HOLO_MAP_COMMON_CLASSES_BITMASK_H_ */
