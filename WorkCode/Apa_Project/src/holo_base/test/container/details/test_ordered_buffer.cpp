/**
 * @brief unit test for OrderedBuffer class
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
#include <holo/container/details/ordered_buffer.h>


using holo::container::details::OrderedBuffer;

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

    holo::bool_t operator>(const Foo& other) const
    {
        return *(other.data) < *(this->data);
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
 * @brief Test OrderedBufferConstructors;
 *
 */
TEST(OrderedBuffer, Constructor)
{
    /// Test OrderedBuffer()
    {
        OrderedBuffer<Foo, 10> container;
        ASSERT_EQ(0, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_TRUE(container.empty());
    }

    /// Test OrderedBuffer(InputIt first, InputIt last, const Compare& comp = Compare()): C()
    {
        // Test raw pointer
        holo::int32_t test_int_array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        OrderedBuffer<holo::int32_t, 10> int_container(&test_int_array[2], &test_int_array[8]);
        ASSERT_EQ(6, int_container.size());
        ASSERT_EQ(10, int_container.max_size());
        for(std::size_t i = 0; i < int_container.size(); ++i)
        {
            ASSERT_TRUE(2 + (holo::int32_t)i == int_container[i]);
        }

        OrderedBuffer<holo::int32_t, 10, std::greater<holo::int32_t> > int_container2(
                &test_int_array[2], &test_int_array[8]);
        ASSERT_EQ(6, int_container2.size());
        ASSERT_EQ(10, int_container2.max_size());
        for(std::size_t i = 0; i < int_container2.size(); ++i)
        {
            ASSERT_EQ(7 - (holo::int32_t)i, int_container2[i]);
        }

        std::vector<Foo> test_vector = 
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        // zero
        {
            OrderedBuffer<Foo, 10> container(test_vector.begin(), test_vector.begin());
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            OrderedBuffer<Foo, 10> container(test_vector.begin() + 2, test_vector.begin() + 8);
            ASSERT_EQ(6, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(2 + i) == container[i]);
            }

            OrderedBuffer<Foo, 10, std::greater<Foo> > container2(
                    test_vector.begin() + 2, test_vector.begin() + 8);
            ASSERT_EQ(6, container2.size());
            ASSERT_EQ(10, container2.max_size());
            ASSERT_FALSE(container2.empty());
            for(std::size_t i = 0; i < container2.size(); ++i)
            {
                ASSERT_TRUE(Foo(7 - i) == container2[i]);
            }
        }
        // max_size
        {
            OrderedBuffer<Foo, 10> container(test_vector.begin(), test_vector.begin() + 10);
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
            OrderedBuffer<Foo, 10> container(test_vector.begin(), test_vector.end());
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());

            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i + 1), container[i]);
            }
        }
    }

    /// Test OrderedBuffer(const OrderedBuffer& other)
    {
        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        OrderedBuffer<Foo, 10> container_other(test_vector.begin() + 2, test_vector.begin() + 8);
        OrderedBuffer<Foo, 10> container(container_other);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        for(std::size_t i = 0; i < container.size(); ++i)
        {
            ASSERT_TRUE(Foo(2 + i) == container[i]);
        }
    }

    /// Test OrderedBuffer(OrderedBuffer&& other)
    {
        OrderedBuffer<Foo, 10> container_other = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        const holo::int32_t* origin_ptr = &(container_other[0].GetData());
        OrderedBuffer<Foo, 10> container(std::move(container_other));
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        OrderedBuffer<Foo, 10> tmp{Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        ASSERT_EQ(container, tmp);
        const holo::int32_t* ptr = &(container[0].GetData());
        ASSERT_EQ(ptr, origin_ptr);
    }

    /// Test OrderedBuffer(std::initializer_list<value_type> ilist)
    {
        // zero
        {
            OrderedBuffer<Foo, 10> container({});
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            OrderedBuffer<Foo, 10> container( 
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
            OrderedBuffer<Foo, 10> container( 
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
            OrderedBuffer<Foo, 10> container( 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)});
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());

            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i + 1), container[i]);
            }
        }
    }
}

