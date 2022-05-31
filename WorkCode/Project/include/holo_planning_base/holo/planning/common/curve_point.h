/*!
 *  \brief
 *  \author sunlei (sunlei@holomatic.com)
 *  \date 2017-11-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _HOLO_PLANNING_CURVE_POINT_H_
#define _HOLO_PLANNING_CURVE_POINT_H_

#include <vector>

#include <holo/planning/common/headers.h>

namespace holo
{
namespace planning
{
/**
 * @brief   This class describe a Point On a Curve.
 *
 * @details Since So Many People disagree with the name change of this file, I will give a detailed explaination of the
 *          reason and list all the flaws of the original design.
 *          CONS:
 *          1. Using a typedef under the outmost name space holo::planning is not good.
 *             Let's go further more on this topic: Can anyone knows exactly how many typedef, static, const exists and
 *             their location in holo::planning?
 *          2. The design of the original file is not good. The purpose of it is to define a Class representing a
 *             ReferencePath. But, the only Class in this file represents a Point on a ReferencePath and only one line
 *             of code implies the file name: reference_path.h.
 *          3. As stated(for no use of abbreviations), since long names are not distateful, what's the use of typedef here?
 *             Why a statement like, std::vector<ReferencePathPoint> is not good? Is not clear?
 *          4. Making a Abstraction in this file seems to be a better idea, at least to me. I want this Class/File to
 *             represent a Point On A Curve and providing all the information and operations planning module needs.
 *
 *          Some defence on abbreviations:
 *          1. Ref is a very well-known abbreviation for reference, it is listed in wikipedia.
 *          2. CurvePoint could be understood by developers from other team, it is not vague.
 *          3. Yes, Longnames are not forbidden for usage in google cpp style guide, But they do have some particles of
 *             the document dealing with the format problems caused by those really long names.
 *          4. We found the original Long Names "friendly and easy for reading"(not noly talking about this file),
 *             probably because we know very well of the existing code. Which means, we found it "familiar" but not
 *             "easy for reading".
 *             Just think,
 *             LongggReturnType LongggggClassName::ReallyLonggggggggggggggggggggFunctionName (LonggggVariableNames a,
 *                                                                                            LonggggVariableNames b,
 *                                                                                            LonggggVariableNames c,
 *                                                                                            LonggggVariableNames d)
 *             This kind of Longgg things also appears in a variable declaration, if statement...
 *             Does this kind of writing really optimal for readibility?
 *             Or the following expressions better:
 *             ReturnType ClassName::Function(Type a, Type b, Type c, Type d) ...
 *             As long as the meaning is clear, I always treats simple words as powerful and long expressions
 *             cumbersome.
 *
 */
class CurvePoint
{
public:
    CurvePoint()  = default;
    ~CurvePoint() = default;

    void      SetX(float64_t x) noexcept;
    float64_t GetX() const noexcept;

    void      SetY(float64_t y) noexcept;
    float64_t GetY() const noexcept;

    void      SetZ(float64_t z) noexcept;
    float64_t GetZ() const noexcept;

    void      SetTheta(float64_t theta) noexcept;
    float64_t GetTheta() const noexcept;

    void      SetKappa(float64_t kappa) noexcept;
    float64_t GetKappa() const noexcept;

    void      SetDKappa(float64_t dkappa) noexcept;
    float64_t GetDKappa() const noexcept;

    void      SetS(float64_t s) noexcept;
    float64_t GetS() const noexcept;

    void      SetConf(float64_t conf) noexcept;
    float64_t GetConf() const noexcept;

    float64_t Dist(const CurvePoint& point) const;

protected:
    float64_t x_          = 0.0;
    float64_t y_          = 0.0;
    float64_t z_          = 0.0;
    float64_t theta_      = 0.0;
    float64_t kappa_      = 0.0;
    float64_t dkappa_     = 0.0;
    float64_t s_          = 0.0;
    float64_t confidence_ = 0.0;
};

}  // namespace planning
}  // namespace holo

#endif
