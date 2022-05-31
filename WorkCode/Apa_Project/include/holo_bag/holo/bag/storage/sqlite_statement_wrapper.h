/**
 * @file sqlite_statement_wrapper.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the sqlite statement wrapper
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_STORAGE_SQLITE_STATEMENT_WRAPPER_HPP_
#define _HOLOBAG_STORAGE_SQLITE_STATEMENT_WRAPPER_HPP_

#include <holo/bag/storage/sqlite_exception.h>
#include <holo/container/vector.h>
#include <sqlite3.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>

namespace holo
{
namespace bag
{
class SqliteStatementWrapper : public std::enable_shared_from_this<SqliteStatementWrapper>
{
public:
    using DataSequenceType = holo::container::Vector<uint8_t, std::numeric_limits<size_t>::max()>;

    SqliteStatementWrapper(sqlite3* database, const std::string& query);
    SqliteStatementWrapper(const SqliteStatementWrapper&) = delete;
    SqliteStatementWrapper& operator=(const SqliteStatementWrapper&) = delete;
    ~SqliteStatementWrapper();

    template <typename... Columns>
    class QueryResult
    {
    public:
        using RowType = std::tuple<Columns...>;
        class Iterator : public std::iterator<std::input_iterator_tag, RowType>
        {
        public:
            static int const POSITION_END = -1;
            Iterator(std::shared_ptr<SqliteStatementWrapper> statement, int position)
              : statement_(statement), next_row_idx_(position), cached_row_idx_(POSITION_END - 1)
            {
                if (next_row_idx_ != POSITION_END)
                {
                    if (statement_->Step())
                    {
                        ++next_row_idx_;
                    }
                    else
                    {
                        next_row_idx_ = POSITION_END;
                    }
                }
            }

            Iterator(const Iterator&) = delete;
            Iterator& operator=(const Iterator&) = delete;

            Iterator(Iterator&&) = default;
            Iterator& operator=(Iterator&&) = default;

            Iterator& operator++()
            {
                if (next_row_idx_ != POSITION_END)
                {
                    if (statement_->Step())
                    {
                        ++next_row_idx_;
                    }
                    else
                    {
                        next_row_idx_ = POSITION_END;
                    }
                    return *this;
                }
                else
                {
                    throw SqliteException("Cannot increment result iterator beyond result set!");
                }
            }
            Iterator operator++(int)
            {
                auto old_value = *this;
                ++(*this);
                return old_value;
            }

            RowType operator*() const
            {
                if (next_row_idx_ == POSITION_END)
                {
                    throw SqliteException("Cannot dereference iterator at end of result set!");
                }
                if (isRowCacheValid())
                {
                    return row_cache_;
                }
                RowType row{};
                obtainRowValues(row);
                return row;
            }

            bool operator==(const Iterator& other) const
            {
                return statement_ == other.statement_ && next_row_idx_ == other.next_row_idx_;
            }

            bool operator!=(const Iterator& other) const
            {
                return !(*this == other);
            }

        private:
            template <typename Indices = std::index_sequence_for<Columns...>>
            void obtainRowValues(RowType& row) const
            {
                obtainRowValuesImpl(row, Indices{});
                row_cache_      = row;
                cached_row_idx_ = next_row_idx_ - 1;
            }

            template <size_t I, size_t... Is, typename RemainingIndices = std::index_sequence<Is...>>
            void obtainRowValuesImpl(RowType& row, std::index_sequence<I, Is...>) const
            {
                statement_->obtainColumnValue(I, std::get<I>(row));
                obtainRowValuesImpl(row, RemainingIndices{});
            }
            void obtainRowValuesImpl(RowType&, std::index_sequence<>) const
            {
            }  // end of recursion

            bool isRowCacheValid() const
            {
                return cached_row_idx_ == next_row_idx_ - 1;
            }

            std::shared_ptr<SqliteStatementWrapper> statement_;
            int                                     next_row_idx_;
            mutable int                             cached_row_idx_;
            mutable RowType                         row_cache_;
        };

        explicit QueryResult(std::shared_ptr<SqliteStatementWrapper> statement)
          : statement_(statement), is_already_accessed_(false)
        {
        }

        Iterator begin()
        {
            tryAccessData();
            return Iterator(statement_, 0);
        }

        Iterator end()
        {
            return Iterator(statement_, Iterator::POSITION_END);
        }

        RowType get_single_line()
        {
            return *begin();
        }

    private:
        void tryAccessData()
        {
            if (is_already_accessed_)
            {
                throw SqliteException("Only one iterator per query result is supported!");
            }
            is_already_accessed_ = true;
        }

        std::shared_ptr<SqliteStatementWrapper> statement_;
        bool                                    is_already_accessed_;
    };

    std::shared_ptr<SqliteStatementWrapper> ExecuteAndReset();
    template <typename... Columns>
    QueryResult<Columns...> ExecuteQuery();

    template <typename T1, typename T2, typename... Params>
    std::shared_ptr<SqliteStatementWrapper> Bind(T1 value1, T2 value2, Params... values);
    std::shared_ptr<SqliteStatementWrapper> Bind(int value);
    std::shared_ptr<SqliteStatementWrapper> Bind(int64_t value);
    std::shared_ptr<SqliteStatementWrapper> Bind(double value);
    std::shared_ptr<SqliteStatementWrapper> Bind(const std::string& value);
    std::shared_ptr<SqliteStatementWrapper> Bind(const DataSequenceType& value);

    std::shared_ptr<SqliteStatementWrapper> Reset();
    bool Step();

private:
    bool isQueryOk(int return_code);

    void obtainColumnValue(size_t index, int& value) const;
    void obtainColumnValue(size_t index, int64_t& value) const;
    void obtainColumnValue(size_t index, double& value) const;
    void obtainColumnValue(size_t index, std::string& value) const;
    void obtainColumnValue(size_t index, DataSequenceType& value) const;

    template <typename T>
    void checkAndReportBindError(int return_code, T value);
    void checkAndReportBindError(int return_code);

    sqlite3_stmt* statement_;
    int           last_bound_parameter_index_;
};

template <typename T1, typename T2, typename... Params>
inline std::shared_ptr<SqliteStatementWrapper> SqliteStatementWrapper::Bind(T1 value1, T2 value2, Params... values)
{
    Bind(value1);
    return Bind(value2, values...);
}

template <>
inline void SqliteStatementWrapper::checkAndReportBindError(int return_code, std::string value)
{
    if (return_code != SQLITE_OK)
    {
        throw SqliteException("SQLite error when binding parameter " + std::to_string(last_bound_parameter_index_) +
                              " to value '" + value + "'. Return code: " + std::to_string(return_code));
    }
}

template <typename T>
inline void SqliteStatementWrapper::checkAndReportBindError(int return_code, T value)
{
    checkAndReportBindError(return_code, std::to_string(value));
}

template <typename... Columns>
inline SqliteStatementWrapper::QueryResult<Columns...> SqliteStatementWrapper::ExecuteQuery()
{
    return QueryResult<Columns...>(shared_from_this());
}

using SqliteStatement = std::shared_ptr<SqliteStatementWrapper>;

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_STORAGE_SQLITE_STATEMENT_WRAPPER_HPP_
