/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file results.h
 * @brief Definition for MatchingResults.
 * @author wanghaiyang(wanghaiyang@holomaitc.com)
 * @date "2020-03-22"
 */

#ifndef HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_RESULTS_H_
#define HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_RESULTS_H_

#include <holo/map/common/common_type_define.h>
#include <holo/map/common/utility.h>
#include <holo/map/service/client/matcher/result.h>

namespace holo
{
namespace map
{
namespace service
{
namespace client
{
namespace matcher
{

/**
 * @addtogroup matcher
 * @{
 *
 */

/**
 * @brief A container of all the available results.
 */
class MatchingResults
{
public:
    /// Redefine type for vector.
    using VectorType = std::vector<MatchingResult>;
    /// Redefine smart pointer for MatchingResults.
    using SPtrType = std::shared_ptr<MatchingResults>;
    /// Redefine smart const pointer for MatchingResults.
    using CSPtrType = std::shared_ptr<MatchingResults const>;

    /// The default capacity of matching results.
    static std::size_t const DEFAULT_CAPACITY;

    /**
     * @brief Format a MatchingResult to a JSON string.
     * 
     * @param[in] r An object of MatchingResult.
     * @return A JSON string.
     */
    static std::string FormatToString(MatchingResults const& r);

    /**
     * @brief Constructor.
     * 
     * @return Nothing.
     */
    MatchingResults() = default;

    /**
     * @brief Destructor.
     * 
     * @return Nothing.
     */
    ~MatchingResults() = default;
    
    /**
     * @brief Constructor.
     * 
     * @param[in] c The capacity of result buffer.
     * @return Nothing.
     */
    explicit MatchingResults(std::size_t const c) :
        capacity_(c)
    {
        this->results_.reserve(c);
    }

    /**
     * @brief Copy constructor.
     * 
     * @param[in] r Another object of MatchingResults.
     * @return Nothing.
     */
    MatchingResults(MatchingResults const& r) :
        capacity_(r.capacity_),
        results_(r.results_)
    {
    }

    /**
     * @brief Move constructor.
     * 
     * @param[in] r Another object of MatchingResults.
     * @return Nothing.
     */
    MatchingResults(MatchingResults&& r)
    {
        this->capacity_ = r.capacity_;
        this->results_ = std::move(r.results_);
    }

    /**
     * @brief Copy assignment.
     * 
     * @param[in] r Another object of MatchingResults.
     * @return *this.
     */
    MatchingResults& operator = (MatchingResults const& r)
    {
        if (this != &r)
        {
            this->capacity_ = r.capacity_;
            this->results_  = r.results_;
        }
        return *this;
    }

    /**
     * @brief Move assignment.
     * 
     * @param[in] r Another object of MatchingResults.
     * @return *this.
     */
    MatchingResults& operator = (MatchingResults&& r)
    {
        if (this != &r)
        {
            this->capacity_ = r.capacity_;
            this->results_  = std::move(r.results_);
        }
        return *this;
    }

    /**
     * @brief Whether of not are two objects equal.
     * 
     * @param[in] r Another object of MatchingResults.
     * @return true: Equal, false: otherwise.
     */
    bool operator == (MatchingResults const& r) const noexcept
    {
        bool ok = (this->capacity_ == r.capacity_);
        
        std::size_t const count1 = this->results_.size();
        std::size_t const count2 = r.results_.size();
        
        ok = ok && (count1 == count2);
        
        for (std::size_t i = 0; i < count1 && ok; ++i)
        {
            ok = this->results_[i] == r.results_[i];
        }
        
        return ok;
    }

    /**
     * @brief  Whether of not are two objects unequal.
     * 
     * @param[in] r Another object of MatchingResults.
     * @return true: Unequal, false: otherwise.
     */
    bool operator != (MatchingResults const& r) const noexcept
    {
        return !(*this == r);
    }

    /**
     * @brief Clear all the elements in the buffer.
     * 
     * @return Nothing.
     */
    void Clear()
    {
        this->results_.clear();
    }

