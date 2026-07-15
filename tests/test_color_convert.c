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

static void test_rgb2hsl(void)
{
    static const struct {
        rgb_t source;
        hsl_t expected;
    } cases[] = {
        { {  0,   0,   0}, {0.0f, 0.0f, 0.000f} },
        { {127, 127, 127}, {0.0f, 0.0f, 0.498f} },
        { {255, 255, 255}, {0.0f, 0.0f, 1.000f} },

        { {255,   0,   0}, {  0.0f, 1.0f, 0.5f} },
        { {  0, 255,   0}, {120.0f, 1.0f, 0.5f} },
        { {  0,   0, 255}, {240.0f, 1.0f, 0.5f} },

        { {255, 255,   0}, { 60.0f, 1.0f, 0.5f} },
        { {  0, 255, 255}, {180.0f, 1.0f, 0.5f} },
        { {255,   0, 255}, {300.0f, 1.0f, 0.5f} },

        { { 59, 126, 200}, {211.5f, 0.562f, 0.508f} },
        { { 99,  61, 154}, {264.5f, 0.433f, 0.422f} },
        { {188,  52,  11}, { 13.9f, 0.889f, 0.390f} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        hsl_t actual;

        rgb2hsl(&cases[i].source, &actual);

        TEST_ASSERT_FLOAT_WITHIN(0.1f, cases[i].expected.h, actual.h);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.s, actual.s);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.l, actual.l);
    }
}

static void test_rgb2hsv(void)
{
    static const struct {
        rgb_t source;
        hsv_t expected;
    } cases[] = {
        { {  0,   0,   0}, {0.0f, 0.0f, 0.000f} },
        { {127, 127, 127}, {0.0f, 0.0f, 0.498f} },
        { {255, 255, 255}, {0.0f, 0.0f, 1.000f} },

        { {255,   0,   0}, {  0.0f, 1.0f, 1.0f} },
        { {  0, 255,   0}, {120.0f, 1.0f, 1.0f} },
        { {  0,   0, 255}, {240.0f, 1.0f, 1.0f} },

        { {255, 255,   0}, { 60.0f, 1.0f, 1.0f} },
        { {  0, 255, 255}, {180.0f, 1.0f, 1.0f} },
        { {255,   0, 255}, {300.0f, 1.0f, 1.0f} },

        { { 59, 126, 200}, {211.5f, 0.705f, 0.784f} },
        { { 99,  61, 154}, {264.5f, 0.604f, 0.604f} },
        { {188,  52,  11}, { 13.9f, 0.941f, 0.737f} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        hsv_t actual;

        rgb2hsv(&cases[i].source, &actual);

        TEST_ASSERT_FLOAT_WITHIN(0.1f, cases[i].expected.h, actual.h);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.s, actual.s);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.v, actual.v);
    }
}

static void test_rgb2cmyk(void)
{
    static const struct {
        rgb_t source;
        cmyk_t expected;
    } cases[] = {
        { {  0,   0,   0}, {0.0f, 0.0f, 0.0f, 1.000f} },
        { {127, 127, 127}, {0.0f, 0.0f, 0.0f, 0.502f} },
        { {255, 255, 255}, {0.0f, 0.0f, 0.0f, 0.000f} },

        { {255,   0,   0}, {0.0f, 1.0f, 1.0f, 0.0f} },
        { {  0, 255,   0}, {1.0f, 0.0f, 1.0f, 0.0f} },
        { {  0,   0, 255}, {1.0f, 1.0f, 0.0f, 0.0f} },

        { {255, 255,   0}, {0.0f, 0.0f, 1.0f, 0.0f} },
        { {  0, 255, 255}, {1.0f, 0.0f, 0.0f, 0.0f} },
        { {255,   0, 255}, {0.0f, 1.0f, 0.0f, 0.0f} },

        { { 59, 126, 200}, {0.705f, 0.370f, 0.000f, 0.215f} },
        { { 99,  61, 154}, {0.357f, 0.604f, 0.000f, 0.396f} },
        { {188,  52,  11}, {0.000f, 0.723f, 0.941f, 0.263f} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        cmyk_t actual;

        rgb2cmyk(&cases[i].source, &actual);

        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.c, actual.c);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.m, actual.m);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.y, actual.y);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.k, actual.k);
    }
}

