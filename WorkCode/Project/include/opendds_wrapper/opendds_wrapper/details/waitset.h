#ifndef OPENDDS_WRAPPER_DETAILS_WAITSET_H_
#define OPENDDS_WRAPPER_DETAILS_WAITSET_H_

#include <functional>
#include <mutex>
#include <unordered_map>

#include <dds/DCPS/WaitSet.h>

#include "exceptions.h"

namespace opendds_wrapper
{
class WaitSet
{
public:
    WaitSet();

    void                  AddCallback(DDS::Condition* condition, std::function<void()> const& callback);
    std::function<void()> GetCallback(DDS::Condition* condition);
    void                  DeleteCallback(DDS::Condition* condition);
    void                  DeleteAllCallback();
    DDS::ReturnCode_t     Wait(DDS::ConditionSeq& seq, int32_t sec, uint32_t nsec);

    void AddSchedule(DDS::Condition* condition);
    void SetSchedule(DDS::Condition* condition, bool schedule);
    bool GetSchedule(DDS::Condition* condition);
    void DeleteSchedule(DDS::Condition* condition);
    void DeleteAllSchedule();

private:
    using CallbackMap = std::unordered_map<DDS::Condition*, std::function<void()>>;
    using ScheduleMap = std::unordered_map<DDS::Condition*, bool>;

    CallbackMap        callback_map_;
    ScheduleMap        schedule_map_;
    DDS::WaitSet       waitset_;
    mutable std::mutex schedule_mutex_;
    mutable std::mutex callback_mutex_;
};

}  // namespace opendds_wrapper

#endif
