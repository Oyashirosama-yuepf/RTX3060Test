/*!
 *  \brief
 *  \author lisongze (lisongze@holomatic.com)
 *  \date 2018-11-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_PERCEPTION_UTILS_CLASS_REGISTRY_H_
#define HOLO_PERCEPTION_UTILS_CLASS_REGISTRY_H_

//STL
#include <unordered_map>
#include <memory>

namespace holo
{

namespace perception
{

template<typename Key>
class RegistryConstructionError : public std::exception
{
public:
    RegistryConstructionError(const Key &key)   :key(key){}

    const char *what()const throw(){return "Undefined key";}
    const Key key;
};

template<typename Base, typename Key>
class ClassRegistry
{
public:

    ClassRegistry() = default;
    ~ClassRegistry() = default;

    template<typename... Args>
    void Register(const Key &key, Args... args);

    std::shared_ptr<Base> Get(const Key &key);

private:

    std::unordered_map<Key, std::shared_ptr<Base> > m_map;

public:
    typedef RegistryConstructionError<Key> ConstrError;
};

}   /// end namespace perception

}   /// end namespace holo

#include "impl/class_registry.tpp"

#endif // HOLO_PERCEPTION_UTILS_CLASS_REGISTRY_H_