static void test_rgb2rgba(void)
{
    const rgb_t source = {44, 96, 238};
    const rgba_t expected = {44, 96, 238, 255};

    rgba_t actual;
    rgb2rgba(&source, &actual);

    TEST_ASSERT_EQUAL(expected.r, actual.r);
    TEST_ASSERT_EQUAL(expected.g, actual.g);
    TEST_ASSERT_EQUAL(expected.b, actual.b);
    TEST_ASSERT_EQUAL(expected.a, actual.a);
}

static void test_rgb2hex(void)
{
    const rgb_t source = {0xDB, 0x29, 0x8A};
    const int expected = 0xDB298A;

    int actual;
    rgb2hex(&source, &actual);

    TEST_ASSERT_EQUAL(expected, actual);
}

static void test_hsl2rgb(void)
{
    static const struct {
        hsl_t source;
        rgb_t expected;
    } cases[] = {
        { {0.0f, 0.0f, 0.000f}, {  0,   0,   0} },
        { {0.0f, 0.0f, 0.498f}, {127, 127, 127} },
        { {0.0f, 0.0f, 1.000f}, {255, 255, 255} },

        { {  0.0f, 1.0f, 0.5f}, {255,   0,   0} },
        { {120.0f, 1.0f, 0.5f}, {  0, 255,   0} },
        { {240.0f, 1.0f, 0.5f}, {  0,   0, 255} },

        { { 60.0f, 1.0f, 0.5f}, {255, 255,   0} },
        { {180.0f, 1.0f, 0.5f}, {  0, 255, 255} },
        { {300.0f, 1.0f, 0.5f}, {255,   0, 255} },

        { {211.5f, 0.562f, 0.508f}, { 59, 126, 200} },
        { {264.5f, 0.433f, 0.422f}, { 99,  61, 154} },
        { { 13.9f, 0.889f, 0.390f}, {188,  52,  11} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        rgb_t actual;

        hsl2rgb(&cases[i].source, &actual);

        TEST_ASSERT_EQUAL(cases[i].expected.r, actual.r);
        TEST_ASSERT_EQUAL(cases[i].expected.g, actual.g);
        TEST_ASSERT_EQUAL(cases[i].expected.b, actual.b);
    }
}

static void test_hsv2rgb(void)
{
    static const struct {
        hsv_t source;
        rgb_t expected;
    } cases[] = {
        { {0.0f, 0.0f, 0.000f}, {  0,   0,   0} },
        { {0.0f, 0.0f, 0.498f}, {127, 127, 127} },
        { {0.0f, 0.0f, 1.000f}, {255, 255, 255} },

        { {  0.0f, 1.0f, 1.0f}, {255,   0,   0} },
        { {120.0f, 1.0f, 1.0f}, {  0, 255,   0} },
        { {240.0f, 1.0f, 1.0f}, {  0,   0, 255} },

        { { 60.0f, 1.0f, 1.0f}, {255, 255,   0} },
        { {180.0f, 1.0f, 1.0f}, {  0, 255, 255} },
        { {300.0f, 1.0f, 1.0f}, {255,   0, 255} },

        { {211.5f, 0.705f, 0.784f}, { 59, 126, 200} },
        { {264.5f, 0.604f, 0.604f}, { 99,  61, 154} },
        { { 13.9f, 0.941f, 0.737f}, {188,  52,  11} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        rgb_t actual;

        hsv2rgb(&cases[i].source, &actual);

        TEST_ASSERT_EQUAL(cases[i].expected.r, actual.r);
        TEST_ASSERT_EQUAL(cases[i].expected.g, actual.g);
        TEST_ASSERT_EQUAL(cases[i].expected.b, actual.b);
    }
}

static void test_cmyk2rgb(void)
{
    static const struct {
        cmyk_t source;
        rgb_t expected;
    } cases[] = {
        { {0.0f, 0.0f, 0.0f, 1.000f}, {  0,   0,   0} },
        { {0.0f, 0.0f, 0.0f, 0.502f}, {127, 127, 127} },
        { {0.0f, 0.0f, 0.0f, 0.000f}, {255, 255, 255} },

        { {0.0f, 1.0f, 1.0f, 0.0f}, {255,   0,   0} },
        { {1.0f, 0.0f, 1.0f, 0.0f}, {  0, 255,   0} },
        { {1.0f, 1.0f, 0.0f, 0.0f}, {  0,   0, 255} },

        { {0.0f, 0.0f, 1.0f, 0.0f}, {255, 255,   0} },
        { {1.0f, 0.0f, 0.0f, 0.0f}, {  0, 255, 255} },
        { {0.0f, 1.0f, 0.0f, 0.0f}, {255,   0, 255} },

        { {0.705f, 0.370f, 0.000f, 0.215f}, { 59, 126, 200} },
        { {0.357f, 0.604f, 0.000f, 0.396f}, { 99,  61, 154} },
        { {0.000f, 0.723f, 0.941f, 0.263f}, {188,  52,  11} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        rgb_t actual;

        cmyk2rgb(&cases[i].source, &actual);

        TEST_ASSERT_EQUAL(cases[i].expected.r, actual.r);
        TEST_ASSERT_EQUAL(cases[i].expected.g, actual.g);
        TEST_ASSERT_EQUAL(cases[i].expected.b, actual.b);
    }
}

static void test_rgba2rgb(void)
{
    const rgba_t source = {78, 14, 32, 50};
    const rgb_t expected = {78, 14, 32};

    rgb_t actual;
    rgba2rgb(&source, &actual);

    TEST_ASSERT_EQUAL(expected.r, actual.r);
    TEST_ASSERT_EQUAL(expected.g, actual.g);
    TEST_ASSERT_EQUAL(expected.b, actual.b);
}

static void test_hex2rgb(void)
{
    const int source = 0x14E97C;
    const rgb_t expected = {0x14, 0xE9, 0x7C};

    rgb_t actual;
    hex2rgb(&source, &actual);

    TEST_ASSERT_EQUAL(expected.r, actual.r);
    TEST_ASSERT_EQUAL(expected.g, actual.g);
    TEST_ASSERT_EQUAL(expected.b, actual.b);
}

static void test_hsl2hsv(void)
{
    static const struct {
        hsl_t source;
        hsv_t expected;
    } cases[] = {
        { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {0.0f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.5f} },
        { {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },

        { {  0.0f, 1.0f, 0.5f}, {  0.0f, 1.0f, 1.0f} },
        { {120.0f, 1.0f, 0.5f}, {120.0f, 1.0f, 1.0f} },
        { {240.0f, 1.0f, 0.5f}, {240.0f, 1.0f, 1.0f} },

        { {211.5f, 0.562f, 0.508f}, {211.5f, 0.705f, 0.785f} },
        { {264.5f, 0.433f, 0.422f}, {264.5f, 0.604f, 0.605f} },
        { { 13.9f, 0.889f, 0.390f}, { 13.9f, 0.941f, 0.737f} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        hsv_t actual;

        hsl2hsv(&cases[i].source, &actual);

        TEST_ASSERT_FLOAT_WITHIN(0.1f, cases[i].expected.h, actual.h);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.s, actual.s);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.v, actual.v);
    }
}

static void test_hsv2hsl(void)
{
    static const struct {
        hsv_t source;
        hsl_t expected;
    } cases[] = {
        { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} },
        { {0.0f, 0.0f, 0.5f}, {0.0f, 0.0f, 0.5f} },
        { {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f} },

        { {  0.0f, 1.0f, 1.0f}, {  0.0f, 1.0f, 0.5f} },
        { {120.0f, 1.0f, 1.0f}, {120.0f, 1.0f, 0.5f} },
        { {240.0f, 1.0f, 1.0f}, {240.0f, 1.0f, 0.5f} },

        { {211.5f, 0.705f, 0.785f}, {211.5f, 0.562f, 0.508f} },
        { {264.5f, 0.604f, 0.605f}, {264.5f, 0.433f, 0.422f} },
        { { 13.9f, 0.941f, 0.737f}, { 13.9f, 0.889f, 0.390f} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        hsl_t actual;

        hsv2hsl(&cases[i].source, &actual);

        TEST_ASSERT_FLOAT_WITHIN(0.1f, cases[i].expected.h, actual.h);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.s, actual.s);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, cases[i].expected.l, actual.l);
    }
}

static void test_rgb_invert(void)
{
    const rgb_t source = {0x85, 0xDF, 0x64};
    const rgb_t expected = {0x7A, 0x20, 0x9B};

    rgb_t actual = source;
    rgb_invert(&actual);

    TEST_ASSERT_EQUAL(expected.r, actual.r);
    TEST_ASSERT_EQUAL(expected.g, actual.g);
    TEST_ASSERT_EQUAL(expected.b, actual.b);
}

static void test_rgb_blend(void)
{
    static const struct {
        rgb_t background;
        rgba_t foreground;
        rgb_t expected_blend;
    } cases[] = {
        { {255,   0,   0}, {0,   0, 255, 255}, {  0,   0, 255} },
        { {255, 255,   0}, {0,   0, 255, 127}, {128, 128, 127} },
        { {255,   0, 255}, {0, 255,   0,   0}, {255,   0, 255} },

        { {180,  50,  20}, { 10, 240, 180, 192}, { 52, 193, 140} },
        { { 65,  70, 109}, { 29, 248,   5,  63}, { 56, 114,  83} },
        { { 30, 100, 200}, {220,  40,  60,  64}, { 78,  85, 165} },
    };

    size_t i;

    for (i = 0; i < ARRAY_SIZE(cases); i++) {
        rgb_t actual_blend = cases[i].background;

        rgb_blend(&actual_blend, &cases[i].foreground);

        TEST_ASSERT_EQUAL(cases[i].expected_blend.r, actual_blend.r);
        TEST_ASSERT_EQUAL(cases[i].expected_blend.g, actual_blend.g);
        TEST_ASSERT_EQUAL(cases[i].expected_blend.b, actual_blend.b);
    }
}

static void test_hex_websafe(void)
{
    const int source = 0x74A026;
    const int expected = 0x669933;

    int actual = source;
    hex_websafe(&actual);

    TEST_ASSERT_EQUAL(expected, actual);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_hsl_valid);
    RUN_TEST(test_hsv_valid);
    RUN_TEST(test_cmyk_valid);

    RUN_TEST(test_rgb2hsl);
    RUN_TEST(test_rgb2hsv);
    RUN_TEST(test_rgb2cmyk);
    RUN_TEST(test_rgb2rgba);
    RUN_TEST(test_rgb2hex);

    RUN_TEST(test_hsl2rgb);
    RUN_TEST(test_hsv2rgb);
    RUN_TEST(test_cmyk2rgb);
    RUN_TEST(test_rgba2rgb);
    RUN_TEST(test_hex2rgb);

    RUN_TEST(test_hsl2hsv);
    RUN_TEST(test_hsv2hsl);

    RUN_TEST(test_rgb_invert);
    RUN_TEST(test_rgb_blend);

    RUN_TEST(test_hex_websafe);

    return UNITY_END();
}
