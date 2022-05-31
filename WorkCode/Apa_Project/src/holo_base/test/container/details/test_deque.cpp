/**
 * @brief unit test for Deque class
 * @author zhangjiannan@holomatic.com
 * @date Sep 25, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <iostream>
#include <vector>
#include <cstring>
#include <gtest/gtest.h>
#include <holo/core/types.h>
#include <holo/container/details/deque.h>

using holo::container::details::Deque;

/**
 * @brief 
 */
class Foo
{
public:
    Foo(): data(new int)
    {
        //std::cout << "Default constructor Foo!" << std::endl;
        *data = 0;
    }

    explicit Foo(int value): data(new int(value))
    {
        //std::cout << "Constructor Foo with one argument!" << std::endl;
    }

    Foo(const Foo& other): data(new int)
    {
        //std::cout << "Copy constructor Foo!" << std::endl;
        *data = *(other.data);
    }

    Foo(Foo&& other): data(other.data)
    {
        //std::cout << "Rvalue copy constructor Foo!" << std::endl;
        other.data = nullptr;
    }

    Foo& operator=(const Foo& other)
    {
        //std::cout << "Assign operator Foo!" << std::endl;
        if(this == &other)
        {
            return *this;
        }
        else
        {
            if(data == nullptr)
            {
                data = new int;
            }
            *data = *(other.data);
            return *this;
        }
    }

    Foo& operator=(Foo&& other)
    {
        //std::cout << "Assign operator Foo!" << std::endl;
        if(this == &other)
        {
            return *this;
        }
        else
        {
            if (data != nullptr)
            {
                delete data;
            }
            data = other.data;
            other.data = nullptr;
            return *this;
        }
    }

    holo::bool_t operator== (const Foo& other) const
    {
        return *(this->data) == *(other.data);
    }

    holo::bool_t operator<(const Foo& other) const
    {
        return *(this->data) < *(other.data);
    }

    ~Foo()
    {
        //std::cout << "destructor Foo!" << std::endl;
        if(data != nullptr)
        {
            delete data;
        }
    }

    const holo::int32_t& GetData() const
    {
        return *data;
    }

private:
    holo::int32_t* data;
};

/**
 * @brief Test DequeConstructors;
 *
 */
TEST(Deque, Constructor)
{
    /// Test Deque()
    {
        Deque<Foo, 10> container;
        ASSERT_EQ(0, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_TRUE(container.empty());
    }

    /// Test Deque(size_type n)
    {
        // zero
        {
            Deque<Foo, 10> container(0);
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            Deque<Foo, 10> container(3);
            ASSERT_EQ(3, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo() == container[i]);
            }
        }
        // max size
        {
            Deque<Foo, 10> container(10);
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo() == container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container(11);
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }

    /// Test Deque(size_type n, const value_type& value)
    {
        // zero
        {
            Deque<Foo, 10> container(0, Foo(1));
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal casae
        {
            Deque<Foo, 10> container(3, Foo(1));
            ASSERT_EQ(3, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(1) == container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container(10, Foo(1));
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(1) == container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container(11, Foo(1));
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }

    /// Test template<typename InputIt> Deque(InputIt first, InputIt last)
    {
        // Test raw pointer
        holo::int32_t test_int_array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Deque<holo::int32_t, 10> int_container(&test_int_array[2], &test_int_array[8]);
        ASSERT_EQ(6, int_container.size());
        ASSERT_EQ(10, int_container.max_size());
        for(std::size_t i = 0; i < int_container.size(); ++i)
        {
            ASSERT_TRUE(2 + (holo::int32_t)i == int_container[i]);
        }

        // if this successfully compile, means 
        // template<typename InputIt = int> Deque(InputIt first, InputIt last) 
        // is not instantiated. 
        // There will be no ambiguous between this function and Deque(size_type n, const value_type& value);
        Deque<holo::int32_t, 10> int_container2(3, 10);

        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        // zero
        {
            Deque<Foo, 10> container(test_vector.begin(), test_vector.begin());
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            Deque<Foo, 10> container(test_vector.begin() + 2, test_vector.begin() + 8);
            ASSERT_EQ(6, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(2 + i) == container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container(test_vector.begin(), test_vector.begin() + 10);
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(i) == container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container(test_vector.begin(), test_vector.end());
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }

    /// Test Deque(const Deque& other)
    {
        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        Deque<Foo, 10> container_other(test_vector.begin() + 2, test_vector.begin() + 8);
        Deque<Foo, 10> container(container_other);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        for(std::size_t i = 0; i < container.size(); ++i)
        {
            ASSERT_TRUE(Foo(2 + i) == container[i]);
        }
    }

    /// Test Deque(Deque&& other)
    {
        Deque<Foo, 10> container_other = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        const holo::int32_t* origin_ptr = &(container_other[0].GetData());
        Deque<Foo, 10> container(std::move(container_other));
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        Deque<Foo, 10> tmp{Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        ASSERT_EQ(container, tmp);
        const holo::int32_t* ptr = &(container[0].GetData());
        ASSERT_EQ(ptr, origin_ptr);
    }

    /// Test Deque(std::initializer_list<value_type> ilist)
    {
        // zero
        {
            Deque<Foo, 10> container({});
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            Deque<Foo, 10> container( 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5)});
            ASSERT_EQ(6, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i), container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container( 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i), container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container( 
                    {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)});
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }
}

TEST(Deque, OperatorAssignment)
{
    /// Test Deque& operator= (const Deque& other);
    {
        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        Deque<Foo, 10> container_other(test_vector.begin() + 2, test_vector.begin() + 8);
        Deque<Foo, 10> container = container_other;
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        for(std::size_t i = 0; i < container.size(); ++i)
        {
            ASSERT_TRUE(Foo(2 + i) == container[i]);
        }
    }

    /// Test Deque& operator= (Deque&& other);
    {
        Deque<Foo, 10> container_other = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        const holo::int32_t* origin_ptr = &(container_other[0].GetData());
        Deque<Foo, 10> container = std::move(container_other);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        Deque<Foo, 10> tmp{Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        ASSERT_EQ(container, tmp);
        const holo::int32_t* ptr = &(container[0].GetData());
        ASSERT_EQ(ptr, origin_ptr);
    }

    /// Test Deque& operator= (std::initializer_list<value_type> ilist);
    {
        // zero
        {
            Deque<Foo, 10> container = {};
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            Deque<Foo, 10> container = 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5)};
            ASSERT_EQ(6, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i), container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container = 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)};
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i), container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container = 
                    {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }
}


TEST(Deque, OperatorAssignmentException)
{
    Deque<Foo, 2> container = {Foo(0), Foo(1)};
    try
    {
        container = {Foo(0), Foo(1), Foo(2)};
    }
    catch(...)
    {
    }
}

/**
 * @brief Test reference at( size_type pos ); const_reference at( size_type pos ) const;
 */
TEST(Deque, Method_at)
{
    Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    for(holo::uint32_t i = 0; i < container.size(); ++i)
    {
        ASSERT_EQ(Foo(i), container.at(i));
    }
    try 
    {
        container.at(container.size());
        FAIL() << "Expect throw holo::exception::OutOfRangeException";
    }
    catch(holo::exception::OutOfRangeException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected excception";
    }

    const Deque<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    for(holo::uint32_t i = 0; i < const_container.size(); ++i)
    {
        ASSERT_EQ(Foo(i), const_container.at(i));
    }
    try 
    {
        const_container.at(const_container.size());
        FAIL() << "Expect throw holo::exception::OutOfRangeException";
    }
    catch(holo::exception::OutOfRangeException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected excception";
    }
}

/**
 * @brief Test 
 * reference operator[]( size_type pos ) noexcept;
 * const_reference operator[]( size_type pos ) const noexcept;
 */
TEST(Deque, OperatorSquareBrackets)
{
    Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    for(holo::uint32_t i = 0; i < container.size(); ++i)
    {
        ASSERT_EQ(Foo(i), container[i]);
    }
    container[container.size()];

    const Deque<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    for(holo::uint32_t i = 0; i < const_container.size(); ++i)
    {
        ASSERT_EQ(Foo(i), const_container[i]);
    }
    const_container[const_container.size()];
}

TEST(Deque, Method_front)
{
    Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), container.front());
    container.pop_front();
    ASSERT_EQ(Foo(1), container.front());
    container.pop_front();
    ASSERT_EQ(Foo(2), container.front());

    const Deque<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), const_container.front());

    Deque<Foo, 10> empty_container;
    try
    {
        empty_container.front();
        FAIL() << "Expect throw holo::exception::OutOfRangeException";
    }
    catch(holo::exception::OutOfRangeException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception";
    }

    const Deque<Foo, 10> const_empty_container;
    try
    {
        const_empty_container.front();
        FAIL() << "Expect throw holo::exception::OutOfRangeException";
    }
    catch(holo::exception::OutOfRangeException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception";
    }
}

