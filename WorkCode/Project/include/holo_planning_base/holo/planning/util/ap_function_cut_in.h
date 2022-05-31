/*!
 *  \brief
 *  \author huangwenhui (huangwenhui@holomatic.com)
 *  \date Oct 17 2019
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _AP_FUNCTION_CUT_IN_H_
#define _AP_FUNCTION_CUT_IN_H_

#include <holo/planning/util/ap_function.h>

namespace holo
{
namespace planning
{
class APFunctionCutIn : public APFunction
{
public:
    APFunctionCutIn();

    ~APFunctionCutIn();

    /**
     * @brief      According to current apf ,calculate cut-in-car'artificaldistance ,used in current class's function : EffectiveCutIn
     *
     * @param[in]  current headway_time      The   headway_time
     * @param      apf_param                 The   dist  ,The   v_ego, The   v_ob
     * @param      vehicle length            The   car_length
     * @return     artificaldistance
     */
    float64_t CalcArtificalDistance(const float64_t& headway_time, const APF_PARAM& param, const float32_t& car_length);

    /**
     * @brief      According to confidence headway time calc safedist when artificial dist equal to zero ,used in current class's function :  CalcAvoidCutIn
     *
     * @param[in]  confidence_headwaytime    The   headway_time
     * @param      apf_param                 The   v_ego  ,The  v_ob
     * @param      vehicle length            The   car_length
     *
     * @return     safe dist when apf's headway time equal to confidence_headwaytime
     */
    float64_t CalcSafeDistance(const float64_t& headway_time, const APF_PARAM& param, const float64_t& car_length);
};

}  // namespace planning
}  // namespace holo

#endif
