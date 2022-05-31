/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file ransac_problem_data_container_adapter.h
 * @brief this class provides unified APIs to for any ransac problem
 * @author jiaxing.zhao, duyanwei
 * @date 2019-09-04
 */

#ifndef HOLO_NUMERICS_RANSAC_PROBLEM_DATA_CONTAINER_ADAPTER_
#define HOLO_NUMERICS_RANSAC_PROBLEM_DATA_CONTAINER_ADAPTER_

#include <vector>

namespace holo
{
/**
 * @addtogroup numerics
 * @{
 */

/**
 * @brief this class defines unified APIs for any type of data container
 *
 * @tparam _SampleType indicates data type, such as Point2T, Point3T etc.
 */
template <typename _SampleType>
class RansacProblemDataContainerAdapterBaseT
{
public:
    using SampleType = _SampleType;

    /**
     * @brief default constructor
     */
    RansacProblemDataContainerAdapterBaseT()
    {
    }

    /**
     * @brief destructor
     *
     */
    virtual ~RansacProblemDataContainerAdapterBaseT() noexcept
    {
    }

    /**
     * @brief Access of correspondences, retrieve a specified sample
     *
     * @param index The serialized index of sample
     * @return the sample
     */
    virtual SampleType const& GetSample(uint64_t const index) const = 0;

    /**
     * @brief get sample size
     *
     * @return size of samples
     */
    virtual uint64_t GetSampleSize() const = 0;

};  // RansacProblemDataContainerAdapterBaseT

/**
 * @brief data container of std::vector
 *
 * @tparam SampleType
 */
template <typename _SampleType>
class RansacProblemDataContainerAdapterStdVectorT : public RansacProblemDataContainerAdapterBaseT<_SampleType>
{
public:
    using Base       = RansacProblemDataContainerAdapterBaseT<_SampleType>;
    using SampleType = typename Base::SampleType;

    /**
     * @brief disable default constructor
     */
    RansacProblemDataContainerAdapterStdVectorT() = delete;

    /**
     * @brief constructor with data
     *
     * @param input data
     */
    explicit RansacProblemDataContainerAdapterStdVectorT(std::vector<SampleType> const& input) : data_(input)
    {
    }

    /**
     * @brief move constructor with data
     *
     * @param input data
     */
    explicit RansacProblemDataContainerAdapterStdVectorT(std::vector<SampleType>&& input) : data_(std::move(input))
    {
    }

    /**
     * @brief destructor
     *
     */
    virtual ~RansacProblemDataContainerAdapterStdVectorT() noexcept
    {
    }

    /**
     * @brief Access of correspondences, retrieve a specified sample
     *
     * @param index The serialized index of sample
     * @return the sample
     */
    virtual SampleType const& GetSample(uint64_t const index) const override
    {
        if (index >= data_.size())
        {
            // LOG(ERROR) << "Get sample of index overflow !";
            throw std::runtime_error("index overflow");
        }
        return data_[index];
    }

    /**
     * @brief get sample size
     *
     * @return size of samples
     */
    virtual uint64_t GetSampleSize() const override
    {
        return static_cast<uint64_t>(data_.size());
    }

private:
    /**
     * @brief internal data
     *
     */
    std::vector<SampleType> data_;

};  // RansacProblemDataContainerAdapterStdVectorT

/**
 * @}
 *
 */

}  // namespace holo

#endif  // HOLO_NUMERICS_RANSAC_PROBLEM_DATA_CONTAINER_ADAPTER_
