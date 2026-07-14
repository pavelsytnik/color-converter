/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2024-2026 Pavlo Sytnyk.                                 *
 * Licensed under the MIT License. See LICENSE for license information.  *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**
 * @file color_convert.h
 * @brief A tiny header-only library for color conversion and manipulation.
 *
 * Define `COLOR_CONVERT_IMPLEMENTATION` in exactly one C/C++ source file
 * before including this header to generate the library implementation.
 *
 * To generate a static implementation, define `COLOR_CONVERT_STATIC` together
 * with `COLOR_CONVERT_IMPLEMENTATION`.
 *
 * `COLOR_CONVERT_API` may be defined before including this header to customize
 * the linkage specifier used for API functions.
 *
 * Examples:
 *
 * @code
 * #define COLOR_CONVERT_IMPLEMENTATION
 * #include "color_convert.h"
 * @endcode
 *
 * @code
 * #define COLOR_CONVERT_STATIC
 * #define COLOR_CONVERT_IMPLEMENTATION
 * #include "color_convert.h"
 * @endcode
 *
 * @code
 * #define COLOR_CONVERT_API __declspec(dllexport)
 * #define COLOR_CONVERT_IMPLEMENTATION
 * #include "color_convert.h"
 * @endcode
 */

#ifndef COLOR_CONVERT_H
#define COLOR_CONVERT_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef COLOR_CONVERT_API
# ifdef COLOR_CONVERT_STATIC
#  define COLOR_CONVERT_API static
# else
#  define COLOR_CONVERT_API extern
# endif
#endif

/**
 * HSL color format.
 */
typedef struct hsl {
    float h; /**< Hue         [0, 360). */
    float s; /**< Saturation  [0, 1].   */
    float l; /**< Lightness   [0, 1].   */
} hsl_t;

/**
 * HSV color format.
 */
typedef struct hsv {
    float h; /**< Hue         [0, 360). */
    float s; /**< Saturation  [0, 1].   */
    float v; /**< Value       [0, 1].   */
} hsv_t;

/**
 * 8-bit sRGB color format.
 */
typedef struct rgb {
    unsigned char r; /**< Red    [0, 255]. */
    unsigned char g; /**< Green  [0, 255]. */
    unsigned char b; /**< Blue   [0, 255]. */
} rgb_t;

/**
 * 8-bit sRGB color format with alpha.
 */
typedef struct rgba {
    unsigned char r; /**< Red    [0, 255]. */
    unsigned char g; /**< Green  [0, 255]. */
    unsigned char b; /**< Blue   [0, 255]. */
    unsigned char a; /**< Alpha  [0, 255]. */
} rgba_t;

/**
 * CMYK color format.
 */
typedef struct cmyk {
    float c; /**< Cyan       [0, 1]. */
    float m; /**< Magenta    [0, 1]. */
    float y; /**< Yellow     [0, 1]. */
    float k; /**< Black/Key  [0, 1]. */
} cmyk_t;

/**
 * @brief Check whether an HSL color is valid.
 *
 * @param color An HSL color.
 *
 * @return Non-zero if valid, zero otherwise.
 */
COLOR_CONVERT_API int hsl_valid(const struct hsl *color);

/**
 * @brief Check whether an HSV color is valid.
 *
 * @param color An HSV color.
 *
 * @return Non-zero if valid, zero otherwise.
 */
COLOR_CONVERT_API int hsv_valid(const struct hsv *color);

/**
 * @brief Check whether a CMYK color is valid.
 *
 * @param color A CMYK color.
 *
 * @return Non-zero if valid, zero otherwise.
 */
COLOR_CONVERT_API int cmyk_valid(const struct cmyk *color);

/**
 * @brief Convert an RGB color to an HSL one.
 *
 * @param[in]  in  An RGB color.
 * @param[out] out An HSL color.
 */
COLOR_CONVERT_API void rgb2hsl(const struct rgb *in, struct hsl *out);

/**
 * @brief Convert an RGB color to an HSV one.
 *
 * @param[in]  in  An RGB color.
 * @param[out] out An HSV color.
 */
COLOR_CONVERT_API void rgb2hsv(const struct rgb *in, struct hsv *out);

/**
 * @brief Convert an RGB color to a CMYK one.
 *
 * @param[in]  in  An RGB color.
 * @param[out] out A CMYK color.
 */
