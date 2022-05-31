/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2018-01-24
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_AP_FUNCTION_H_
#define _HOLO_PLANNING_AP_FUNCTION_H_

#include <holo/log/hololog.h>
#include <holo/core/types.h>

namespace holo
{
namespace planning
{
class APFunction
{
public:
    struct APF_PARAM
    {
        float64_t v_ego;
        float64_t a_ego;
        float64_t v_ob;
        float64_t a_ob;
        float64_t dist_ob;
    };

public:
    /**
     * @brief      Contructor.
     */
    APFunction();

    /**
    * @brief      Contructor.
    */
    APFunction(float64_t headway_time,
               float64_t k1,
               float64_t k2,
               float64_t k3,
               float64_t cd,
               float64_t stand_still);

    /**
     * @brief      Destroys the object.
     */
    ~APFunction();

    /**
     * @brief      Calculates the artifical distance.
     *
     * @param[in]  param  The parameter.
     *
     * @return     The artifical distance.
     */
    float64_t CalcArtificalDistance(const APF_PARAM& param, const float32_t car_length) const;

    float64_t CalcStableDistance(float64_t v) const;

    /*
     * @brief      Calculates the acceleration.
     *
     * @param[in]  dist  The artificial distance
     *
     * @return     The acceleration.
     */
    float64_t CalcAcceleration(float64_t dist) const;

    /**
     * @brief      Sets the headway time.
     *
     * @param[in]  time  The time
     */
    void SetHeadwayTime(const float64_t& time);

    /**
     * @brief      Gets the headway time.
     *
     * @return     The headway time.
     */
    float64_t GetHeadwayTime() const;

    /**
     * @brief      Sets the k1 of APF.
     *
     * @param[in]  k1    The k1
     */
    void SetK1(const float64_t& k1);

    /**
     * @brief      Gets the k1 of APF.
     *
     * @return     The k1.
     */
    float64_t GetK1() const;

    /**
     * @brief      Sets the k2 of APF.
     *
     * @param[in]  k2    The k2
     */
    void SetK2(const float64_t& k2);

    /**
     * @brief      Gets the k2 of APF.
     *
     * @return     The k2.
     */
    float64_t GetK2() const;

    /**
     * @brief      Sets the k3 of APF.
     *
     * @param[in]  k3    The k3
     */
    void SetK3(const float64_t& k3);

    /**
     * @brief      Gets the k3 of APF.
     *
     * @return     The k3.
     */
    float64_t GetK3() const;

    /**
     * @brief      Sets the cd.
     *
     * @param[in]  cd   The bandwidth of the apf
     */
    void SetCd(const float64_t& cd);

    /**
     * @brief      Gets the cd.
     *
     * @return     The bandwidth of the apf.
     */
    float64_t GetCd() const;

    /**
     * @brief      Sets the stand still.
     *
     * @param[in]  stand_still  The stand still
     */
    void SetStandStill(const float64_t& stand_still);

    /**
     * @brief      Gets the stand still.
     *
     * @return     The stand still.
     */
    float64_t GetStandStill() const;

protected:
    /**
     * headway time of the apf
     */
    float64_t headway_time_;

    /**
     * k1 of the apf
     */
    float64_t k1_;

    /**
     * k2 of the apf
     */
    float64_t k2_;

    /**
     * k3 of the apf
     */
    float64_t k3_;

    /**
     * bandwidth of the apf
     */
    float64_t cd_;

    /**
     * minimum distance to the leading vehicle
     */
    float64_t stand_still_;

    /**
     * maximum follow distance
     */
    float64_t max_follow_distance_;

    /**
     * depend on k2 and k3
     */
    float64_t ce_;
};

}  // namespace planning
}  // namespace holo

#endif
