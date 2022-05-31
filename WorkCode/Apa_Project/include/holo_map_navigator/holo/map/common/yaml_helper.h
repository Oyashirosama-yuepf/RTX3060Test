/*!
 * \brief YAML helper
 * \author Yuchao Hu (huyuchao@holomatic.com)
 * \date 2019-10-11
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_YAML_HELPER_H_
#define HOLO_MAP_COMMON_YAML_HELPER_H_

#include <holo/utils/yaml.h>

namespace holo
{
namespace map
{
namespace yaml_helper
{
struct Node
{
    ::std::string                file;
    ::std::vector<::std::string> parent_keys;
    ::YAML::Node                 node;
};

///
/// @brief Load sub node by given parent node and key name
///
/// @param[in] _node Parent node
/// @param[in] _key Key name
/// @param[in] _exit_if_failed Whether exit if the sub node does not exist
/// @return Sub node
///
const Node Load(const Node& _node, const ::std::string& _key, const bool exit_if_failed = true);

///
/// @brief Load sub map node by given parent node and key name
///
/// @param[in] _node Parent node
/// @param[in] _key Key name
/// @param[in] _exit_if_failed Whether exit if the sub map node does not exist
/// @return Sub map node
///
const Node LoadMap(const Node& _node, const ::std::string& _key, const bool _exit_if_failed = true);

///
/// @brief Load sub sequence node by given parent node and key name
///
/// @param[in] _node Parent node
/// @param[in] _key Key name
/// @param[in] _exit_if_failed Whether exit if the sub sequence node does not exist
/// @return Sub sequence node
///
const Node LoadSequence(const Node& _node, const ::std::string& _key, const bool exit_if_failed = true);

///
/// @brief Load sub scalar node by given parent node and key name
///
/// @param[in] _node Parent node
/// @param[in] _key Key name
/// @param[in] _exit_if_failed Whether exit if the sub scalar node does not exist
/// @return Sub scalar node
///
const Node LoadScalar(const Node& _node, const ::std::string& _key, const bool exit_if_failed = true);

///
/// @brief Load sub scalar node's value by given parent node and key name
///
/// @tparam T Scalar type
/// @param[in] _node Parent node
/// @param[in] _key Key name
/// @param[in] _exit_if_failed Whether exit if the sub scalar node does not exist
/// @return Sub scalar node's value
///
template <typename T>
T LoadScalar(const Node& _node, const ::std::string& _key, const bool exit_if_failed = true);
}  // namespace yaml_helper
}  // namespace map
}  // namespace holo
#endif  // HOLO_MAP_COMMON_YAML_HELPER_H_
