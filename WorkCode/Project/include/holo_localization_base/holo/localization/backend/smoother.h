/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file smoother.h
 * @brief a class which smoothing factor graph
 * @author Li Chao (lichao@holomatic.com)
 * @author Bai Pengfei (baipengfei@holomatic.com)
 * @date Dec 04, 2019
 */

#ifndef HOLO_LOCALIZATION_BACKEND_SMOOTHER_H_
#define HOLO_LOCALIZATION_BACKEND_SMOOTHER_H_

#include <holo/common/optional.h>
#include <holo/localization/backend/factor_graph.h>
#include <holo/localization/common/imu_preintegration.h>
#include <holo/localization/common/wheel_preintegration.h>

namespace holo
{
namespace localization
{
/**
 * @addtogroup backend
 * @{
 *
 */

/**
 * @brief define parameters for smoother
 *
 */
struct SmootherParameters
{
    /**
     * @brief define optimizer type used in Smoother
     *
     */
    enum class OptimizerType
    {
        DOGLEG = 0,  ///< Dog leg optimizer which is more robust
        GN     = 1,  ///< Gauss Newton optimizer which needs good initial values

    };  // OptimizerType

    Scalar  lag_size                        = 2.0;     ///< the lag size of smoother, in unit of seconds.
    bool_t  get_all_values                  = false;   ///< the flag of get all of values in smootehr. (default: false)
    bool_t  get_covariance_matrix           = true;    ///< the flag of get covariance matrix of state (default: true).
    uint8_t additional_iterations           = 0u;      ///< optional perform multiple ISAM2 iterations.
    bool_t  enable_factor_error_computation = false;   ///< the flag of factor error computation.
    bool_t  verbose                         = false;   ///< the verbosity of smoother. (default: false)
    bool_t  throw_cheirality                = false;   ///< if true, rethrows Cheirality exceptions (default: false)
    bool_t  verbose_cheirality              = false;   ///< if true, prints text for Cheirality exceptions
    bool_t  find_unused_factor_slots        = true;    ///< enable this option to add factors in the first
                                                       ///< available factor slots, to avoid accumulating
                                                       ///< NULL factor slots, at the cost of having to search
                                                       ///< for slots every time a factor is added. (default: true)
    OptimizerType optimizer_type = OptimizerType::GN;  ///< Optimizer type used in smoother

    Scalar relinearize_threshold = 0.1;  ///< only relinearize variables whose linear delta magnitude is larger
                                         ///< than this threshold, it will influence accuracy(small) and speed(large)
    uint16_t relinearize_skip = 10u;     ///< only relinearize any variables every relinearize_skip,
                                         ///< it will influence the accuracy(small) and speed(large)
};

/**
 * @brief This struct defines state of smoother.
 *
 */
struct SmootherState
{
    FactorGraph factor_graph;             ///< factor graph which contains factors and values.
    uint8_t     iterations         = 0u;  ///< the number of optimizer iterations performed.
    uint8_t     intermediate_steps = 0u;  ///< the number if intermediate steps performed within the optimization.
    Scalar      final_error        = Scalar(0);  ///< final factor graph error

};  // struct SmootherState

/**
 * @brief Fixed lag smoother
 *
 */
class Smoother
{
public:
    using Parameters           = SmootherParameters;
    using ImuPreintegrationPtr = ImuPreintegration::Ptr;
    using Ptr                  = std::shared_ptr<Smoother>;
    using ConstPtr             = std::shared_ptr<const Smoother>;

    /* constructor */
    Smoother() = delete;

    /**
     * @brief construct smoother object
     *
     * @param  params the configuration of smoother
     */
    Smoother(const Parameters params = Parameters());

    /**
     * @brief Destroy the Smoother object
     *
     */
    virtual ~Smoother() noexcept;

    /* movable */
    Smoother(Smoother&& smoother) noexcept;
    Smoother& operator=(Smoother&& smoother) noexcept;

    /* copyable */
    Smoother(const Smoother& smoother);
    Smoother& operator=(const Smoother& smoother);

    /**
     * @brief Add factor graph into smoother.
     *
     * @param factor_graph factor graph which contains factors and values.
     * @return OptionalT<SmootherState> return SmootherState if success, otherwise nonetype.
     */
    OptionalT<SmootherState> Run(const FactorGraph& factor_graph);

    /**
     * @brief get the configuration of smoother
     *
     * @return the configuration of smoother
     */
    Parameters GetParameters() const
    {
        return params_;
    }

    /**
     * @brief Reset smoother state
     *
     */
    void Reset();

    /**
     * @brief Get the Marginal Covariance object
     * @todo if input symbol's valuetype is POSE3, the order of covariance matrix need to be converted before output
     *
     * @param symbol variable symbol
     * @return covariance of variable
     */
    MatrixXType GetMarginalCovariance(const Symbol& symbol) const;

    /**
     * @brief Get the Marginal Covariance object
     * @todo if input symbols include symbol's valuetype POSE3, we need to find the number of rows of X and convert the
     * corresponding covariance
     *
     * @param symbols variable symbols vector
     * @return MatrixXType covariance of covariance
     */
    MatrixXType GetMarginalCovariance(std::vector<Symbol> const& symbols) const;

private:
    Parameters params_;  ///< parameters of fixed lag smoother

    class Implement;  ///< PIMPL (Pointer to Implementation)
    std::unique_ptr<Implement> impl_;

};  // Smoother

/**
 * @}
 *
 */

}  // namespace localization

}  // namespace holo

#endif  // HOLO_LOCALIZATION_BACKEND_SMOOTHER_H_
