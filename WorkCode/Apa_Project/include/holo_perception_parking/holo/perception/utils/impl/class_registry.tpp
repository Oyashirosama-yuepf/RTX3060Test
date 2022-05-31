namespace holo
{

namespace perception
{

template<typename Base,
        typename Key>
template<typename... Args>
void ClassRegistry<Base, Key>::Register(const Key &key, Args... args)
{
    m_map[key] = std::make_shared<Base>(std::forward<Args>(args)...);
}

template<typename Base,
        typename Key>
std::shared_ptr<Base> ClassRegistry<Base, Key>::Get(const Key &key)
{
    try{
        return m_map.at(key);
    }
    catch(const std::out_of_range &e)
    {
        throw ConstrError(key);
    }
}

}   /// end namespace perception

}   /// end namespace holo