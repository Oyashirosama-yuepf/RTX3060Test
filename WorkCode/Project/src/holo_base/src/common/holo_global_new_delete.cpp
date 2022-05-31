#include <new>
#include "stdlib.h"

/**
 * @brief operator new
 *
 * @param size
 * @return void*
 */
void* operator new(std::size_t size)
{
    void* ptr = malloc(size);
    if (nullptr == ptr)
    {
        throw std::bad_alloc();
    }
    else
    {
        return ptr;
    }
}

/**
 * @brief operator new
 *
 * @param size
 * @param nothrow_value
 * @return void*
 */
void* operator new(std::size_t size, const std::nothrow_t& nothrow_value) noexcept
{
    (void)nothrow_value;
    return malloc(size);
}

/**
 * @brief operator new[]
 *
 * @param size
 * @return void*
 */
void* operator new[](std::size_t size)
{
    void* ptr = malloc(size);
    if (nullptr == ptr)
    {
        throw std::bad_alloc();
    }
    else
    {
        return ptr;
    }
}

/**
 * @brief operator new[]
 *
 * @param size
 * @param nothrow_value
 * @return void*
 */
void* operator new[](std::size_t size, const std::nothrow_t& nothrow_value) noexcept
{
    (void)nothrow_value;
    return malloc(size);
}

/**
 * @brief operator delete
 *
 * @param ptr
 */
void operator delete(void* ptr) noexcept
{
    if (ptr)
    {
        free(ptr);
    }
}

/**
 * @brief operator delete
 *
 * @param ptr
 * @param nothrow_constant
 */
void operator delete(void* ptr, const std::nothrow_t& nothrow_constant) noexcept
{
    (void)nothrow_constant;
    if (ptr)
    {
        free(ptr);
    }
}

/**
 * @brief operator delete[]
 *
 * @param ptr
 */
void operator delete[](void* ptr) noexcept
{
    if (ptr)
    {
        free(ptr);
    }
}

/**
 * @brief operator delete[]
 *
 * @param ptr
 * @param nothrow_constant
 */
void operator delete[](void* ptr, const std::nothrow_t& nothrow_constant) noexcept
{
    (void)nothrow_constant;
    if (ptr)
    {
        free(ptr);
    }
}
