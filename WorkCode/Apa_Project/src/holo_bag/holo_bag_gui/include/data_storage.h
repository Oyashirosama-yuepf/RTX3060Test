/**
 * @file data_storage.h
 * @author housixiu (housiixu1@holomatic.com)
 * @brief the header of the DataStorage
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_BAG_GUI_DATA_STORAGE_H_
#define _HOLO_BAG_GUI_DATA_STORAGE_H_

#include <iostream>
#include <holo/core/types.h>

struct DataStorage
{
    int             argc;
    char**          argv;
    holo::float32_t rate_      = 1.0;
    holo::float64_t skip_time_ = 0.0;
    holo::float64_t bag_duration_;
    holo::float64_t bag_start_time_;  
    holo::bool_t    pause_ = false;
    std::string     config_path_;
    std::string     file_path_;
    std::string     node_name_;
};


#endif //_HOLO_BAG_GUI_DATA_STORAGE_H_