TEST(Deque, Method_back)
{
    Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(2), container.back());
    container.pop_back();
    ASSERT_EQ(Foo(1), container.back());
    container.pop_back();
    ASSERT_EQ(Foo(0), container.back());

    const Deque<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(2), const_container.back());

    Deque<Foo, 10> empty_container;
    try
    {
        empty_container.back();
        FAIL() << "Expect throw holo::exception::OutOfRangeException";
    }
    catch(holo::exception::OutOfRangeException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception";
    }

    const Deque<Foo, 10> const_empty_container;
    try
    {
        const_empty_container.back();
        FAIL() << "Expect throw holo::exception::OutOfRangeException";
    }
    catch(holo::exception::OutOfRangeException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception";
    }
}

TEST(Deque, Method_begin)
{
    Deque<Foo, 10> container = {Foo(0), Foo(1), Foo(2)};
    const Deque<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});

    ASSERT_EQ(Foo(0), *container.begin());
    container.pop_front();
    ASSERT_EQ(Foo(1), *container.begin());
    container.pop_front();
    ASSERT_EQ(Foo(2), *container.begin());
    container.pop_front();
    ASSERT_EQ(container.end(), container.begin());

    ASSERT_EQ(Foo(0), *const_container.begin());

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(Foo(0), *container.cbegin());
    container.pop_front();
    ASSERT_EQ(Foo(1), *container.cbegin());
    container.pop_front();
    ASSERT_EQ(Foo(2), *container.cbegin());
    container.pop_front();
    ASSERT_EQ(container.cend(), container.cbegin());
    ASSERT_EQ(container.end(), container.cbegin());
    ASSERT_EQ(container.cend(), container.begin());
    ASSERT_EQ(container.cbegin(), container.cend());
    ASSERT_EQ(container.begin(), container.cend());
    ASSERT_EQ(container.cbegin(), container.end());

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(Foo(2), *container.rbegin());
    container.pop_back();
    ASSERT_EQ(Foo(1), *container.rbegin());
    container.pop_back();
    ASSERT_EQ(Foo(0), *container.rbegin());
    container.pop_back();
    ASSERT_EQ(container.rend(), container.rbegin());

    ASSERT_EQ(Foo(2), *const_container.rbegin());

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(Foo(2), *container.crbegin());
    container.pop_back();
    ASSERT_EQ(Foo(1), *container.crbegin());
    container.pop_back();
    ASSERT_EQ(Foo(0), *container.crbegin());
    container.pop_back();
    ASSERT_EQ(container.crend(), container.crbegin());
    ASSERT_EQ(container.rend(), container.crbegin());
    ASSERT_EQ(container.crend(), container.rbegin());
    ASSERT_EQ(container.crbegin(), container.crend());
    ASSERT_EQ(container.rbegin(), container.crend());
    ASSERT_EQ(container.crbegin(), container.rend());
}

