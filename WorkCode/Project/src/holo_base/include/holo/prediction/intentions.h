/**
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file intentions.h
 * @brief Defines Intentions class.
 * @author xieshuai(xieshuai@holomatic.com)
 * @date "2019-12-23"
 */

#include <functional>
#include <unordered_set>

#include <holo/common/timestamp.h>
#include <holo/core/exception.h>
#include <holo/core/types.h>
#include <holo/prediction/intention.h>
#include <holo/serialization/serialization.h>

#ifndef HOLO_PREDICTION_INTENTIONS_H_
#define HOLO_PREDICTION_INTENTIONS_H_

namespace holo
{
namespace prediction
{
/**
 * @addtogroup prediction
 *
 * @{
 */

/**
 * @brief Intentions class.
 *
 *
 * @details This class is implemented as an unordered set of Intention.
 */
class Intentions
{
public:

    using Timestamp = holo::common::Timestamp;

    /**
     * @brief Hash function class for hashing Intention.
     */
    class Hash
    {
    public:
        size_t operator()(Intention const& key) const
        {
            return std::hash<uint32_t>()(key.GetId());
        }
    };

    /**
     * @brief KeyEqual function class for comparing Intention.
     */
    class KeyEqual
    {
    public:
        bool_t operator()(Intention const& lhs, Intention const& rhs) const
        {
            return lhs.GetId() == rhs.GetId();
        }
    };

    using Container      = std::unordered_set<Intention, Hash, KeyEqual>;
    using key_type       = uint32_t;
    using value_type     = Intention;
    using size_type      = size_t;
    using const_iterator = Container::const_iterator;

    /**
     * @brief Default constructor. Zero initializes stamp_ and default-initializes Container.
     */
    Intentions() : stamp_(0u, 0u), data_()
    {
    }

    /**
     * @brief Copy constructor.
     */
    Intentions(Intentions const& other) : stamp_(other.stamp_), data_(other.data_)
    {
    }

    /**
     * @brief Move constructor.
     */
    Intentions(Intentions&& other) : stamp_(std::move(other.stamp_)), data_(std::move(other.data_))
    {
    }

    /**
     * @brief Destructor
     */
    ~Intentions() noexcept
    {
    }

    /**
     * @brief Get timestamp (only for use by ROS/DDS for indexing)
     *
     * @return const reference to timestamp
     */
    Timestamp const& GetTimestamp() const noexcept
    {
        return stamp_;
    }

    /**
     * @brief Set timestamp (only for use by ROS/DDS for indexing)
     *
     * @param stamp stamp
     */
    void SetTimestamp(Timestamp const& stamp)
    {
        stamp_ = stamp;
    }

    /**
     * @brief Read-only access to Intention with specified ID
     *
     * @param id Intention ID
     *
     * @throw std::out_of_range when ID is not found in Intentions
     *
     * @return const reference to Intention if specified ID
     */
    value_type const& At(key_type const& id) const
    {
        auto const iter = data_.find(Intention(id));
        if (iter != data_.end())
        {
            return *iter;
        }
        else
        {
            throw holo::exception::OutOfRangeException("ID not found");
        }
    }

    /**
     * @brief Find Intention with specified ID
     *
     * @param key Intention ID
     *
     * @return const iterator to found key or end of Intentions if not
     */
    const_iterator Find(key_type const& id) const
    {
        return data_.find(Intention(id));
    }

    /**
     * @brief Get const iterator to first Intention in Intentions
     *
     * @return const iterator to first Intention in Intentions
     */
    const_iterator begin() const noexcept
    {
        return data_.begin();
    }

    /**
     * @brief Get const iterator to end of Intentions
     *
     * @return const iterator to end of Intentions
     */
    const_iterator end() const noexcept
    {
        return data_.end();
    }

    /**
     * @brief Insert Intention to Intentions
     *
     * @param intention Intention
     *
     * @details No insertion is performed if key is found in Intentions.
     *
     * @return boolean flag indicating if insertion succeeds
     */
    bool_t Insert(value_type const& intention)
    {
        return data_.insert(intention).second;
    }

    /**
     * @brief Insert Intention to Intentions with inplace element construction.
     *
     * @param stamp_start start of intention life time
     * @param stamp_end end of intention life time
     * @param id obstacle UUID
     * @param lateral_intention lateral intention type
     * @param longitudinal_intention longitudinal intention type
     * @param lateral_confidence lateral_confidence of intention in range: [0.0f, 1.0f]
     * @param longitudinal_confidence longitudinal_confidence of intention in range: [0.0f, 1.0f]
     *
     * @details No insertion is performed if key is found in Intentions.
     *
     * @return boolean flag indicating if insertion succeeds
     */
    bool_t Emplace(Timestamp const& stamp_start, Timestamp const& stamp_end,
                   uint32_t const& id, Intention::LateralIntention const& lateral_intention,
                   Intention::LongitudinalIntention const& longitudinal_intention, float32_t const& lateral_confidence,
                   float32_t const& longitudinal_confidence)
    {
        return data_
            .emplace(stamp_start, stamp_end, id, lateral_intention, longitudinal_intention, lateral_confidence,
                     longitudinal_confidence)
            .second;
    }

    /**
     * @brief Erase Intention with specified ID
     *
     * @param id Intention ID
     *
     * @return boolean flag indicating if erase succeeds
     */
    bool_t Erase(key_type const& id)
    {
        for (auto iter = data_.begin(); iter != data_.end(); iter++)
        {
            if (iter->GetId() == id)
            {
                (void)data_.erase(iter);
                return true;
            }
        }
        return true;
    }

    /**
     * @brief Count number of elements in Intentions
     *
     * @return number of elements in Intentions
     */
    size_type size() const noexcept
    {
        return data_.size();
    }

    /**
     * @brief Erases all elements of Intentions
     *
     */
    void clear() noexcept
    {
        data_.clear();
    }

    /**
     * @brief Copy assignment operator
     *
     * @param other Intentions
     */
    Intentions& operator=(Intentions const& other)
    {
        stamp_ = other.stamp_;
        data_  = other.data_;
        return *this;
    }

    /**
     * @brief Move assignment operator
     *
     * @param other Intentions
     */
    Intentions& operator=(Intentions&& other)
    {
        stamp_ = std::move(other.stamp_);
        data_  = std::move(other.data_);
        return *this;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        uint32_t size         = 0;
        size_t   aligned_size = stamp_.GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(size);
        for (Intentions::const_iterator iter = begin(); iter != end(); iter++)
        {
            aligned_size += iter->GetSerializedSize<ALIGN>();
        }
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << stamp_ << static_cast<uint32_t>(size()) << holo::serialization::align;
        for (Intentions::const_iterator iter = begin(); iter != end(); iter++)
        {
            serializer << *iter;
        }
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t size;
        deserializer >> stamp_ >> size >> holo::serialization::align;
        for (uint32_t i = 0; i < size; i++)
        {
            Intention intention;
            deserializer >> intention;
            Insert(intention);
        }
    }

private:
    Timestamp stamp_;
    Container               data_;
};

/**
 * @}
 */

}  // namespace prediction
}  // namespace holo

#endif