COLOR_CONVERT_API void rgb2cmyk(const struct rgb *in, struct cmyk *out);

/**
 * @brief Convert an RGB color to an RGBA one.
 *
 * @param[in]  in  An RGB color.
 * @param[out] out An RGBA color.
 */
COLOR_CONVERT_API void rgb2rgba(const struct rgb *in, struct rgba *out);

/**
 * @brief Convert an RGB color to a hexadecimal one.
 *
 * @param[in]  in  An RGB color.
 * @param[out] out A hexadecimal color.
 */
COLOR_CONVERT_API void rgb2hex(const struct rgb *in, int *out);

/**
 * @brief Convert an HSL color to an RGB one.
 *
 * @param[in]  in  An HSL color.
 * @param[out] out An RGB color.
 */
COLOR_CONVERT_API void hsl2rgb(const struct hsl *in, struct rgb *out);

/**
 * @brief Convert an HSV color to an RGB one.
 *
 * @param[in]  in  An HSV color.
 * @param[out] out An RGB color.
 */
COLOR_CONVERT_API void hsv2rgb(const struct hsv *in, struct rgb *out);

/**
 * @brief Convert a CMYK color to an RGB one.
 *
 * @param[in]  in  A CMYK color.
 * @param[out] out An RGB color.
 */
COLOR_CONVERT_API void cmyk2rgb(const struct cmyk *in, struct rgb *out);

/**
 * @brief Convert an RGBA color to an RGB one.
 *
 * @param[in]  in  An RGBA color.
 * @param[out] out An RGB color.
 */
COLOR_CONVERT_API void rgba2rgb(const struct rgba *in, struct rgb *out);

/**
 * @brief Convert a hexadecimal color to an RGB one.
 *
 * @param[in]  in  A hexadecimal color.
 * @param[out] out An RGB color.
 */
COLOR_CONVERT_API void hex2rgb(const int *in, struct rgb *out);

/**
 * @brief Convert an HSL color to an HSV one.
 *
 * @param[in]  in  An HSL color.
 * @param[out] out An HSV color.
 */
COLOR_CONVERT_API void hsl2hsv(const struct hsl *in, struct hsv *out);

/**
 * @brief Convert an HSV color to an HSL one.
 *
 * @param[in]  in  An HSV color.
 * @param[out] out An HSL color.
 */
COLOR_CONVERT_API void hsv2hsl(const struct hsv *in, struct hsl *out);

/**
 * @brief Invert an RGB color.
 *
 * @param[in,out] color An RGB color.
 */
COLOR_CONVERT_API void rgb_invert(struct rgb *color);

/**
 * @brief Blend an RGBA color over an RGB color.
 *
 * The blended result is stored in `dst`.
 * The alpha channel of `src` determines the blend factor.
 *
 * @param[in,out] dst The background RGB color.
 * @param[in]     src The foreground RGBA color.
 */
COLOR_CONVERT_API void rgb_blend(struct rgb *dst, const struct rgba *src);

/**
 * @brief Make a hexadecimal color web-safe.
 *
 * @deprecated This function will be deleted in version 2.0.
 *
 * @param[in,out] color A hexadecimal color.
 */
COLOR_CONVERT_API void hex_websafe(int *color);

#ifdef __cplusplus
}
#endif

#ifdef COLOR_CONVERT_IMPLEMENTATION

#define max_(x, y) ((x) > (y) ? (x) : (y))
#define min_(x, y) ((x) < (y) ? (x) : (y))

#define trunc_(x) ((float)(int)(x))
#define abs_(x) ((x) >= 0 ? (x) : -(x))
#define fmod_(x, y) ((x) - trunc_((x) / (y)) * (y))

#define rgb_set_(rgb, r_, g_, b_) \
do {                              \
    (rgb)->r = (r_);              \
    (rgb)->g = (g_);              \
    (rgb)->b = (b_);              \
} while (0)

COLOR_CONVERT_API int hsl_valid(const struct hsl *color)
{
    return (color->h >= 0.f && color->h < 360.f) &&
           (color->s >= 0.f && color->s <= 1.f) &&
           (color->l >= 0.f && color->l <= 1.f);
}