    /**
     * @brief Whether or not one of the results is matched.
     * 
     * @return true: One of the results is matched.
     *         false: None of result is matched.
     */
    bool IsMatched() const
    {
        bool rtn = false;
        std::size_t const count = this->results_.size();
        for (std::size_t i = 0; i < count && !rtn; ++i)
        {
            rtn = this->results_[i].IsMatched();
        }
        return rtn;
    }

    /**
     * @brief Whether or not the container is available.
     * 
     * @return true: The container is available.
     *         false: The container is not available.
     */
    bool IsAvailable() const noexcept
    {
        return !this->results_.empty();
    }

    /**
     * @brief Whether or not the results are overlapped.
     * 
     * @return true: Overlapped, false: Otherwise.
     */
    bool IsOverlapped() const noexcept;

    /**
     * @brief Access the size of the container.
     * 
     * @return The size of the container.
     */
    std::size_t GetSize() const noexcept
    {
        return this->results_.size();
    }

    /**
     * @brief Access the capacity of the container.
     * 
     * @return The capacity of the container.
     */
    std::size_t GetCapacity() const noexcept
    {
        return this->capacity_;
    }

    /**
     * @brief Get all the results of this container.
     * 
     * @return All the const results.
     */
    VectorType const& GetResults() const noexcept
    {
        return this->results_;
    }

    /**
     * @brief Assign new results to the container.
     * 
     * @note If the size of container is more than the capacity, the worst result
     *       will be removed if all results are sorted or the last result will be
     *       removed.
     * @param[in] rs Another objects of MatchingResult.
     * @param[in] sort Sort the results if true.
     * @return Nothing.
     */
    void SetResults(MatchingResults::VectorType const& rs, bool const sort = true);

    /**
     * @brief Assign new results to the container.
     * 
     * @note If the size of container is more than the capacity, the worst result
     *       will be removed if all results are sorted or the last result will be
     *       removed.
     * @param[in] rs Another objects of MatchingResult.
     * @param[in] sort Sort the results if true.
     * @return Nothing.
     */
    void SetResults(MatchingResults::VectorType&& rs, bool const sort = true);

    /**
     * @brief Append a new result to the container.
     * 
     * @note If the size of container is more than the capacity, the worst result
     *       will be removed if all results are sorted or the last result will be
     *       removed.
     * @param[in] r Another objects of MatchingResult.
     * @param[in] sort Sort the results if true.
     * @return Nothing.
     */
    void AddResult(MatchingResult const& r, bool const sort = true);

    /**
     * @brief Append a new result to the container.
     * 
     * @note If the size of container is more than the capacity, the worst result
     *       will be removed if all results are sorted or the last result will be
     *       removed.
     * @param[in] r Another objects of MatchingResult.
     * @param[in] sort Sort the results if true.
     * @return Nothing.
     */
    void AddResult(MatchingResult&& r, bool const sort = true);

    /**
     * @brief Append results to the container.
     * 
     * @note If the size of container is more than the capacity, the worst result
     *       will be removed if all results are sorted or the last result will be
     *       removed.
     * @param[in] rs Another objects of MatchingResult.
     * @param[in] sort Sort the results if true.
     * @return Nothing.
     */
    void AddResults(MatchingResults::VectorType const& rs, bool const sort = true);

    /**
     * @brief Sort all the results, and the best element wil be set at the front.
     * 
     * @note This function should be used after all the AddResult/s done.
     * @return Nothing.
     */
    void SortResults();

private:
    /**
     * @brief Update history status for all the matching results.
     * 
     * @param[in] r true: The history is reliable;
     *              false: The history is non-reliable.
     */
    void updateResultsHistoryStatus(holo::bool_t const r);

private:
    std::size_t capacity_ = DEFAULT_CAPACITY;   ///< The capacity of the container.
    MatchingResults::VectorType results_;      ///< A container of all the available results.

    friend class MapMatcher;
    
}; ///< End of class MatchingResults.

/**
 * @}
 *
 */

} ///< namespace matcher
} ///< namespace client
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_FEATURE_NAVIGATOR_MATCHER_RESULTS_H_ */

