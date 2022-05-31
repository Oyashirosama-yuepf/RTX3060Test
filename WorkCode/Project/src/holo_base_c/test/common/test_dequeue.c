/*!
 * @brief Unit test for Dequeue objects.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-4
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <holo_c/common/dequeue.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <unity.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_init(struct Dequeuef *dequeue, float32_t *buffer, uint32_t buffer_size);
 */
static void test_dequeuef_init(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[20];

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_init(&dequeue, buffer, 20));
    TEST_ASSERT_TRUE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(20, dequeuef_get_capacity(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(0, dequeuef_get_size(&dequeue));

    /* Minimum dequeue */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_init(&dequeue, buffer, 1));
    TEST_ASSERT_TRUE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(1, dequeuef_get_capacity(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(0, dequeuef_get_size(&dequeue));

    /* Invalid parameters */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INVALID_PARAMETER, dequeuef_init(&dequeue, buffer, 0));
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INVALID_PARAMETER, dequeuef_init(&dequeue, buffer, UINT32_MAX));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_push_back(struct Dequeuef *dequeue, float32_t data);
 */
static void test_dequeuef_push_back(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[5];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 5);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 1.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(1, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 2.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(2, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 3.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(3, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 4.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(4, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 5.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_TRUE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(5, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    /* Overflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_OVERFLOW, dequeuef_push_back(&dequeue, 6.0f));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, NULL));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 6.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_TRUE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(5, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, data);

    /* Minimum dequeue */
    dequeuef_init(&dequeue, buffer, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_back(&dequeue, 1.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_TRUE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(1, dequeuef_get_size(&dequeue));

    /* Overflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_OVERFLOW, dequeuef_push_back(&dequeue, 1.0f));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_push_front(struct Dequeuef *dequeue, float32_t data);
 */
static void test_dequeuef_push_front(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[5];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 5);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 1.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(1, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 2.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(2, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 3.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(3, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 4.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_FALSE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(4, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 5.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_TRUE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(5, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    /* Overflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_OVERFLOW, dequeuef_push_front(&dequeue, 5.0f));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, NULL));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 6.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_TRUE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(5, dequeuef_get_size(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, data);

    /* Minimum dequeue */
    dequeuef_init(&dequeue, buffer, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_push_front(&dequeue, 1.0f));
    TEST_ASSERT_FALSE(dequeuef_is_empty(&dequeue));
    TEST_ASSERT_TRUE(dequeuef_is_full(&dequeue));
    TEST_ASSERT_EQUAL_UINT32(1, dequeuef_get_size(&dequeue));

    /* Overflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_OVERFLOW, dequeuef_push_front(&dequeue, 1.0f));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_pop_back(struct Dequeuef *dequeue, float32_t *data);
 */
static void test_dequeuef_pop_back(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[5];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 5);
    dequeuef_push_front(&dequeue, 1.0f);
    dequeuef_push_front(&dequeue, 2.0f);
    dequeuef_push_front(&dequeue, 3.0f);
    dequeuef_push_front(&dequeue, 4.0f);
    dequeuef_push_front(&dequeue, 5.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    dequeuef_push_front(&dequeue, 1.0f);
    dequeuef_push_front(&dequeue, 2.0f);
    dequeuef_push_front(&dequeue, 3.0f);
    dequeuef_push_front(&dequeue, 4.0f);
    dequeuef_push_front(&dequeue, 5.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_pop_back(&dequeue, &data));

    /* Minimum dequeue */
    dequeuef_init(&dequeue, buffer, 1);
    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_pop_back(&dequeue, &data));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_pop_front(struct Dequeuef *dequeue, float32_t *data);
 */
static void test_dequeuef_pop_front(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[5];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 5);
    dequeuef_push_back(&dequeue, 1.0f);
    dequeuef_push_back(&dequeue, 2.0f);
    dequeuef_push_back(&dequeue, 3.0f);
    dequeuef_push_back(&dequeue, 4.0f);
    dequeuef_push_back(&dequeue, 5.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    dequeuef_push_back(&dequeue, 1.0f);
    dequeuef_push_back(&dequeue, 2.0f);
    dequeuef_push_back(&dequeue, 3.0f);
    dequeuef_push_back(&dequeue, 4.0f);
    dequeuef_push_back(&dequeue, 5.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_pop_front(&dequeue, &data));

    /* Minimum dequeue */
    dequeuef_init(&dequeue, buffer, 1);
    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_pop_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_pop_front(&dequeue, &data));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_peek_front(struct Dequeuef *dequeue, float32_t *data);
 */
static void test_dequeuef_peek_back(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[4];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 4);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_peek_back(&dequeue, &data));

    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    dequeuef_push_back(&dequeue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    dequeuef_push_back(&dequeue, 3.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    dequeuef_push_back(&dequeue, 4.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);

    /* Minimum dequeue */
    dequeuef_init(&dequeue, buffer, 1);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_peek_back(&dequeue, &data));

    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_back(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_peek_front(struct Dequeuef *dequeue, float32_t *data);
 */
static void test_dequeuef_peek_front(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[4];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 4);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_peek_front(&dequeue, &data));

    dequeuef_push_front(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    dequeuef_push_front(&dequeue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    dequeuef_push_front(&dequeue, 3.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    dequeuef_push_front(&dequeue, 4.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);

    /* Minimum dequeue */
    dequeuef_init(&dequeue, buffer, 1);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_UNDERFLOW, dequeuef_peek_front(&dequeue, &data));

    dequeuef_push_front(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_peek_front(&dequeue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_get_data_by_index(const struct Dequeuef *dequeue, uint32_t index, float32_t *data);
 */
static void test_dequeuef_get_data_by_index(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[4];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 4);
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INDEX_OUT_OF_RANGE, dequeuef_get_data_by_index(&dequeue, 0, &data));
    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_get_data_by_index(&dequeue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INDEX_OUT_OF_RANGE, dequeuef_get_data_by_index(&dequeue, 1, &data));
    dequeuef_push_front(&dequeue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_get_data_by_index(&dequeue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_get_data_by_index(&dequeue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INDEX_OUT_OF_RANGE, dequeuef_get_data_by_index(&dequeue, 2, &data));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t dequeuef_get_data_by_reverse_index(const struct Dequeuef *dequeue, uint32_t index, float32_t
 * *data);
 */
static void test_dequeuef_get_data_by_reverse_index(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[4];
    float32_t       data;

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 4);
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INDEX_OUT_OF_RANGE, dequeuef_get_data_by_reverse_index(&dequeue, 0, &data));
    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_get_data_by_reverse_index(&dequeue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INDEX_OUT_OF_RANGE, dequeuef_get_data_by_reverse_index(&dequeue, 1, &data));
    dequeuef_push_front(&dequeue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_get_data_by_reverse_index(&dequeue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, dequeuef_get_data_by_reverse_index(&dequeue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_DEQUEUE_INDEX_OUT_OF_RANGE, dequeuef_get_data_by_reverse_index(&dequeue, 2, &data));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test float32_t dequeuef_get_data_by_index_unsafe(const struct Dequeuef *dequeue, uint32_t index);
 */
void test_dequeuef_get_data_by_index_unsafe(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[4];

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 4);
    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, dequeuef_get_data_by_index_unsafe(&dequeue, 0));
    dequeuef_push_front(&dequeue, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, dequeuef_get_data_by_index_unsafe(&dequeue, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, dequeuef_get_data_by_index_unsafe(&dequeue, 1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test float32_t dequeuef_get_data_by_reverse_index_unsafe(const struct Dequeuef *dequeue, uint32_t index);
 */
static void test_dequeuef_get_data_by_reverse_index_unsafe(void)
{
    struct Dequeuef dequeue;
    float32_t       buffer[4];

    /* Normal case */
    dequeuef_init(&dequeue, buffer, 4);
    dequeuef_push_back(&dequeue, 1.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, dequeuef_get_data_by_reverse_index_unsafe(&dequeue, 0));
    dequeuef_push_front(&dequeue, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, dequeuef_get_data_by_reverse_index_unsafe(&dequeue, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, dequeuef_get_data_by_reverse_index_unsafe(&dequeue, 1));
}

// TODO test is_full, is_empty, get_capacity, get_size

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_dequeuef_init);
    RUN_TEST(test_dequeuef_push_back);
    RUN_TEST(test_dequeuef_push_front);
    RUN_TEST(test_dequeuef_pop_back);
    RUN_TEST(test_dequeuef_pop_front);
    RUN_TEST(test_dequeuef_peek_back);
    RUN_TEST(test_dequeuef_peek_front);
    RUN_TEST(test_dequeuef_get_data_by_index);
    RUN_TEST(test_dequeuef_get_data_by_reverse_index);
    RUN_TEST(test_dequeuef_get_data_by_index_unsafe);
    RUN_TEST(test_dequeuef_get_data_by_reverse_index_unsafe);
    return UNITY_END();
}