TEST(Deque, Method_end)
{
    Deque<Foo, 10> container = {Foo(0), Foo(1), Foo(2)};
    const Deque<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});

    ASSERT_EQ(Foo(2), *(container.end() - 1));
    container.pop_back();
    ASSERT_EQ(Foo(1), *(container.end() - 1));
    container.pop_back();
    ASSERT_EQ(Foo(0), *(container.end() - 1));
    container.pop_back();
    ASSERT_EQ(container.end(), container.begin());

    ASSERT_EQ(Foo(2), *(const_container.end() - 1));

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(Foo(2), *(container.cend() - 1));
    container.pop_back();
    ASSERT_EQ(Foo(1), *(container.cend() - 1));
    container.pop_back();
    ASSERT_EQ(Foo(0), *(container.cend() - 1));
    container.pop_back();
    ASSERT_EQ(container.cend(), container.cbegin());
    ASSERT_EQ(container.end(), container.cbegin());
    ASSERT_EQ(container.cend(), container.begin());
    ASSERT_EQ(container.cbegin(), container.cend());
    ASSERT_EQ(container.begin(), container.cend());
    ASSERT_EQ(container.cbegin(), container.end());

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    container.pop_front();
    ASSERT_EQ(Foo(1), *(container.rend() - 1));
    container.pop_front();
    ASSERT_EQ(Foo(2), *(container.rend() - 1));
    container.pop_front();
    ASSERT_EQ(container.rend(), container.rend());

    ASSERT_EQ(Foo(0), *(const_container.rend() - 1));

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(Foo(0), *(container.crend() - 1));
    container.pop_front();
    ASSERT_EQ(Foo(1), *(container.crend() - 1));
    container.pop_front();
    ASSERT_EQ(Foo(2), *(container.crend() - 1));
    container.pop_front();
    ASSERT_EQ(container.crend(), container.crbegin());
    ASSERT_EQ(container.rend(), container.crbegin());
    ASSERT_EQ(container.crend(), container.rbegin());
    ASSERT_EQ(container.crbegin(), container.crend());
    ASSERT_EQ(container.rbegin(), container.crend());
    ASSERT_EQ(container.crbegin(), container.rend());
}

TEST(Deque, Method_empty_size_max_size_resize_shrink_to_fit)
{
    Deque<Foo, 10> container;
    ASSERT_EQ(0, container.size());
    ASSERT_TRUE(container.empty());
    ASSERT_EQ(10, container.max_size());

    container = {Foo(0), Foo(1), Foo(2)};
    ASSERT_EQ(3, container.size());
    ASSERT_FALSE(container.empty());
    ASSERT_EQ(10, container.max_size());

    container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)};
    ASSERT_EQ(10, container.size());
    ASSERT_FALSE(container.empty());
    ASSERT_EQ(10, container.max_size());

    try
    {
        container.resize(3);
    }
    catch(...)
    {
        FAIL() << "Unexpected exception";
    }

    try
    {
        container.resize(20);
        FAIL() << "Expect throw holo::exception::BadAllocException";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Unexpected exception";
    }

    container.shrink_to_fit();
}

TEST(Deque, Method_assign)
{
    /// Test void assign(size_type n, const value_type& value)
    {
        // zero
        {
            Deque<Foo, 10> container;
            container.assign(0, Foo(1));
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal casae
        {
            Deque<Foo, 10> container;
            container.assign(3, Foo(1));
            ASSERT_EQ(3, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(1) == container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container;
            container.assign(10, Foo(1));
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(1) == container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container;
                container.assign(11, Foo(1));
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }

    /// Test template<typename InputIt> void assign(InputIt first, InputIt last)
    {
        // Test raw pointer
        holo::int32_t test_int_array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        Deque<holo::int32_t, 10> int_container;
        int_container.assign(&test_int_array[2], &test_int_array[8]);
        ASSERT_EQ(6, int_container.size());
        ASSERT_EQ(10, int_container.max_size());
        for(std::size_t i = 0; i < int_container.size(); ++i)
        {
            ASSERT_TRUE(2 + (holo::int32_t)i == int_container[i]);
        }

        // if this successfully compile, means 
        // template<typename InputIt = int> void assign(InputIt first, InputIt last) 
        // is not instantiated. 
        // There will be no ambiguous between this function and Deque(size_type n, const value_type& value);
        Deque<holo::int32_t, 10> int_container2;
        int_container2.assign(3, 10);

        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        // zero
        {
            Deque<Foo, 10> container;
            container.assign(test_vector.begin(), test_vector.begin());
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            Deque<Foo, 10> container;
            container.assign(test_vector.begin() + 2, test_vector.begin() + 8);
            ASSERT_EQ(6, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(2 + i) == container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container;
            container.assign(test_vector.begin(), test_vector.begin() + 10);
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(i) == container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container;
                container.assign(test_vector.begin(), test_vector.end());
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }

    /// Test Deque(std::initializer_list<value_type> ilist)
    {
        // zero
        {
            Deque<Foo, 10> container;
            container.assign({});
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            Deque<Foo, 10> container; 
            container.assign( 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5)});
            ASSERT_EQ(6, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i), container[i]);
            }
        }
        // max_size
        {
            Deque<Foo, 10> container;
            container.assign( 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i), container[i]);
            }
        }
        // overflow
        {
            try
            {
                Deque<Foo, 10> container;
                container.assign( 
                    {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)});
                FAIL() << "Expect throw holo::exception::BadAllocException";
            }
            catch(holo::exception::BadAllocException& e)
            {
            }
            catch(...)
            {
                FAIL() << "Catch unexpected exception";
            }
        }
    }
}

TEST(Deque, Method_clear)
{
    Deque<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
    ASSERT_EQ(10, container.size());
    ASSERT_EQ(10, container.max_size());
    ASSERT_FALSE(container.empty());

    container.clear();
    ASSERT_EQ(0, container.size());
    ASSERT_EQ(10, container.max_size());
    ASSERT_TRUE(container.empty());
}

/**
 * @brief Test insert
 */