TEST(OrderedBuffer, OperatorAssignment)
{
    /// Test OrderedBuffer& operator= (const OrderedBuffer& other);
    {
        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        OrderedBuffer<Foo, 10> container_other(test_vector.begin() + 2, test_vector.begin() + 8);
        OrderedBuffer<Foo, 10> container = container_other;
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        for(std::size_t i = 0; i < container.size(); ++i)
        {
            ASSERT_TRUE(Foo(2 + i) == container[i]);
        }
    }

    /// Test OrderedBuffer& operator= (OrderedBuffer&& other);
    {
        OrderedBuffer<Foo, 10> container_other = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        const holo::int32_t* origin_ptr = &(container_other[0].GetData());
        OrderedBuffer<Foo, 10> container = std::move(container_other);
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(10, container.max_size());
        ASSERT_FALSE(container.empty());
        OrderedBuffer<Foo, 10> tmp{Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6)};
        ASSERT_EQ(container, tmp);
        const holo::int32_t* ptr = &(container[0].GetData());
        ASSERT_EQ(ptr, origin_ptr);
    }

    /// Test OrderedBuffer& operator= (std::initializer_list<value_type> ilist);
    {
        // zero
        {
            OrderedBuffer<Foo, 10> container = {};
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            OrderedBuffer<Foo, 10> container = 
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
            OrderedBuffer<Foo, 10> container = 
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
            OrderedBuffer<Foo, 10> container = 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i + 1), container[i]);
            }
        }
    }
}

/**
 * @brief Test reference at( size_type pos ); const_reference at( size_type pos ) const;
 */
TEST(OrderedBuffer, Method_at)
{
    OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
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

    const OrderedBuffer<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
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
TEST(OrderedBuffer, OperatorSquareBrackets)
{
    OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    for(holo::uint32_t i = 0; i < container.size(); ++i)
    {
        ASSERT_EQ(Foo(i), container[i]);
    }
    container[container.size()];

    const OrderedBuffer<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    for(holo::uint32_t i = 0; i < const_container.size(); ++i)
    {
        ASSERT_EQ(Foo(i), const_container[i]);
    }
    const_container[const_container.size()];
}

TEST(OrderedBuffer, Method_front)
{
    OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), container.front());
    container.pop_front();
    ASSERT_EQ(Foo(1), container.front());
    container.pop_front();
    ASSERT_EQ(Foo(2), container.front());

    const OrderedBuffer<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(0), const_container.front());

    OrderedBuffer<Foo, 10> empty_container;
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

    const OrderedBuffer<Foo, 10> const_empty_container;
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

TEST(OrderedBuffer, Method_back)
{
    OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(2), container.back());
    container.pop_back();
    ASSERT_EQ(Foo(1), container.back());
    container.pop_back();
    ASSERT_EQ(Foo(0), container.back());

    const OrderedBuffer<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});
    ASSERT_EQ(Foo(2), const_container.back());

    OrderedBuffer<Foo, 10> empty_container;
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

    const OrderedBuffer<Foo, 10> const_empty_container;
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

TEST(OrderedBuffer, Method_begin)
{
    OrderedBuffer<Foo, 10> container = {Foo(0), Foo(1), Foo(2)};
    const OrderedBuffer<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});

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

TEST(OrderedBuffer, Method_end)
{
    OrderedBuffer<Foo, 10> container = {Foo(0), Foo(1), Foo(2)};
    const OrderedBuffer<Foo, 10> const_container({Foo(0), Foo(1), Foo(2)});

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

TEST(OrderedBuffer, Method_empty_size_max_size_resize_shrink_to_fit)
{
    OrderedBuffer<Foo, 10> container;
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

TEST(OrderedBuffer, Method_assign)
{
    /// Test template<typename InputIt> void assign(InputIt first, InputIt last)
    {
        // Test raw pointer
        holo::int32_t test_int_array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        OrderedBuffer<holo::int32_t, 10> int_container;
        int_container.assign(&test_int_array[2], &test_int_array[8]);
        ASSERT_EQ(6, int_container.size());
        ASSERT_EQ(10, int_container.max_size());
        for(std::size_t i = 0; i < int_container.size(); ++i)
        {
            ASSERT_TRUE(2 + (holo::int32_t)i == int_container[i]);
        }

        std::vector<Foo> test_vector = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        // zero
        {
            OrderedBuffer<Foo, 10> container;
            container.assign(test_vector.begin(), test_vector.begin());
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            OrderedBuffer<Foo, 10> container;
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
            OrderedBuffer<Foo, 10> container;
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
            OrderedBuffer<Foo, 10> container;
            container.assign(test_vector.begin(), test_vector.end());
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_TRUE(Foo(i + 1) == container[i]);
            }
        }
    }

    /// Test OrderedBuffer(std::initializer_list<value_type> ilist)
    {
        // zero
        {
            OrderedBuffer<Foo, 10> container;
            container.assign({});
            ASSERT_EQ(0, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_TRUE(container.empty());
        }
        // normal case
        {
            OrderedBuffer<Foo, 10> container; 
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
            OrderedBuffer<Foo, 10> container;
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
            OrderedBuffer<Foo, 10> container;
            container.assign( 
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)});
            ASSERT_EQ(10, container.size());
            ASSERT_EQ(10, container.max_size());
            ASSERT_FALSE(container.empty());
            for(std::size_t i = 0; i < container.size(); ++i)
            {
                ASSERT_EQ(Foo(i + 1), container[i]);
            }
        }
    }
}

