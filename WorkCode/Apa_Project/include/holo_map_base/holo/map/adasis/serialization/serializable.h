/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file serializable.h
 * @brief This header file defines the Objects that can be serialized.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-08
 */
#ifndef HOLO_MAP_ADASIS_SERIALIZABLE_H_
#define HOLO_MAP_ADASIS_SERIALIZABLE_H_

namespace holo
{
namespace map
{
namespace adasis
{
namespace serialization
{
class Deserializer;
class Serializer;

/// Objects that can be serialized
class Serializable
{
public:
    inline Serializable() {}
    inline virtual ~Serializable(){};

    virtual void Serialize(Serializer& s) const = 0;
    virtual void Deserialize(Deserializer& s)   = 0;
};

} // namespace serialization
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_SERIALIZABLE_H_ */