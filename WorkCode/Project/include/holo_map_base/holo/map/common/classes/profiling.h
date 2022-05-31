/*!
 *  \brief Performance profiling.
 *  \author wanghaiyang (wanghaiyang@holomaitc.com)
 *  \date 2019-06-13
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_CLASSES_PROFILING_H_
#define HOLO_MAP_COMMON_CLASSES_PROFILING_H_

#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
#include <holo/log/hololog.h>
#include <holo/os/tictoc_timer.h>
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */

#include <holo/map/common/common_type_define.h>

#include <string>

namespace holo
{
namespace map
{

class Profiling
{
public:
    Profiling() = default;
    virtual ~Profiling();

    /**
     * @param [in] _start If _start is true, the profiling object will start timing.
     * 
     */
    explicit Profiling(const bool _start);

    /**
     * @brief Cotructure with log info.
     * @param [in] _func Function name, we can use macro: __FUNC__.
     * @param [in] _file Source file name, we can use macro: __FILE__.
     * @param [in] _line Line number of _func in _file, we can use macro: __LINE__.
     */
    Profiling(const std::string& _func, const std::string _file, const int _line);

    /**
     * @brief Start timer.
     */
    void Start();

    /**
     * @brief Get elapsed from start.
     * @return Time elapsed(ms).
     */
    float64_t Elapsed();

protected:

#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    TicTocTimer timer_;
    std::string function_;
    std::string file_;
    int line_ = 0;
    bool automatic_ = false;
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */
}; ///< End of class Profiling

inline Profiling::Profiling(const bool _start)
{
#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    if (_start)
    {
        this->Start();
    }
#else
    (void)_start;
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */
}

inline Profiling::Profiling(const std::string& _func, const std::string _file, const int _line)
{
#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    this->automatic_ = true;  
    this->function_ = _func;  
    this->file_ = _file;
    this->line_ = _line;
    LOG(INFO) << "holo map performance monitor start, file=" << this->file_
              << " func=" << this->function_ << " line=" << this->line_;
    this->Start();
#else
    (void)_func;
    (void)_file;
    (void)_line;
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */
}

inline Profiling::~Profiling()
{
#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    if (this->automatic_)
    {
        const float64_t cost = this->Elapsed();
        LOG(INFO) << "holo map performance monitor stop, file=" << this->file_
                  << " func=" << this->function_ << " line=" << this->line_  << " cost=" << cost;
    }
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */
}

inline void Profiling::Start()
{
#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    timer_.Tic();
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */
}

inline float64_t Profiling::Elapsed()
{
#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    return timer_.Elapsed() * 1000;
#else
    return 0;
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */
}

#ifdef HOLO_MAP_ENABLE_PROFILING_WITH_TIMER
    #ifndef HOLO_MAP_PERFORMANCE_MONITOR_AUTO_PROFILING
        #define HOLO_MAP_PERFORMANCE_MONITOR_AUTO_PROFILING                         \
            holo::map::Profiling __holo_map_performance_monitor_auto_profiling__(   \
                std::string(__func__), std::string(__FILE__), __LINE__);
    #endif

    #ifndef HOLO_MAP_PERFORMANCE_MONITOR_PROFILING_START
        #define HOLO_MAP_PERFORMANCE_MONITOR_PROFILING_START                        \
            holo::map::Profiling __holo_map_performance_monitor_profiling__(true);
    #endif
            
    #ifndef HOLO_MAP_PERFORMANCE_MONITOR_PROFILING_END
        #define HOLO_MAP_PERFORMANCE_MONITOR_PROFILING_END                          \
            LOG(INFO) << "holo_map performance monitor, " << __func__               \
                      << " cost=" << __holo_map_performance_monitor_profiling__.Elapsed();
    #endif
#else 
    #define HOLO_MAP_PERFORMANCE_MONITOR_AUTO_PROFILING
    #define HOLO_MAP_PERFORMANCE_MONITOR_PROFILING_START
    #define HOLO_MAP_PERFORMANCE_MONITOR_PROFILING_END
#endif /* HOLO_MAP_ENABLE_PROFILING_WITH_TIMER */

} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_COMMON_CLASSES_PROFILING_H_ */
