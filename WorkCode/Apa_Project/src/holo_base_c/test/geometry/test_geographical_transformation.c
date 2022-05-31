#include <holo_c/geometry/geographical_transformation.h>
#include <holo_c/core/types.h>
#include <holo_c/core/retcode.h>
#include <unity.h>

static void test_LL2UTM(void)
{
    retcode_t rc;
    float64_t utm_east;
    float64_t utm_north;
    int zone_id;

    rc = LL2UTM(30.6531625008, 121.1890005577, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(51, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 326474.4650588095, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 3392563.1296714176, utm_north);

    rc = LL2UTM(58.11, 80.98, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(44, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 498821.443344, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 6440957.081531, utm_north);

    rc = LL2UTM(58.11, 5.515320, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(32, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 294711.286866, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 6446259.946195, utm_north);

    rc = LL2UTM(75.11, 5.515320, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(31, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 572128.025935, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 8337410.330767, utm_north);

    rc = LL2UTM(75.11, 15.543175, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(33, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 515579.948664, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 8335951.354783, utm_north);

    rc = LL2UTM(75.11, 25.571031, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(35, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 459015.879022, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 8336373.927453, utm_north);

    rc = LL2UTM(75.11, 35.598886, &utm_north, &utm_east, &zone_id);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_EQUAL_INT32(37, zone_id);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 402493.929340, utm_east);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 8338677.746832, utm_north);
}

static void test_UTM2LL(void)
{
    retcode_t rc;
    float64_t lat;
    float64_t lon;

    rc = UTM2LL(3392563.1296714176, 326474.4650588095, 51, &lat, &lon);
    TEST_ASSERT_EQUAL_INT32(RC_SUCCESS, rc);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 30.6531625008, lat);
    TEST_ASSERT_DOUBLE_WITHIN(0.000001, 121.1890005577, lon);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_LL2UTM);
    RUN_TEST(test_UTM2LL);
    return UNITY_END();
}
