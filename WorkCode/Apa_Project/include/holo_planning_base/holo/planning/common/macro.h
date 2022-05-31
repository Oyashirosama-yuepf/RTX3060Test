/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-01-19
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_MACRO_H_
#define _HOLO_PLANNING_MACRO_H_

#define DISALLOW_COPY_AND_ASSIGN(classname)         \
private:                                            \
    classname(const classname &);                   \
    classname &operator=(const classname &);

#define DISALLOW_IMPLICIT_CONSTRUCTORS(classname)   \
private:                                            \
    classname();                                    \
    DISALLOW_COPY_AND_ASSIGN(classname);

#define DECLARE_SINGLETON(classname)                \
public:                                             \
    static classname* Instance()                    \
    {                                               \
        static classname instance;                  \
        return &instance;                           \
    }                                               \
    DISALLOW_IMPLICIT_CONSTRUCTORS(classname)       \


#define UNREFERENCE_PARAM(p) ((void*)&p)

#define PRE_LANE_CHANGE(level)                      \
    LOG(level) << "[PRE_LANE_CHANGE] "

#endif