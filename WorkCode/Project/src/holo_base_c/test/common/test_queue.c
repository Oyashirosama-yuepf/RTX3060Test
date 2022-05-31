/*!
 * @brief Unit test for Queue objects.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-9-4
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <holo_c/common/queue.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <unity.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t queuef_init(struct Queuef *queue, float32_t *buffer, uint32_t buffer_size);
 */
static void test_queuef_init(void)
{
    struct Queuef queue;
    float32_t     buffer[20];

    /* Normal case */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_init(&queue, buffer, 20));
    TEST_ASSERT_TRUE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(20, queuef_get_capacity(&queue));
    TEST_ASSERT_EQUAL_UINT32(0, queuef_get_size(&queue));

    /* Minimum queue */
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_init(&queue, buffer, 1));
    TEST_ASSERT_TRUE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(1, queuef_get_capacity(&queue));
    TEST_ASSERT_EQUAL_UINT32(0, queuef_get_size(&queue));

    /* Invalid parameters */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INVALID_PARAMETER, queuef_init(&queue, buffer, 0));
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INVALID_PARAMETER, queuef_init(&queue, buffer, UINT32_MAX));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t queuef_push(struct Queuef *queue, float32_t data);
 */
static void test_queuef_push(void)
{
    struct Queuef queue;
    float32_t     buffer[5];

    /* Normal case */
    queuef_init(&queue, buffer, 5);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 1.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(1, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 2.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(2, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 3.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(3, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 4.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(4, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 5.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_TRUE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(5, queuef_get_size(&queue));

    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 1.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(1, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 2.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(2, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 3.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(3, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 4.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_FALSE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(4, queuef_get_size(&queue));

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 5.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_TRUE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(5, queuef_get_size(&queue));

    /* Overflow */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_OVERFLOW, queuef_push(&queue, 1.0f));

    /* Minimum queue */
    queuef_init(&queue, buffer, 1);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_push(&queue, 1.0f));
    TEST_ASSERT_FALSE(queuef_is_empty(&queue));
    TEST_ASSERT_TRUE(queuef_is_full(&queue));
    TEST_ASSERT_EQUAL_UINT32(1, queuef_get_size(&queue));

    /* Overflow */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_OVERFLOW, queuef_push(&queue, 1.0f));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t queuef_pop(struct Queuef *queue, float32_t *data);
 */
static void test_queuef_pop(void)
{
    struct Queuef queue;
    float32_t     buffer[5];
    float32_t     data;

    /* Normal case */
    queuef_init(&queue, buffer, 5);
    queuef_push(&queue, 1.0f);
    queuef_push(&queue, 2.0f);
    queuef_push(&queue, 3.0f);
    queuef_push(&queue, 4.0f);
    queuef_push(&queue, 5.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    queuef_push(&queue, 1.0f);
    queuef_push(&queue, 2.0f);
    queuef_push(&queue, 3.0f);
    queuef_push(&queue, 4.0f);
    queuef_push(&queue, 5.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_UNDERFLOW, queuef_pop(&queue, &data));

    /* Get without get data */
    queuef_push(&queue, 1.0f);
    queuef_push(&queue, 2.0f);
    TEST_ASSERT_EQUAL_UINT32(2, queuef_get_size(&queue));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, NULL));
    TEST_ASSERT_EQUAL_UINT32(1, queuef_get_size(&queue));
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);

    /* Minimum queue */
    queuef_init(&queue, buffer, 1);
    queuef_push(&queue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_pop(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_UNDERFLOW, queuef_pop(&queue, &data));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t queuef_peek(const struct Queuef *queue, float32_t *data);
 */
static void test_queuef_peek(void)
{
    struct Queuef queue;
    float32_t     buffer[4];
    float32_t     data;

    /* Normal case */
    queuef_init(&queue, buffer, 4);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_UNDERFLOW, queuef_peek(&queue, &data));

    queuef_push(&queue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_peek(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    queuef_push(&queue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_peek(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    queuef_push(&queue, 3.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_peek(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    queuef_push(&queue, 4.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_peek(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);

    /* Minimum queue */
    queuef_init(&queue, buffer, 1);
    /* Underflow */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_UNDERFLOW, queuef_peek(&queue, &data));

    queuef_push(&queue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_peek(&queue, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test retcode_t queuef_get_data_by_index(const struct Queuef *queue, uint32_t index, float32_t *data);
 */
static void test_queuef_get_data_by_index(void)
{
    struct Queuef queue;
    float32_t     buffer[5];
    float32_t     data;

    /* Normal case */
    queuef_init(&queue, buffer, 5);
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_index(&queue, 0, &data));
    queuef_push(&queue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_index(&queue, 1, &data));
    queuef_push(&queue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);

    /* out of range */
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_index(&queue, 2, &data));

    queuef_push(&queue, 3.0f);
    queuef_push(&queue, 4.0f);
    queuef_push(&queue, 5.0f);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 2, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 3, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 4, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 2, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);

    queuef_push(&queue, 6.0f);
    queuef_push(&queue, 7.0f);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 3, &data));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_index(&queue, 4, &data));
    TEST_ASSERT_EQUAL_FLOAT(7.0f, data);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief retcode_t queuef_get_data_by_reverse_index(const struct Queuef *queue, uint32_t index, float32_t *data);
 */
static void test_queuef_get_data_by_reverse_index(void)
{
    struct Queuef queue;
    float32_t     buffer[5];
    float32_t     data;

    /* Normal case */
    queuef_init(&queue, buffer, 5);
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_reverse_index(&queue, 0, &data));
    queuef_push(&queue, 1.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_reverse_index(&queue, 1, &data));
    queuef_push(&queue, 2.0f);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_reverse_index(&queue, 2, &data));

    queuef_push(&queue, 3.0f);
    queuef_push(&queue, 4.0f);
    queuef_push(&queue, 5.0f);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 2, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 3, &data));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 4, &data));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, data);

    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 2, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_QUEUE_INDEX_OUT_OF_RANGE, queuef_get_data_by_reverse_index(&queue, 3, &data));

    queuef_push(&queue, 6.0f);
    queuef_push(&queue, 7.0f);

    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 0, &data));
    TEST_ASSERT_EQUAL_FLOAT(7.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 1, &data));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 2, &data));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 3, &data));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, data);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, queuef_get_data_by_reverse_index(&queue, 4, &data));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, data);
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief float32_t queuef_get_data_by_index_unsafe(const struct Queuef *queue, uint32_t index);
 */
