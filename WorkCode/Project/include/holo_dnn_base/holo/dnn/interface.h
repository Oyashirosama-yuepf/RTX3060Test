/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file interface.h
 * @brief This header file defines interface
 * @author huanglihong(huanglihong@holomatic.com)
 * @date "2020-10-21"
 */

#ifndef HOLO_DNN_INTERFACE_H_
#define HOLO_DNN_INTERFACE_H_
#include <holo/perception/common/box2d.h>
#include <holo/perception/common/box_object.h>

#include <string>
namespace holo
{
namespace dnn
{
class DnnInterface
{
public:
    /**
     * @brief init dnn with app on target platform based on yaml config
     *
     * @param node config_yaml_path app config yaml path
     * @return success or fail
     */
    virtual holo::bool_t Init(std::string const& config_yaml_path) = 0;

    /**
     * @brief preprocess data
     *
     * @param array_data_ptr data pointer, maybe opencv mat or raw nv12 data
     * @return
     */
    virtual holo::bool_t PreProcess(const void* const array_data_ptr) = 0;

    /**
     * @brief inference on target platform
     * @param array_data_ptr input
     * @param array_output_ptr output
     *
     * @param
     */
    virtual holo::bool_t Inference(const void* const array_data_ptr, void* const array_output_ptr) = 0;

    /**
     * @brief post process
     * @param array_output_ptr output data pointer, maybe vector<bbox2d> type or something else
     * @return
     */
    virtual holo::bool_t PostProcess(void* const array_output_ptr) = 0;

    /**
     * @brief show dnn env
     * @param
     * @return
     */
    virtual void ShowDnnEnv() = 0;

    /**
     * @brief release resources such as memory and handles
     *
     * @param
     * @return
     */
    virtual ~DnnInterface(){};
};

}  // namespace dnn
}  // namespace holo

#endif  // !HOLO_DNN_INTERFACE_H_
