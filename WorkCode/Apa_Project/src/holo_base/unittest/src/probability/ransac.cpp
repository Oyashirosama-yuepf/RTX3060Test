#include <holo/geometry/point2.h>
#include <holo/probability/ransac/ransac.h>
#include <holo/probability/ransac/ransac_line2_fitting_problem.h>

using Scalar      = holo::float64_t;
using ProblemType = holo::RansacLine2FittingProblemT<Scalar>;
template class holo::Ransac<ProblemType>;
