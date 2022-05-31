/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file default_initializer.h
 * @brief Default initialization of log module
 * @author moxiao@holomatic.com
 * @date 2021-09-06
 */

#ifndef HOLO_LOG_LOG4CPLUS_DEFAULT_INITIALIZER_H_
#define HOLO_LOG_LOG4CPLUS_DEFAULT_INITIALIZER_H_

namespace holo
{
namespace log
{
namespace log4cplus
{
/**
 * @brief Default Initializer
 */
class DefaultInitializer final
{
public:
    /**
     * @brief default constructor
     */
    DefaultInitializer();

    /**
     * @brief destructor
     */
    ~DefaultInitializer() noexcept;

    DefaultInitializer(DefaultInitializer const&) = delete;
    DefaultInitializer(DefaultInitializer&&)      = delete;
    DefaultInitializer& operator=(DefaultInitializer const&) = delete;
    DefaultInitializer& operator=(DefaultInitializer&&) = delete;
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo

#endif