TEST(Deque, Method_insert_lvalue)
{
    // Test iterator insert( const_iterator pos, const value_type& value );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
        Deque<Foo, 10> expected_container({Foo(-1), Foo(0), Foo(1), Foo(2)});
        Deque<Foo, 10>::iterator it;
        Deque<Foo, 10>::reverse_iterator rit;

        // insert front
        Foo value(-1);
        it = container.insert(container.begin(), value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        value = Foo(3);
        value = Foo(3);
        value = Foo(3);
        value = Foo(3);
        it = container.insert(container.rbegin().base(), value);
        ASSERT_EQ(Foo(3), *it);
        ASSERT_EQ(Foo(3), *container.rbegin());
        ASSERT_EQ(Foo(3), *(container.end() - 1));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle
        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(1), Foo(2), Foo(3)};
        it = std::find(container.begin(), container.end(), Foo(0));
        value = Foo(11);
        it = container.insert(it, value);
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3)};
        rit = std::find(container.rbegin(), container.rend(), Foo(0));
        value = Foo(12);
        it = container.insert(rit.base(), value);
        ASSERT_EQ(Foo(12), *it);
        ASSERT_EQ(7, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4)};
        value = Foo(4);
        it = container.insert(container.end(), value);
        ASSERT_EQ(Foo(4), *it);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(8, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-2), Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4)};
        value = Foo(-2);
        it = container.insert(container.rend().base(), value);
        ASSERT_EQ(Foo(-2), *it);
        ASSERT_EQ(Foo(-2), *(container.rend() - 1));
        ASSERT_EQ(Foo(-2), *container.begin());
        ASSERT_EQ(9, container.size());
        ASSERT_EQ(expected_container, container);

        //overflow
        value = Foo(100);
        expected_container = {Foo(-2), Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4), Foo(100)};
        it = container.insert(container.end(), value);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
        
        try
        {
            it = container.insert(container.end(), value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
    }
}

TEST(Deque, Method_insert_rvalue)
{
    // Test iterator insert( const_iterator pos, const value_type&& value );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
        Deque<Foo, 10> expected_container({Foo(-1), Foo(0), Foo(1), Foo(2)});
        Deque<Foo, 10>::iterator it;
        Deque<Foo, 10>::reverse_iterator rit;

        // insert front
        Foo value(-1);
        it = container.insert(container.begin(), std::move(value));
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        it = container.insert(container.rbegin().base(), Foo(3));
        ASSERT_EQ(Foo(3), *it);
        ASSERT_EQ(Foo(3), *container.rbegin());
        ASSERT_EQ(Foo(3), *(container.end() - 1));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle
        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(1), Foo(2), Foo(3)};
        it = std::find(container.begin(), container.end(), Foo(0));
        value = Foo(11);
        it = container.insert(it, std::move(value));
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3)};
        rit = std::find(container.rbegin(), container.rend(), Foo(0));
        it = container.insert(rit.base(), Foo(12));
        ASSERT_EQ(Foo(12), *it);
        ASSERT_EQ(7, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4)};
        it = container.insert(container.end(), Foo(4));
        ASSERT_EQ(Foo(4), *it);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(8, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-2), Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4)};
        value = Foo(-2);
        it = container.insert(container.rend().base(), std::move(value));
        ASSERT_EQ(Foo(-2), *it);
        ASSERT_EQ(Foo(-2), *(container.rend() - 1));
        ASSERT_EQ(Foo(-2), *container.begin());
        ASSERT_EQ(9, container.size());
        ASSERT_EQ(expected_container, container);

        //overflow
        expected_container = {Foo(-2), Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4), Foo(100)};
        it = container.insert(container.end(), Foo(100));
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
        
        try
        {
            it = container.insert(container.end(), Foo(100));
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
    }
}

