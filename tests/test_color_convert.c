#define COLOR_CONVERT_STATIC
#define COLOR_CONVERT_IMPLEMENTATION
#include <color_convert.h>

#include <unity.h>

#include <stddef.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

/* These are defined to prevent compilation errors. */
void setUp(void) {}
void tearDown(void) {}

static void test_hsl_valid(void)
{
    static const struct {
        hsl_t color;
        int expected;
    } cases[] = {
        { {   0.0f,   0.0f,   0.0f}, 1 },
        { { 180.0f,   0.5f,   0.5f}, 1 },
        { {359.99f,   1.0f,   1.0f}, 1 },
        { { -0.01f,   0.5f,   0.5f}, 0 },
        { { 360.0f,   0.5f,   0.5f}, 0 },
        { { 180.0f, -0.01f,   0.5f}, 0 },
        { { 180.0f,  1.01f,   0.5f}, 0 },
        { { 180.0f,   0.5f, -0.01f}, 0 },
        { { 180.0f,   0.5f,  1.01f}, 0 },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        TEST_ASSERT_EQUAL(cases[i].expected, hsl_valid(&cases[i].color));
    }
}

static void test_hsv_valid(void)
{
    static const struct {
        hsv_t color;
        int expected;
    } cases[] = {
        { {   0.0f,   0.0f,   0.0f}, 1 },
        { { 180.0f,   0.5f,   0.5f}, 1 },
        { {359.99f,   1.0f,   1.0f}, 1 },
        { { -0.01f,   0.5f,   0.5f}, 0 },
        { { 360.0f,   0.5f,   0.5f}, 0 },
        { { 180.0f, -0.01f,   0.5f}, 0 },
        { { 180.0f,  1.01f,   0.5f}, 0 },
        { { 180.0f,   0.5f, -0.01f}, 0 },
        { { 180.0f,   0.5f,  1.01f}, 0 },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        TEST_ASSERT_EQUAL(cases[i].expected, hsv_valid(&cases[i].color));
    }
}

static void test_cmyk_valid(void)
{
    static const struct {
        cmyk_t color;
        int expected;
    } cases[] = {
        { {  0.0f,   0.0f,   0.0f,   0.0f}, 1 },
        { {  0.5f,   0.5f,   0.5f,   0.5f}, 1 },
        { {  1.0f,   1.0f,   1.0f,   1.0f}, 1 },
        { {-0.01f,   0.5f,   0.5f,   0.5f}, 0 },
        { { 1.01f,   0.5f,   0.5f,   0.5f}, 0 },
        { {  0.5f, -0.01f,   0.5f,   0.5f}, 0 },
        { {  0.5f,  1.01f,   0.5f,   0.5f}, 0 },
        { {  0.5f,   0.5f, -0.01f,   0.5f}, 0 },
        { {  0.5f,   0.5f,  1.01f,   0.5f}, 0 },
        { {  0.5f,   0.5f,   0.5f, -0.01f}, 0 },
        { {  0.5f,   0.5f,   0.5f,  1.01f}, 0 },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        TEST_ASSERT_EQUAL(cases[i].expected, cmyk_valid(&cases[i].color));
    }
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_hsl_valid);
    RUN_TEST(test_hsv_valid);
    RUN_TEST(test_cmyk_valid);

    return UNITY_END();
}