COLOR_CONVERT_API int hsv_valid(const struct hsv *color)
{
    return (color->h >= 0.f && color->h < 360.f) &&
           (color->s >= 0.f && color->s <= 1.f) &&
           (color->v >= 0.f && color->v <= 1.f);
}

COLOR_CONVERT_API int cmyk_valid(const struct cmyk *color)
{
    return (color->c >= 0.f && color->c <= 1.f) &&
           (color->m >= 0.f && color->m <= 1.f) &&
           (color->y >= 0.f && color->y <= 1.f) &&
           (color->k >= 0.f && color->k <= 1.f);
}

COLOR_CONVERT_API void rgb2hsl(const struct rgb *in, struct hsl *out)
{
    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    float cmax = max_(max_(r, g), b);
    float cmin = min_(min_(r, g), b);

    float d = cmax - cmin;

    out->l = (cmax + cmin) / 2.f;

    if (d == 0.f) {
        out->h = 0.f;
        out->s = 0.f;
        return;
    }

    out->s = (out->l > 0.5f)
        ? (d / (2.f - cmax - cmin))
        : (d / (cmax + cmin));

    if (cmax == r) {
        out->h = (g - b) / d + (g < b ? 6.f : 0.f);
    } else if (cmax == g) {
        out->h = (b - r) / d + 2.f;
    } else {
        out->h = (r - g) / d + 4.f;
    }

    out->h *= 60.f;
}

COLOR_CONVERT_API void rgb2hsv(const struct rgb *in, struct hsv *out)
{
    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    float cmax = max_(max_(r, g), b);
    float cmin = min_(min_(r, g), b);

    float d = cmax - cmin;

    out->v = cmax;

    if (d == 0.f) {
        out->h = 0.f;
        out->s = 0.f;
        return;
    }

    out->s = (cmax == 0.f) ? 0.f : (d / cmax);

    if (cmax == r) {
        out->h = (g - b) / d + (g < b ? 6.f : 0.f);
    } else if (cmax == g) {
        out->h = (b - r) / d + 2.f;
    } else {
        out->h = (r - g) / d + 4.f;
    }

    out->h *= 60.f;
}

COLOR_CONVERT_API void rgb2cmyk(const struct rgb *in, struct cmyk *out)
{
    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    out->k = 1.f - max_(max_(r, g), b);

    if (out->k == 1.f) {
        out->c = 0.f;
        out->m = 0.f;
        out->y = 0.f;
        return;
    }

    out->c = (1.f - r - out->k) / (1.f - out->k);
    out->m = (1.f - g - out->k) / (1.f - out->k);
    out->y = (1.f - b - out->k) / (1.f - out->k);
}

COLOR_CONVERT_API void rgb2rgba(const struct rgb *in, struct rgba *out)
{
    out->r = in->r;
    out->g = in->g;
    out->b = in->b;
    out->a = 0xFF;
}

COLOR_CONVERT_API void rgb2hex(const struct rgb *in, int *out)
{
    *out = (unsigned)in->r << 16
         | (unsigned)in->g << 8
         | (unsigned)in->b;
}

COLOR_CONVERT_API void hsl2rgb(const struct hsl *in, struct rgb *out)
{
    float h = in->h / 60.f;
    float s = in->s;
    float l = in->l;

    float c = (1.f - abs_(2.f * l - 1.f)) * s;
    float x = c * (1.f - abs_(fmod_(h, 2.f) - 1.f));
    float m = l - c / 2.f;

    struct rgb rgb;

    if (h >= 0.f && h < 1.f) {
        rgb_set_(&rgb, c, x, 0);
    } else if (h >= 1.f && h < 2.f) {
        rgb_set_(&rgb, x, c, 0);
    } else if (h >= 2.f && h < 3.f) {
        rgb_set_(&rgb, 0, c, x);
    } else if (h >= 3.f && h < 4.f) {
        rgb_set_(&rgb, 0, x, c);
    } else if (h >= 4.f && h < 5.f) {
        rgb_set_(&rgb, x, 0, c);
    } else {
        rgb_set_(&rgb, c, 0, x);
    }

    out->r = (unsigned char)((rgb.r + m) * 255.f);
    out->g = (unsigned char)((rgb.g + m) * 255.f);
    out->b = (unsigned char)((rgb.b + m) * 255.f);
}