static void test_queuef_get_data_by_index_unsafe(void)
{
    struct Queuef queue;
    float32_t     buffer[5];

    /* Normal case */
    queuef_init(&queue, buffer, 5);
    queuef_push(&queue, 1.0f);
    queuef_push(&queue, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(1.0f, queuef_get_data_by_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, queuef_get_data_by_index_unsafe(&queue, 1));

    queuef_push(&queue, 3.0f);
    queuef_push(&queue, 4.0f);
    queuef_push(&queue, 5.0f);

    TEST_ASSERT_EQUAL_FLOAT(1.0f, queuef_get_data_by_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, queuef_get_data_by_index_unsafe(&queue, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, queuef_get_data_by_index_unsafe(&queue, 2));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, queuef_get_data_by_index_unsafe(&queue, 3));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, queuef_get_data_by_index_unsafe(&queue, 4));

    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);

    TEST_ASSERT_EQUAL_FLOAT(3.0f, queuef_get_data_by_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, queuef_get_data_by_index_unsafe(&queue, 1));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, queuef_get_data_by_index_unsafe(&queue, 2));

    queuef_push(&queue, 6.0f);
    queuef_push(&queue, 7.0f);

    TEST_ASSERT_EQUAL_FLOAT(3.0f, queuef_get_data_by_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, queuef_get_data_by_index_unsafe(&queue, 1));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, queuef_get_data_by_index_unsafe(&queue, 2));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, queuef_get_data_by_index_unsafe(&queue, 3));
    TEST_ASSERT_EQUAL_FLOAT(7.0f, queuef_get_data_by_index_unsafe(&queue, 4));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief float32_t queuef_get_data_by_reverse_index_unsafe(const struct Queuef *queue, uint32_t index);
 */
static void test_queuef_get_data_by_reverse_index_unsafe(void)
{
    struct Queuef queue;
    float32_t     buffer[5];

    /* Normal case */
    queuef_init(&queue, buffer, 5);
    queuef_push(&queue, 1.0f);
    queuef_push(&queue, 2.0f);
    TEST_ASSERT_EQUAL_FLOAT(2.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 1));

    queuef_push(&queue, 3.0f);
    queuef_push(&queue, 4.0f);
    queuef_push(&queue, 5.0f);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 2));
    TEST_ASSERT_EQUAL_FLOAT(2.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 3));
    TEST_ASSERT_EQUAL_FLOAT(1.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 4));

    queuef_pop(&queue, NULL);
    queuef_pop(&queue, NULL);

    TEST_ASSERT_EQUAL_FLOAT(5.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 1));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 2));

    queuef_push(&queue, 6.0f);
    queuef_push(&queue, 7.0f);

    TEST_ASSERT_EQUAL_FLOAT(7.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 0));
    TEST_ASSERT_EQUAL_FLOAT(6.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 1));
    TEST_ASSERT_EQUAL_FLOAT(5.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 2));
    TEST_ASSERT_EQUAL_FLOAT(4.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 3));
    TEST_ASSERT_EQUAL_FLOAT(3.0f, queuef_get_data_by_reverse_index_unsafe(&queue, 4));
}

// TODO test is_full, is_empty, get_capacity, get_size

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_queuef_init);
    RUN_TEST(test_queuef_push);
    RUN_TEST(test_queuef_pop);
    RUN_TEST(test_queuef_peek);
    RUN_TEST(test_queuef_get_data_by_index);
    RUN_TEST(test_queuef_get_data_by_reverse_index);
    RUN_TEST(test_queuef_get_data_by_index_unsafe);
    RUN_TEST(test_queuef_get_data_by_reverse_index_unsafe);
    return UNITY_END();
}
