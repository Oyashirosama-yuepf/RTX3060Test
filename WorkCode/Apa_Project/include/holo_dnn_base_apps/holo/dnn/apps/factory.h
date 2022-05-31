/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file factory.h
 * @brief This header file defines  factory class
 * @author huanglihong(huanglihong@holomatic.com)
 * @date "2020-10-21"
 */
#ifndef HOLO_DNN_FACTORY_H_
#define HOLO_DNN_FACTORY_H_

#include <holo/log/hololog.h>
#include <holo/dnn/interface.h>

#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace holo
{
namespace dnn
{
class DnnFactory
{
public:
    using AppPointer      = std::shared_ptr<DnnInterface>;
    using Creator         = std::function<std::shared_ptr<DnnInterface>()>;
    using CreatorRegistry = std::map<std::string, Creator>;

public:
    /**
     * @brief create dnn
     *
     * @param config_yaml_path config path
     * @return dnn inference
     */
    static AppPointer CreateDnn(std::string const& config_yaml_path);
    /**
     * @brief add dnn application creator
     * @param type the type name of creator
     * @param creator the application creator func
     */
    static void AddCreator(std::string const& type, Creator creator);

    /**
     * @brief Create registry
     * @return dnn registry
     */
    static CreatorRegistry& Registry();

    /**
     * @brief Get all dnn type in registry
     * @return a vector with dnn type
     */
    static std::vector<std::string> DnnTypeList();

private:
    DnnFactory();
    /**
     * @brief Get all dnn type in registry with string
     * @return a string of all dnn type
     */
    static std::string DnnTypesListString();
};

class DnnFactoryRegister
{
public:
    DnnFactoryRegister(std::string const& type, DnnFactory::Creator creator);
};

#define REGISTER_DNN_CREATOR(name, creator) static DnnFactoryRegister g_creator_##name(#name, creator)

#define REGISTER_DNN_CLASS(name, type)                                                                                 \
    std::shared_ptr<DnnInterface> Creator_##name()                                                                     \
    {                                                                                                                  \
        return std::shared_ptr<DnnInterface>(new type());                                                              \
    }                                                                                                                  \
    REGISTER_DNN_CREATOR(name, Creator_##name)

}  // namespace dnn
}  // namespace holo

#endif  // !HOLO_DNN_FACTORY_H_