TEST(OrderedBuffer, Method_clear)
{
    OrderedBuffer<Foo, 10> container(
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
TEST(OrderedBuffer, Method_insert_lvalue)
{
    // Test std::pair<iterator, holo::holo::bool_t> insert( const value_type& value );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
        OrderedBuffer<Foo, 10> expected_container({Foo(-1), Foo(0), Foo(1), Foo(2)});
        OrderedBuffer<Foo, 10>::iterator it;
        OrderedBuffer<Foo, 10>::reverse_iterator rit;

        // insert front
        Foo value(-1);
        auto pair = container.insert(value);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(-1), *pair.first);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);
        // insert same key in front
        pair = container.insert(value);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(-1), *pair.first);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle
        container = {Foo(-1), Foo(0), Foo(2), Foo(3)};
        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        value = Foo(1);
        pair = container.insert(value);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(1), *pair.first);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert same key in the middle.
        pair = container.insert(value);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(1), *pair.first);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3), Foo(4)};
        value = Foo(4);
        pair = container.insert(value);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(4), *pair.first);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);
        // insert same key in back
        pair = container.insert(value);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(4), *pair.first);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);

        //overflow
        container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        // insert front overflow
        value = Foo(-1);
        pair = container.insert(value);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(container.end(), pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());

        // insert middle overflow
        expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        value = Foo(5);
        pair = container.insert(value);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(5), *pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
        
        // insert back overflow
        expected_container = {Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10), Foo(11)};
        value = Foo(11);
        pair = container.insert(value);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(11), *pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
    }
}

TEST(OrderedBuffer, Method_insert_rvalue)
{
    // Test std::pair<iterator, holo::bool_t> insert( const value_type& value );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
        OrderedBuffer<Foo, 10> expected_container({Foo(-1), Foo(0), Foo(1), Foo(2)});
        OrderedBuffer<Foo, 10>::iterator it;
        OrderedBuffer<Foo, 10>::reverse_iterator rit;

        // insert front
        auto pair = container.insert(Foo(-1));
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(-1), *pair.first);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);
        // insert same key in front
        pair = container.insert(Foo(-1));
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(-1), *pair.first);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle
        container = {Foo(-1), Foo(0), Foo(2), Foo(3)};
        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        pair = container.insert(Foo(1));
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(1), *pair.first);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert same key in the middle.
        pair = container.insert(Foo(1));
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(1), *pair.first);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3)};
        expected_container = {Foo(-1), Foo(0), Foo(1), Foo(2), Foo(3), Foo(4)};
        pair = container.insert(Foo(4));
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(4), *pair.first);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);
        // insert same key in back
        pair = container.insert(Foo(4));
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(4), *pair.first);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(6, container.size());
        ASSERT_EQ(expected_container, container);

        //overflow
        container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        // insert front overflow
        pair = container.insert(Foo(-1));
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(container.end(), pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());

        // insert middle overflow
        expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        pair = container.insert(Foo(5));
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(5), *pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
        
        // insert back overflow
        expected_container = {Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10), Foo(11)};
        pair = container.insert(Foo(11));
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(11), *pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
    }
}