COLOR_CONVERT_API void hsv2rgb(const struct hsv *in, struct rgb *out)
{
    float h = in->h / 60.f;
    float s = in->s;
    float v = in->v;

    float c = v * s;
    float x = c * (1.f - abs_(fmod_(h, 2.f) - 1.f));
    float m = v - c;

    struct rgb rgb;

    if (h >= 0.f && h < 1.f) {
        rgb_set_(&rgb, c, x, 0);
    } else if (h >= 1.f && h < 2.f) {
        rgb_set_(&rgb, x, c, 0);
    } else if (h >= 2.f && h < 3.f) {
        rgb_set_(&rgb, 0, c, x);
    } else if (h >= 3.f && h < 4.f) {
        rgb_set_(&rgb, 0, x, c);
    } else if (h >= 4.f && h < 5.f) {
        rgb_set_(&rgb, x, 0, c);
    } else {
        rgb_set_(&rgb, c, 0, x);
    }

    out->r = (unsigned char)((rgb.r + m) * 255.f);
    out->g = (unsigned char)((rgb.g + m) * 255.f);
    out->b = (unsigned char)((rgb.b + m) * 255.f);
}

COLOR_CONVERT_API void cmyk2rgb(const struct cmyk *in, struct rgb *out)
{
    out->r = (unsigned char)(255.f * (1.f - in->c) * (1.f - in->k));
    out->g = (unsigned char)(255.f * (1.f - in->m) * (1.f - in->k));
    out->b = (unsigned char)(255.f * (1.f - in->y) * (1.f - in->k));
}

COLOR_CONVERT_API void rgba2rgb(const struct rgba *in, struct rgb *out)
{
    out->r = in->r;
    out->g = in->g;
    out->b = in->b;
}

COLOR_CONVERT_API void hex2rgb(const int *in, struct rgb *out)
{
    unsigned value = (unsigned)(*in);

    out->r = (value >> 16) & 0xFF;
    out->g = (value >> 8) & 0xFF;
    out->b = value & 0xFF;
}

#define channel_websafe_(c)          \
(                                    \
    (unsigned)( ((c) <= 0x19) ? 0x00 \
              : ((c) <= 0x4C) ? 0x33 \
              : ((c) <= 0x7F) ? 0x66 \
              : ((c) <= 0xB2) ? 0x99 \
              : ((c) <= 0xE5) ? 0xCC \
              :                 0xFF \
              )                      \
)

COLOR_CONVERT_API void hex_websafe(int *color)
{
    unsigned value = (unsigned)(*color);

    unsigned char r = (value >> 16) & 0xFF;
    unsigned char g = (value >> 8) & 0xFF;
    unsigned char b = value & 0xFF;

    *color = (channel_websafe_(r) << 16)
           | (channel_websafe_(g) << 8)
           | (channel_websafe_(b));
}

#undef channel_websafe_

COLOR_CONVERT_API void hsl2hsv(const struct hsl *in, struct hsv *out)
{
    out->h = in->h;

    out->v = in->l + in->s * min_(in->l, 1.f - in->l);

    out->s = (out->v > 0.f)
        ? 2.f * (1.f - in->l / out->v)
        : 0.f;
}

COLOR_CONVERT_API void hsv2hsl(const struct hsv *in, struct hsl *out)
{
    out->h = in->h;

    out->l = in->v * (1.f - in->s / 2.f);

    out->s = (out->l > 0.f && out->l < 1.f)
        ? (in->v - out->l) / min_(out->l, 1.f - out->l)
        : 0.f;
}

COLOR_CONVERT_API void rgb_invert(struct rgb *color)
{
    color->r = ~color->r;
    color->g = ~color->g;
    color->b = ~color->b;
}

COLOR_CONVERT_API void rgb_blend(struct rgb *dst, const struct rgba *src)
{
    float a = src->a / 255.f;

    dst->r = (unsigned char)(dst->r * (1.f - a) + src->r * a);
    dst->g = (unsigned char)(dst->g * (1.f - a) + src->g * a);
    dst->b = (unsigned char)(dst->b * (1.f - a) + src->b * a);
}

#undef rgb_set_
#undef fmod_
#undef abs_
#undef trunc_
#undef min_
#undef max_

#endif /* COLOR_CONVERT_IMPLEMENTATION */
#endif /* COLOR_CONVERT_H */