TEST(Deque, Method_insert_count_value)
{
    // Test iterator insert( const_iterator pos, size_type count, const value_type& value );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        Deque<Foo, 10> container({Foo(0)});
        Deque<Foo, 10> expected_container({Foo(0)});
        Deque<Foo, 10>::iterator it;
        Deque<Foo, 10>::reverse_iterator rit;

        // insert front with 0 element.
        Foo value(-1);
        it = container.insert(container.begin(), 0, value);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *container.begin());
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with 1 element.
        expected_container = {Foo(-1), Foo(0)};
        container = {Foo(0)};
        it = container.insert(container.begin(), 1, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with n elements.
        expected_container = {Foo(-1), Foo(-1), Foo(-1), Foo(0)};
        container = {Foo(0)};
        it = container.insert(container.begin(), 3, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.begin(), 10, value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *container.begin());
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);

        // insert reverse front with 0 element.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        value = Foo(-1);
        it = container.insert(container.rbegin().base(), 0, value);
        ASSERT_EQ(container.end(), it);
        ASSERT_EQ(Foo(0), *container.rbegin());
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse front with 1 element.
        expected_container = {Foo(0), Foo(-1)};
        container = {Foo(0)};
        it = container.insert(container.rbegin().base(), 1, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.rbegin());
        ASSERT_EQ(Foo(-1), *(container.end() - 1));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse front with n elements.
        expected_container = {Foo(0), Foo(-1), Foo(-1), Foo(-1)};
        container = {Foo(0)};
        it = container.insert(container.rbegin().base(), 3, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.rbegin());
        ASSERT_EQ(Foo(-1), *(container.end() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse front overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.rbegin().base(), 10, value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *container.rbegin());
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle with 0 element
        expected_container = {Foo(-1), Foo(0)};
        container = {Foo(-1), Foo(0)};
        it = container.begin() + 1;
        value = Foo(11);
        it = container.insert(it, 0, value);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with 1 element
        expected_container = {Foo(-1), Foo(11), Foo(0)};
        container = {Foo(-1), Foo(0)};
        it = container.begin() + 1;
        value = Foo(11);
        it = container.insert(it, 1, value);
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with n elements
        expected_container = {Foo(-1), Foo(11), Foo(11), Foo(11), Foo(0)};
        container = {Foo(-1), Foo(0)};
        it = container.begin() + 1;
        value = Foo(11);
        it = container.insert(it, 3, value);
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle overflow.
        expected_container = {Foo(-1), Foo(0)};
        container = {Foo(-1), Foo(0)};
        try
        {
            it = container.insert(container.begin() + 1, 9, value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);

        // insert reverse middle with 0 element
        expected_container = {Foo(-1), Foo(0)};
        container = {Foo(-1), Foo(0)};
        rit = container.rbegin() + 1;
        value = Foo(11);
        it = container.insert(rit.base(), 0, value);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse middle with 1 element
        expected_container = {Foo(-1), Foo(11), Foo(0)};
        container = {Foo(-1), Foo(0)};
        rit = container.rbegin() + 1;
        value = Foo(11);
        it = container.insert(rit.base(), 1, value);
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse middle with n elements
        expected_container = {Foo(-1), Foo(11), Foo(11), Foo(11), Foo(0)};
        container = {Foo(-1), Foo(0)};
        rit = container.rbegin() + 1;
        value = Foo(11);
        it = container.insert(rit.base(), 3, value);
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse middle overflow.
        expected_container = {Foo(-1), Foo(0)};
        container = {Foo(-1), Foo(0)};
        try
        {
            rit = container.rbegin() + 1;
            it = container.insert(rit.base(), 9, value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        expected_container = {Foo(0)};
        container = {Foo(0)};
        value = Foo(-1);
        it = container.insert(container.end(), 0, value);
        ASSERT_EQ(container.end(), it);
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(Foo(0), *(container.rbegin()));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 element.
        expected_container = {Foo(0), Foo(-1)};
        container = {Foo(0)};
        it = container.insert(container.end(), 1, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *(container.end() - 1));
        ASSERT_EQ(Foo(-1), *(container.rbegin()));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n elements.
        expected_container = {Foo(0), Foo(-1), Foo(-1), Foo(-1)};
        container = {Foo(0)};
        it = container.insert(container.end(), 3, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *(container.end() - 1));
        ASSERT_EQ(Foo(-1), *(container.rbegin()));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.end(), 10, value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(Foo(0), *(container.rbegin()));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse back
        expected_container = {Foo(0)};
        container = {Foo(0)};
        value = Foo(-1);
        it = container.insert(container.rend().base(), 0, value);
        ASSERT_EQ(container.begin(), it);
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(Foo(0), *(container.begin()));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 element.
        expected_container = {Foo(-1), Foo(0)};
        container = {Foo(0)};
        it = container.insert(container.rend().base(), 1, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(Foo(-1), *(container.begin()));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n elements.
        expected_container = {Foo(-1), Foo(-1), Foo(-1), Foo(0)};
        container = {Foo(0)};
        it = container.insert(container.rend().base(), 3, value);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(Foo(-1), *(container.begin()));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.rend().base(), 10, value);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(Foo(0), *(container.begin()));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
    }
}

TEST(Deque, Method_insert_iterator_range)
{
    // Test iterator insert( const_iterator pos, InputIt first, InputIt last );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        Deque<Foo, 10> insert_container(
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
        Deque<Foo, 10> container({Foo(10), Foo(11)});
        Deque<Foo, 10> expected_container({Foo(10), Foo(11)});
        Deque<Foo, 10>::iterator it;
        Deque<Foo, 10>::reverse_iterator rit;

        // insert front with 0 element.
        it = container.insert(container.begin(), insert_container.begin(), insert_container.begin());
        ASSERT_EQ(Foo(10), *it);
        ASSERT_EQ(Foo(10), *container.begin());
        ASSERT_EQ(Foo(10), *(container.rend() - 1));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with 1 element.
        expected_container = {Foo(0), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.begin(), insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *container.begin());
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with n elements.
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.begin(), insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *container.begin());
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.begin(), insert_container.begin(), insert_container.end());
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *container.begin());
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);

        // insert reverse front with 0 element.
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.rbegin().base(), insert_container.begin(), insert_container.begin());
        ASSERT_EQ(container.end(), it);
        ASSERT_EQ(Foo(11), *container.rbegin());
        ASSERT_EQ(Foo(11), *(container.end() - 1));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse front with 1 element.
        expected_container = {Foo(10), Foo(11), Foo(0)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.rbegin().base(), insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *container.rbegin());
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse front with n elements.
        expected_container = {Foo(10), Foo(11), Foo(0), Foo(1), Foo(2)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.rbegin().base(), insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(2), *container.rbegin());
        ASSERT_EQ(Foo(2), *(container.end() - 1));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse front overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.rbegin().base(), insert_container.begin(), insert_container.end());
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *container.rbegin());
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle with 0 element
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.begin() + 1;
        it = container.insert(it, insert_container.begin(), insert_container.begin());
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with 1 element
        expected_container = {Foo(10), Foo(0), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.begin() + 1;
        it = container.insert(it, insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with n elements
        expected_container = {Foo(10), Foo(0), Foo(1), Foo(2), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.begin() + 1;
        it = container.insert(it, insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle overflow.
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        try
        {
            it = container.insert(container.begin() + 1, insert_container.begin(), insert_container.begin() + 9);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);

        // insert reverse middle with 0 element
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        rit = container.rbegin() + 1;
        it = container.insert(rit.base(), insert_container.begin(), insert_container.begin());
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse middle with 1 element
        expected_container = {Foo(10), Foo(0), Foo(11)};
        container = {Foo(10), Foo(11)};
        rit = container.rbegin() + 1;
        it = container.insert(rit.base(), insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse middle with n elements
        expected_container = {Foo(10), Foo(0), Foo(1), Foo(2), Foo(11)};
        container = {Foo(10), Foo(11)};
        rit = container.rbegin() + 1;
        it = container.insert(rit.base(), insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse middle overflow.
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        try
        {
            rit = container.rbegin() + 1;
            it = container.insert(rit.base(), insert_container.begin(), insert_container.begin() + 9);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.end(), insert_container.begin(), insert_container.begin());
        ASSERT_EQ(container.end(), it);
        ASSERT_EQ(Foo(11), *(container.end() - 1));
        ASSERT_EQ(Foo(11), *(container.rbegin()));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 element.
        expected_container = {Foo(10), Foo(11), Foo(0)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.end(), insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(Foo(0), *(container.rbegin()));
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n elements.
        expected_container = {Foo(10), Foo(11), Foo(0), Foo(1), Foo(2)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.end(), insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(2), *(container.end() - 1));
        ASSERT_EQ(Foo(2), *(container.rbegin()));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.end(), insert_container.begin(), insert_container.end());
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *(container.end() - 1));
        ASSERT_EQ(Foo(0), *(container.rbegin()));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
        // insert reverse back
        expected_container = {Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.rend().base(), insert_container.begin(), insert_container.begin());
        ASSERT_EQ(container.begin(), it);
        ASSERT_EQ(Foo(10), *(container.rend() - 1));
        ASSERT_EQ(Foo(10), *(container.begin()));
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 element.
        expected_container = {Foo(0), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.rend().base(), insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(Foo(0), *(container.begin()));
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n elements.
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        it = container.insert(container.rend().base(), insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(Foo(0), *it);
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(Foo(0), *(container.begin()));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back overflow.
        expected_container = {Foo(0)};
        container = {Foo(0)};
        try
        {
            it = container.insert(container.rend().base(), insert_container.begin(), insert_container.end());
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
        ASSERT_EQ(Foo(0), *(container.rend() - 1));
        ASSERT_EQ(Foo(0), *(container.begin()));
        ASSERT_EQ(1, container.size());
        ASSERT_EQ(expected_container, container);
    }
}

TEST(Deque, Method_insert_initailize_list)
{
    Deque<Foo, 10> container({Foo(10), Foo(11)});
    Deque<Foo, 10> expected_container({Foo(10), Foo(11)});
    Deque<Foo, 10>::iterator it;
    Deque<Foo, 10>::reverse_iterator rit;

    // insert front with 0 element.
    it = container.insert(container.begin(), {});
    ASSERT_EQ(Foo(10), *it);
    ASSERT_EQ(Foo(10), *container.begin());
    ASSERT_EQ(Foo(10), *(container.rend() - 1));
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // insert front with 1 element.
    expected_container = {Foo(0), Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.begin(), {Foo(0)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(0), *container.begin());
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    ASSERT_EQ(3, container.size());
    ASSERT_EQ(expected_container, container);
    // insert front with n elements.
    expected_container = {Foo(0), Foo(1), Foo(2), Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.begin(), {Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(0), *container.begin());
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    ASSERT_EQ(5, container.size());
    ASSERT_EQ(expected_container, container);
    // insert front overflow.
    expected_container = {Foo(0)};
    container = {Foo(0)};
    try
    {
        it = container.insert(container.begin(), 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
                );
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
    ASSERT_EQ(Foo(0), *container.begin());
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);

    // insert reverse front with 0 element.
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.rbegin().base(), {});
    ASSERT_EQ(container.end(), it);
    ASSERT_EQ(Foo(11), *container.rbegin());
    ASSERT_EQ(Foo(11), *(container.end() - 1));
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse front with 1 element.
    expected_container = {Foo(10), Foo(11), Foo(0)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.rbegin().base(), {Foo(0)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(0), *container.rbegin());
    ASSERT_EQ(Foo(0), *(container.end() - 1));
    ASSERT_EQ(3, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse front with n elements.
    expected_container = {Foo(10), Foo(11), Foo(0), Foo(1), Foo(2)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.rbegin().base(), {Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(2), *container.rbegin());
    ASSERT_EQ(Foo(2), *(container.end() - 1));
    ASSERT_EQ(5, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse front overflow.
    expected_container = {Foo(0)};
    container = {Foo(0)};
    try
    {
        it = container.insert(container.rbegin().base(), 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
                );
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
    ASSERT_EQ(Foo(0), *container.rbegin());
    ASSERT_EQ(Foo(0), *(container.end() - 1));
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);

    // insert middle with 0 element
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.begin() + 1;
    it = container.insert(it, {});
    ASSERT_EQ(Foo(11), *it);
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // insert middle with 1 element
    expected_container = {Foo(10), Foo(0), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.begin() + 1;
    it = container.insert(it, {Foo(0)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(3, container.size());
    ASSERT_EQ(expected_container, container);
    // insert middle with n elements
    expected_container = {Foo(10), Foo(0), Foo(1), Foo(2), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.begin() + 1;
    it = container.insert(it, {Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(5, container.size());
    ASSERT_EQ(expected_container, container);
    // insert middle overflow.
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    try
    {
        it = container.insert(container.begin() + 1, 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
                );
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);

    // insert reverse middle with 0 element
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    rit = container.rbegin() + 1;
    it = container.insert(rit.base(), {});
    ASSERT_EQ(Foo(11), *it);
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse middle with 1 element
    expected_container = {Foo(10), Foo(0), Foo(11)};
    container = {Foo(10), Foo(11)};
    rit = container.rbegin() + 1;
    it = container.insert(rit.base(), {Foo(0)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(3, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse middle with n elements
    expected_container = {Foo(10), Foo(0), Foo(1), Foo(2), Foo(11)};
    container = {Foo(10), Foo(11)};
    rit = container.rbegin() + 1;
    it = container.insert(rit.base(), {Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(5, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse middle overflow.
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    try
    {
        rit = container.rbegin() + 1;
        it = container.insert(rit.base(),
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);

    // insert back
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.end(), {});
    ASSERT_EQ(container.end(), it);
    ASSERT_EQ(Foo(11), *(container.end() - 1));
    ASSERT_EQ(Foo(11), *(container.rbegin()));
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // insert back with 1 element.
    expected_container = {Foo(10), Foo(11), Foo(0)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.end(), {Foo(0)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(0), *(container.end() - 1));
    ASSERT_EQ(Foo(0), *(container.rbegin()));
    ASSERT_EQ(3, container.size());
    ASSERT_EQ(expected_container, container);
    // insert back with n elements.
    expected_container = {Foo(10), Foo(11), Foo(0), Foo(1), Foo(2)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.end(), {Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(2), *(container.end() - 1));
    ASSERT_EQ(Foo(2), *(container.rbegin()));
    ASSERT_EQ(5, container.size());
    ASSERT_EQ(expected_container, container);
    // insert back overflow.
    expected_container = {Foo(0)};
    container = {Foo(0)};
    try
    {
        it = container.insert(container.end(), 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
                );
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
    ASSERT_EQ(Foo(0), *(container.end() - 1));
    ASSERT_EQ(Foo(0), *(container.rbegin()));
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // insert reverse back
    expected_container = {Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.rend().base(), {});
    ASSERT_EQ(container.begin(), it);
    ASSERT_EQ(Foo(10), *(container.rend() - 1));
    ASSERT_EQ(Foo(10), *(container.begin()));
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // insert back with 1 element.
    expected_container = {Foo(0), Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.rend().base(), {Foo(0)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    ASSERT_EQ(Foo(0), *(container.begin()));
    ASSERT_EQ(3, container.size());
    ASSERT_EQ(expected_container, container);
    // insert back with n elements.
    expected_container = {Foo(0), Foo(1), Foo(2), Foo(10), Foo(11)};
    container = {Foo(10), Foo(11)};
    it = container.insert(container.rend().base(), {Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), *it);
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    ASSERT_EQ(Foo(0), *(container.begin()));
    ASSERT_EQ(5, container.size());
    ASSERT_EQ(expected_container, container);
    // insert back overflow.
    expected_container = {Foo(0)};
    container = {Foo(0)};
    try
    {
        it = container.insert(container.rend().base(), 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
                );
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {}
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
    ASSERT_EQ(Foo(0), *(container.rend() - 1));
    ASSERT_EQ(Foo(0), *(container.begin()));
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
}

TEST(Deque, Method_emplace)
{
    // Test typename Deque<T, N>::iterator Deque<T, N>::emplace( const_iterator pos, Args&&... args )
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        Deque<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
        Deque<Foo, 10> expected_container({Foo(-1), Foo(0), Foo(1), Foo(2)});
        Deque<Foo, 10>::iterator it;
        Deque<Foo, 10>::reverse_iterator rit;

        // insert front
        it = container.emplace(container.begin(), -1);
        ASSERT_EQ(Foo(-1), *it);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        it = container.emplace(container.rbegin().base(), 3);
        ASSERT_EQ(Foo(3), *it);
        ASSERT_EQ(Foo(3), *container.rbegin());
        ASSERT_EQ(Foo(3), *(container.end() - 1));
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle
        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(1), Foo(2), Foo(3)};
        it = std::find(container.begin(), container.end(), Foo(0));
        it = container.emplace(it, 11);
        ASSERT_EQ(Foo(11), *it);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3)};
        rit = std::find(container.rbegin(), container.rend(), Foo(0));
        it = container.emplace(rit.base(), 12);
        ASSERT_EQ(Foo(12), *it);
        ASSERT_EQ(7, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        expected_container = {Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4)};
        it = container.emplace(container.end(), 4);
        ASSERT_EQ(Foo(4), *it);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(8, container.size());
        ASSERT_EQ(expected_container, container);

        expected_container = {Foo(-2), Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4)};
        it = container.emplace(container.rend().base(), -2);
        ASSERT_EQ(Foo(-2), *it);
        ASSERT_EQ(Foo(-2), *(container.rend() - 1));
        ASSERT_EQ(Foo(-2), *container.begin());
        ASSERT_EQ(9, container.size());
        ASSERT_EQ(expected_container, container);

        //overflow
        expected_container = {Foo(-2), Foo(-1), Foo(11), Foo(0), Foo(12), Foo(1), Foo(2), Foo(3), Foo(4), Foo(100)};
        it = container.emplace(container.end(), 100);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
        
        try
        {
            it = container.emplace(container.end(), 100);
            FAIL() << "Expected throw exception!";
        }
        catch(holo::exception::BadAllocException& e)
        {}
        catch(...)
        {
            FAIL() << "Catch unexpected exception!";
        }
    }
}

TEST(Deque, Method_erase_iterator)
{
    Deque<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    Deque<Foo, 10> expected_container(
            {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    //erase front
    auto it = container.erase(container.begin());
    ASSERT_EQ(Foo(1), *it);
    ASSERT_EQ(9, container.size());
    ASSERT_EQ(expected_container, container);

    //erase middle
    expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(6), Foo(7), Foo(8), Foo(9)};
    it = container.erase(container.begin() + 4);
    ASSERT_EQ(Foo(6), *it);
    ASSERT_EQ(8, container.size());
    ASSERT_EQ(expected_container, container);

    //erase back
    expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(6), Foo(7), Foo(8)};
    it = container.erase(container.end() - 1);
    ASSERT_EQ(container.end(), it);
    ASSERT_EQ(7, container.size());
    ASSERT_EQ(expected_container, container);

    //erase empty container
    container = {};
    ASSERT_EQ(0, container.size());
}

TEST(Deque, Method_erase_iterator_range)
{
    Deque<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    Deque<Foo, 10> expected_container(
            {Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );

    // first == last
    auto it = container.erase(container.begin(), container.begin());
    ASSERT_EQ(container.begin(), it);
    ASSERT_EQ(10, container.size());
    it = container.erase(container.begin() + 5, container.begin() + 5);
    ASSERT_EQ(container.begin() + 5, it);
    ASSERT_EQ(10, container.size());
    it = container.erase(container.end() - 1, container.end() - 1);
    ASSERT_EQ(container.end() - 1, it);
    ASSERT_EQ(10, container.size());

    //erase front
    it = container.erase(container.begin(), container.begin() + 2);
    ASSERT_EQ(Foo(2), *it);
    ASSERT_EQ(8, container.size());
    ASSERT_EQ(expected_container, container);

    //erase middle
    expected_container = {Foo(2), Foo(3), Foo(6), Foo(7), Foo(8), Foo(9)};
    it = container.erase(container.begin() + 2, container.begin() + 4);
    ASSERT_EQ(Foo(6), *it);
    ASSERT_EQ(6, container.size());
    ASSERT_EQ(expected_container, container);

    //erase back
    expected_container = {Foo(2), Foo(3), Foo(6), Foo(7)};
    it = container.erase(container.end() - 2, container.end());
    ASSERT_EQ(container.end(), it);
    ASSERT_EQ(4, container.size());
    ASSERT_EQ(expected_container, container);

    //erase empty container
    container = {};
    ASSERT_EQ(0, container.size());
}

TEST(Deque, Method_push_back)
{
    Deque<Foo, 10> container;
    Deque<Foo, 10> expected_container;

    // push_back empty container
    expected_container = {Foo(0)};
    ASSERT_EQ(0, container.size());
    container.push_back(Foo(0));
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // push_back non-empty container
    expected_container = {Foo(0), Foo(1)};
    container.push_back(Foo(1));
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // overflow
    container.insert(container.end(), 8, Foo(10));
    ASSERT_EQ(10, container.size());
    try
    {
        container.push_back(Foo(1));
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }

    container = {};
    Foo value(0);
    // push_back empty container
    expected_container = {Foo(0)};
    ASSERT_EQ(0, container.size());
    container.push_back(value);
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // push_back non-empty container
    expected_container = {Foo(0), Foo(1)};
    value = Foo(1);
    container.push_back(value);
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // overflow
    container.insert(container.end(), 8, Foo(10));
    ASSERT_EQ(10, container.size());
    try
    {
        container.push_back(value);
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }

}

TEST(Deque, Method_emplace_back)
{
    Deque<Foo, 10> container;
    Deque<Foo, 10> expected_container;

    // emplace_back empty container
    expected_container = {Foo(0)};
    ASSERT_EQ(0, container.size());
    container.emplace_back(0);
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // emplace_back non-empty container
    expected_container = {Foo(0), Foo(1)};
    container.emplace_back(1);
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // overflow
    container.insert(container.end(), 8, Foo(10));
    ASSERT_EQ(10, container.size());
    try
    {
        container.emplace_back(1);
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
}

TEST(Deque, Method_pop_back)
{
    Deque<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    Deque<Foo, 10> expected_container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8)}
            );

    // pop_back full container
    ASSERT_EQ(10, container.size());
    container.pop_back();
    ASSERT_EQ(9, container.size());
    ASSERT_EQ(expected_container, container);
    // pop_back container
    expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7)};
    container.pop_back();
    ASSERT_EQ(8, container.size());
    ASSERT_EQ(expected_container, container);
    // underflow
}

TEST(Deque, Method_push_front)
{
    Deque<Foo, 10> container;
    Deque<Foo, 10> expected_container;

    // push_front empty container
    expected_container = {Foo(0)};
    ASSERT_EQ(0, container.size());
    container.push_front(Foo(0));
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // push_front non-empty container
    expected_container = {Foo(1), Foo(0)};
    container.push_front(Foo(1));
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // overflow
    container.insert(container.end(), 8, Foo(10));
    ASSERT_EQ(10, container.size());
    try
    {
        container.push_front(Foo(1));
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }

    container = {};
    Foo value(0);
    // push_front empty container
    expected_container = {Foo(0)};
    ASSERT_EQ(0, container.size());
    container.push_front(value);
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // push_front non-empty container
    expected_container = {Foo(1), Foo(0)};
    value = Foo(1);
    container.push_front(value);
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // overflow
    container.insert(container.end(), 8, Foo(10));
    ASSERT_EQ(10, container.size());
    try
    {
        container.push_front(value);
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
}

TEST(Deque, Method_emplace_front)
{
    Deque<Foo, 10> container;
    Deque<Foo, 10> expected_container;

    // emplace_front empty container
    expected_container = {Foo(0)};
    ASSERT_EQ(0, container.size());
    container.emplace_front(0);
    ASSERT_EQ(1, container.size());
    ASSERT_EQ(expected_container, container);
    // emplace_front non-empty container
    expected_container = {Foo(1), Foo(0)};
    container.emplace_front(1);
    ASSERT_EQ(2, container.size());
    ASSERT_EQ(expected_container, container);
    // overflow
    container.insert(container.end(), 8, Foo(10));
    ASSERT_EQ(10, container.size());
    try
    {
        container.emplace_front(1);
        FAIL() << "Expected throw exception!";
    }
    catch(holo::exception::BadAllocException& e)
    {
    }
    catch(...)
    {
        FAIL() << "Catch unexpected exception!";
    }
}

TEST(Deque, Method_pop_front)
{
    Deque<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    Deque<Foo, 10> expected_container(
            {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );

    // pop_front full container
    ASSERT_EQ(10, container.size());
    container.pop_front();
    ASSERT_EQ(9, container.size());
    ASSERT_EQ(expected_container, container);
    // pop_front container
    expected_container = {Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)};
    container.pop_front();
    ASSERT_EQ(8, container.size());
    ASSERT_EQ(expected_container, container);
    // underflow
}

TEST(Deque, Method_swap)
{
    Deque<Foo, 10> container1({});
    Deque<Foo, 10> container2({});
    Deque<Foo, 10> expected_container1({});
    Deque<Foo, 10> expected_container2({});

    // swap two empty containers
    container1.swap(container2);
    ASSERT_EQ(expected_container1, container1);
    ASSERT_EQ(expected_container2, container2);

    // swap empty container and non-empty container
    container1 = {};
    container2 = {Foo(0)};
    expected_container1 = {Foo(0)};
    expected_container2 = {};

    container1.swap(container2);
    ASSERT_EQ(expected_container1, container1);
    ASSERT_EQ(expected_container2, container2);

    // swap two non_empty containers
    container1 = {Foo(1)};
    container2 = {Foo(0)};
    expected_container1 = {Foo(0)};
    expected_container2 = {Foo(1)};

    container1.swap(container2);
    ASSERT_EQ(expected_container1, container1);
    ASSERT_EQ(expected_container2, container2);
}

TEST(Deque, Function_equal_not_equal)
{
    Deque<Foo, 10> container1;
    Deque<Foo, 10> container2;

    container1 = {};
    container2 = {};
    ASSERT_TRUE(container1 == container2);
    ASSERT_FALSE(container1 != container2);

    container1 = {Foo(0)};
    container2 = {Foo(0)};
    ASSERT_TRUE(container1 == container2);
    ASSERT_FALSE(container1 != container2);

    container1 = {Foo(0)};
    container2 = {Foo(1)};
    ASSERT_FALSE(container1 == container2);
    ASSERT_TRUE(container1 != container2);

    container1 = {Foo(0)};
    container2 = {Foo(0), Foo(2)};
    ASSERT_FALSE(container1 == container2);
    ASSERT_TRUE(container1 != container2);
}

TEST(Deque, Function_compare)
{
    Deque<Foo, 10> container1;
    Deque<Foo, 10> container2;

    container1 = {};
    container2 = {};
    ASSERT_FALSE(container1 < container2);
    ASSERT_FALSE(container1 > container2);
    ASSERT_TRUE(container1 <= container2);
    ASSERT_TRUE(container1 >= container2);

    container1 = {Foo(0)};
    container2 = {Foo(0)};
    ASSERT_FALSE(container1 < container2);
    ASSERT_FALSE(container1 > container2);
    ASSERT_TRUE(container1 <= container2);
    ASSERT_TRUE(container1 >= container2);

    container1 = {Foo(0)};
    container2 = {Foo(1)};
    ASSERT_TRUE(container1 < container2);
    ASSERT_FALSE(container1 > container2);
    ASSERT_TRUE(container1 <= container2);
    ASSERT_FALSE(container1 >= container2);

    container1 = {Foo(0)};
    container2 = {Foo(0), Foo(2)};
    ASSERT_TRUE(container1 < container2);
    ASSERT_FALSE(container1 > container2);
    ASSERT_TRUE(container1 <= container2);
    ASSERT_FALSE(container1 >= container2);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