TEST(OrderedBuffer, Method_insert_iterator_range)
{
    // Test iterator insert( const_iterator pos, InputIt first, InputIt last );
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        OrderedBuffer<Foo, 10> insert_container(
                {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
        OrderedBuffer<Foo, 10> container({Foo(10), Foo(11)});
        OrderedBuffer<Foo, 10> expected_container({Foo(10), Foo(11)});

        // insert front with 0 element.
        container.insert(insert_container.begin(), insert_container.begin());
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with 1 element.
        expected_container = {Foo(0), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        container.insert(insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with n elements.
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        container.insert(insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front overflow.
        expected_container = {Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        container.insert(insert_container.begin(), insert_container.end());
        ASSERT_EQ(10, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle with 0 element
        expected_container = {Foo(0), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert(insert_container.begin(), insert_container.begin());
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with 1 element
        expected_container = {Foo(0), Foo(1), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert(insert_container.begin() + 1, insert_container.begin() + 2);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with 1 same key element
        expected_container = {Foo(0), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert(insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with n elements
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert(insert_container.begin() + 1, insert_container.begin() + 4);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with n elements
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert(insert_container.begin(), insert_container.begin() + 4);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle overflow.
        expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert(insert_container.begin(), insert_container.end());
        ASSERT_EQ(10, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        expected_container = {Foo(-2), Foo(-1)};
        container = {Foo(-2), Foo(-1)};
        container.insert(insert_container.begin(), insert_container.begin());
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 element.
        expected_container = {Foo(-2), Foo(-1), Foo(0)};
        container = {Foo(-2), Foo(-1)};
        container.insert(insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 same element.
        expected_container = {Foo(-2), Foo(-1), Foo(0)};
        container = {Foo(-2), Foo(-1), Foo(0)};
        container.insert(insert_container.begin(), insert_container.begin() + 1);
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n elements.
        expected_container = {Foo(-2), Foo(-1), Foo(0), Foo(1), Foo(2)};
        container = {Foo(-2), Foo(-1)};
        container.insert(insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n same elements.
        expected_container = {Foo(-2), Foo(-1), Foo(0), Foo(1), Foo(2)};
        container = {Foo(-2), Foo(-1), Foo(0), Foo(1), Foo(2)};
        container.insert(insert_container.begin(), insert_container.begin() + 3);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back overflow.
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)};
        container = {Foo(-1)};
        container.insert(insert_container.begin(), insert_container.end());
        ASSERT_EQ(10, container.size());
        ASSERT_EQ(expected_container, container);
    }
}

TEST(OrderedBuffer, Method_insert_initailize_list)
{
    // Test void insert( std::initializer_list<value_type> ilist )
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        OrderedBuffer<Foo, 10> container({Foo(10), Foo(11)});
        OrderedBuffer<Foo, 10> expected_container({Foo(10), Foo(11)});

        // insert with 0 element.
        container.insert({});
        ASSERT_EQ(2, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with 1 element.
        expected_container = {Foo(0), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        container.insert({Foo(0)});
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front with n elements.
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        container.insert({Foo(0), Foo(1), Foo(2)});
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert front overflow.
        expected_container = {Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10), Foo(11)};
        container = {Foo(10), Foo(11)};
        container.insert({Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
        ASSERT_EQ(10, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle with 1 element
        expected_container = {Foo(0), Foo(1), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert({Foo(1)});
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with 1 same key element
        expected_container = {Foo(0), Foo(1), Foo(11)};
        container = {Foo(0), Foo(1), Foo(11)};
        container.insert({Foo(1)});
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with n elements
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert({Foo(1), Foo(2), Foo(3)});
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle with n elements
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert({Foo(0), Foo(1), Foo(2), Foo(3)});
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert middle overflow.
        expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(11)};
        container = {Foo(0), Foo(11)};
        container.insert({Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
        ASSERT_EQ(10, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back with 1 element.
        expected_container = {Foo(-2), Foo(-1), Foo(0)};
        container = {Foo(-2), Foo(-1)};
        container.insert({Foo(0)});
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with 1 same element.
        expected_container = {Foo(-2), Foo(-1), Foo(0)};
        container = {Foo(-2), Foo(-1), Foo(0)};
        container.insert({Foo(0)});
        ASSERT_EQ(3, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n elements.
        expected_container = {Foo(-2), Foo(-1), Foo(0), Foo(1), Foo(2)};
        container = {Foo(-2), Foo(-1)};
        container.insert({Foo(0), Foo(1), Foo(2)});
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back with n same elements.
        expected_container = {Foo(-2), Foo(-1), Foo(0), Foo(1), Foo(2)};
        container = {Foo(-2), Foo(-1), Foo(0), Foo(1), Foo(2)};
        container.insert({Foo(0), Foo(1), Foo(2)});
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);
        // insert back overflow.
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)};
        container = {Foo(-1)};
        container.insert({Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)});
        ASSERT_EQ(10, container.size());
        ASSERT_EQ(expected_container, container);
    }
}

TEST(OrderedBuffer, Method_emplace)
{
    // Test typename OrderedBuffer<T, N>::iterator OrderedBuffer<T, N>::emplace( const_iterator pos, Args&&... args )
    // 1 insert front
    // 2 insert middle
    // 3 insert back
    {
        OrderedBuffer<Foo, 10> container({Foo(0), Foo(1), Foo(2)});
        OrderedBuffer<Foo, 10> expected_container({Foo(-1), Foo(0), Foo(1), Foo(2)});

        // emplace front
        auto pair = container.emplace(-1);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(-1), *pair.first);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        pair = container.emplace(-1);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(-1), *pair.first);
        ASSERT_EQ(Foo(-1), *container.begin());
        ASSERT_EQ(Foo(-1), *(container.rend() - 1));
        ASSERT_EQ(4, container.size());
        ASSERT_EQ(expected_container, container);

        // insert middle
        container = {Foo(0), Foo(1), Foo(3), Foo(4)};
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4)};
        pair = container.emplace(2);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(2), *pair.first);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        pair = container.emplace(2);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(2), *pair.first);
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        // insert back
        container = {Foo(0), Foo(1), Foo(2), Foo(3)};
        expected_container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4)};
        pair = container.emplace(4);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(4), *pair.first);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        pair = container.emplace(4);
        ASSERT_FALSE(pair.second);
        ASSERT_EQ(Foo(4), *pair.first);
        ASSERT_EQ(Foo(4), *(container.end() - 1));
        ASSERT_EQ(Foo(4), *container.rbegin());
        ASSERT_EQ(5, container.size());
        ASSERT_EQ(expected_container, container);

        //overflow
        container = {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)};
        expected_container = {Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9), Foo(10)};
        pair = container.emplace(10);
        ASSERT_TRUE(pair.second);
        ASSERT_EQ(Foo(10), *pair.first);
        ASSERT_EQ(expected_container, container);
        ASSERT_EQ(10, container.size());
    }
}

TEST(OrderedBuffer, Method_erase_iterator)
{
    OrderedBuffer<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    OrderedBuffer<Foo, 10> expected_container(
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

TEST(OrderedBuffer, Method_erase_iterator_range)
{
    OrderedBuffer<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    OrderedBuffer<Foo, 10> expected_container(
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

TEST(OrderedBuffer, Method_pop_back)
{
    OrderedBuffer<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    OrderedBuffer<Foo, 10> expected_container(
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

TEST(OrderedBuffer, Method_pop_front)
{
    OrderedBuffer<Foo, 10> container(
            {Foo(0), Foo(1), Foo(2), Foo(3), Foo(4), Foo(5), Foo(6), Foo(7), Foo(8), Foo(9)}
            );
    OrderedBuffer<Foo, 10> expected_container(
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

TEST(OrderedBuffer, Method_swap)
{
    OrderedBuffer<Foo, 10> container1({});
    OrderedBuffer<Foo, 10> container2({});
    OrderedBuffer<Foo, 10> expected_container1({});
    OrderedBuffer<Foo, 10> expected_container2({});

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

TEST(OrderedBuffer, Function_equal_not_equal)
{
    OrderedBuffer<Foo, 10> container1;
    OrderedBuffer<Foo, 10> container2;

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

TEST(OrderedBuffer, Function_compare)
{
    OrderedBuffer<Foo, 10> container1;
    OrderedBuffer<Foo, 10> container2;

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

TEST(OrderedBuffer, Method_emplace_1)
{
    OrderedBuffer<Foo, 0> container({Foo(0), Foo(1), Foo(2)});
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
