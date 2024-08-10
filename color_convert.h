/************************************************************************
 * Copyright (c) 2024 Pavel Sytník.                                     *
 * Licensed under the MIT License. See LICENSE for license information. *
 ************************************************************************/

/**
 * @file color_convert.h
 * @brief A tiny header-only library for interacting with colors.
 */

#ifndef COLOR_CONVERT_H
#define COLOR_CONVERT_H

/**
 * HSL color format.
 */
typedef struct hsl {
    float h; /**< hue         [0; 360) */
    float s; /**< saturation  [0; 1]   */
    float l; /**< lightness   [0; 1]   */
} hsl_t;

/**
 * HSV color format.
 */
typedef struct hsv {
    float h; /**< hue         [0; 360) */
    float s; /**< saturation  [0; 1]   */
    float v; /**< value       [0; 1]   */
} hsv_t;

/**
 * RGB color format.
 */
typedef struct rgb {
    unsigned char r; /**< red    [0; 255] */
    unsigned char g; /**< green  [0; 255] */
    unsigned char b; /**< blue   [0; 255] */
} rgb_t;

/**
 * RGBA color format.
 */
typedef struct rgba {
    unsigned char r; /**< red    [0; 255] */
    unsigned char g; /**< green  [0; 255] */
    unsigned char b; /**< blue   [0; 255] */
    unsigned char a; /**< alpha  [0; 255] */
} rgba_t;

/**
 * CMYK color format.
 */
typedef struct cmyk {
    float c; /**< cyan    [0; 1] */
    float m; /**< magenta [0; 1] */
    float y; /**< yellow  [0; 1] */
    float k; /**< black   [0; 1] */
} cmyk_t;

/**
 * @brief Check if an HSL structure has correct data.
 *
 * @param color    a pointer to an HSL color
 * @return non-zero if valid, zero otherwise
 */
int hsl_valid(const struct hsl *color);

/**
 * @brief Check if an HSV structure has correct data.
 *
 * @param color a pointer to an HSV color
 * @return non-zero if valid, zero otherwise
 */
int hsv_valid(const struct hsv *color);

/**
 * @brief Check if a CMYK structure has correct data.
 *
 * @param color a pointer to a CMYK color
 * @return non-zero if valid, zero otherwise
 */
int cmyk_valid(const struct cmyk *color);

/**
 * @brief Convert an RGB color to an HSL one.
 *
 * @param[in]  in  a pointer to an RGB color
 * @param[out] out a pointer to an HSL color
 */
void rgb2hsl(const struct rgb *in, struct hsl *out);

/**
 * @brief Convert an RGB color to an HSV one.
 *
 * @param[in]  in  a pointer to an RGB color
 * @param[out] out a pointer to an HSV color
 */
void rgb2hsv(const struct rgb *in, struct hsv *out);

/**
 * @brief Convert an RGB color to a CMYK one.
 *
 * @param[in]  in  a pointer to an RGB color
 * @param[out] out a pointer to a CMYK color
 */
void rgb2cmyk(const struct rgb *in, struct cmyk *out);

/**
 * @brief Convert an RGB color to an RGBA one.
 *
 * @param[in]  in  a pointer to an RGB color
 * @param[out] out a pointer to an RGBA color
 */
void rgb2rgba(const struct rgb *in, struct rgba *out);

/**
 * @brief Convert an RGB color to a HEX one.
 *
 * @param[in]  in  a pointer to an RGB color
 * @param[out] out a pointer to a HEX color
 */
void rgb2hex(const struct rgb *in, int *out);

/**
 * @brief Convert an HSL color to an RGB one.
 *
 * @param[in]  in  a pointer to an HSL color
 * @param[out] out a pointer to an RGB color
 */
void hsl2rgb(const struct hsl *in, struct rgb *out);

/**
 * @brief Convert an HSV color to an RGB one.
 *
 * @param[in]  in  a pointer to an HSV color
 * @param[out] out a pointer to an RGB color
 */
void hsv2rgb(const struct hsv *in, struct rgb *out);

/**
 * @brief Convert a CMYK color to an RGB one.
 *
 * @param[in]  in  a pointer to a CMYK color
 * @param[out] out a pointer to an RGB color
 */
void cmyk2rgb(const struct cmyk *in, struct rgb *out);

/**
 * @brief Convert an RGBA color to an RGB one.
 *
 * @param[in]  in  a pointer to an RGBA color
 * @param[out] out a pointer to an RGB color
 */
void rgba2rgb(const struct rgba *in, struct rgb *out);

/**
 * @brief Convert a HEX color to an RGB one.
 *
 * @param[in]  in  a pointer to a HEX color
 * @param[out] out a pointer to an RGB color
 */
void hex2rgb(const int *in, struct rgb *out);

/**
 * @brief Convert an HSL color to an HSV one.
 *
 * @param[in]  in  a pointer to an HSL color
 * @param[out] out a pointer to an HSV color
 */
void hsl2hsv(const struct hsl *in, struct hsv *out);

/**
 * @brief Convert an HSV color to an HSL one.
 *
 * @param[in]  in  a pointer to an HSV color
 * @param[out] out a pointer to an HSL color
 */
void hsv2hsl(const struct hsv *in, struct hsl *out);

/**
 * @brief Invert an RGB color.
 *
 * @param[in,out] color a pointer to an RGB color
 */
void rgb_invert(struct rgb *color);

/**
 * @brief Blend a solid RGB color with an RGBA color.
 * 
 * The result of the blend is stored back in `dst`.
 * The alpha channel of `src` determines the blend ratio.
 *
 * @param[in,out] dst a pointer to the background for the second parameter
 * @param[in]     src a pointer to an RGBA color which will be blended with
 *                    the first
 */
void rgb_blend(struct rgb *dst, const struct rgba *src);

/**
 * @brief Make a hexadecimal color web-safe.
 *
 * @param[in,out] color a pointer to a hexadecimal color
 */
void hex_websafe(int *color);

#ifdef COLOR_CONVERT_IMPLEMENTATION

#define _max(x, y) ((x) > (y) ? (x) : (y))
#define _min(x, y) ((x) < (y) ? (x) : (y))

int hsl_valid(const struct hsl *color)
{
    if (color->h < 0 || color->h >= 360)
        return 0;
    if (color->s < 0 || color->s > 1)
        return 0;
    if (color->l < 0 || color->l > 1)
        return 0;

    return 1;
}

int hsv_valid(const struct hsv *color)
{
    if (color->h < 0 || color->h >= 360)
        return 0;
    if (color->s < 0 || color->s > 1)
        return 0;
    if (color->v < 0 || color->v > 1)
        return 0;

    return 1;
}

int cmyk_valid(const struct cmyk *color)
{
    if (color->c < 0 || color->c > 1)
        return 0;
    if (color->m < 0 || color->m > 1)
        return 0;
    if (color->y < 0 || color->y > 1)
        return 0;
    if (color->k < 0 || color->k > 1)
        return 0;

    return 1;
}

void rgb2hsl(const struct rgb *in, struct hsl *out)
{
    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    float cmax = _max(_max(r, g), b);
    float cmin = _min(_min(r, g), b);

    out->l = (cmax + cmin) / 2;

    if (cmax == cmin)
        out->h = out->s = 0;
    else {
        float d = cmax - cmin;

        out->s = out->l > 0.5f ? d / (2 - cmax - cmin) : d / (cmax + cmin);

        if (cmax == r)
            out->h = (g - b) / d + (g < b ? 6 : 0);
        else if (cmax == g)
            out->h = (b - r) / d + 2;
        else if (cmax == b)
            out->h = (r - g) / d + 4;
        out->h *= 60;
    }
}

void rgb2hsv(const struct rgb *in, struct hsv *out)
{
    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    float cmax = _max(_max(r, g), b);
    float cmin = _min(_min(r, g), b);
    float d = cmax - cmin;

    out->v = cmax;

    if (d == 0)
        out->h = 0;
    else {
        if (cmax == r)
            out->h = (g - b) / d + (g < b ? 6 : 0);
        else if (cmax == g)
            out->h = (b - r) / d + 2;
        else if (cmax == b)
            out->h = (r - g) / d + 4;
        out->h *= 60;
    }

    if (cmax == 0)
        out->s = 0;
    else
        out->s = d / out->v;
}

void rgb2cmyk(const struct rgb *in, struct cmyk *out)
{
    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    out->k = 1 - _max(_max(r, g), b);
    out->c = (1 - r - out->k) / (1 - out->k);
    out->m = (1 - g - out->k) / (1 - out->k);
    out->y = (1 - b - out->k) / (1 - out->k);
}

void rgb2rgba(const struct rgb *in, struct rgba *out)
{
    out->r = in->r;
    out->g = in->g;
    out->b = in->b;
    out->a = 0xFF;
}

void rgb2hex(const struct rgb *in, int *out)
{
    *out = in->r << 16 | in->g << 8 | in->b;
}

#define _trunc(x) ((float) (int) (x))
#define _abs(x) ((x) >= 0 ? (x) : -(x))
#define _fmod(x, y) ((x) - _trunc((x) / (y)) * (y))

/* Set (r,g,b) defined in hsl2rgb() */
#define _RGB(_r, _g, _b) \
do {                     \
    r = _r;              \
    g = _g;              \
    b = _b;              \
} while (0)

void hsl2rgb(const struct hsl *in, struct rgb *out)
{
    float h = in->h/60, s = in->s, l = in->l;

    float c = (1 - _abs(2*l - 1)) * s;
    float x = c * (1 - _abs(_fmod(h, 2) - 1));
    float m = l - c/2;

    float r, g, b;

    if (h >= 0 && h < 1)
        _RGB(c, x, 0);
    else if (h >= 1 && h < 2)
        _RGB(x, c, 0);
    else if (h >= 2 && h < 3)
        _RGB(0, c, x);
    else if (h >= 3 && h < 4)
        _RGB(0, x, c);
    else if (h >= 4 && h < 5)
        _RGB(x, 0, c);
    else if (h >= 5 && h < 6)
        _RGB(c, 0, x);

    out->r = (unsigned char) ((r + m) * 255);
    out->g = (unsigned char) ((g + m) * 255);
    out->b = (unsigned char) ((b + m) * 255);
}

void hsv2rgb(const struct hsv *in, struct rgb *out)
{
    float h = in->h/60, s = in->s, v = in->v;

    float c = v * s;
    float x = c * (1 - _abs(_fmod(h, 2) - 1));
    float m = v - c;

    float r, g, b;

    if (h >= 0 && h < 1)
        _RGB(c, x, 0);
    else if (h >= 1 && h < 2)
        _RGB(x, c, 0);
    else if (h >= 2 && h < 3)
        _RGB(0, c, x);
    else if (h >= 3 && h < 4)
        _RGB(0, x, c);
    else if (h >= 4 && h < 5)
        _RGB(x, 0, c);
    else if (h >= 5 && h < 6)
        _RGB(c, 0, x);

    out->r = (unsigned char) ((r + m) * 255);
    out->g = (unsigned char) ((g + m) * 255);
    out->b = (unsigned char) ((b + m) * 255);
}

#undef _RGB
#undef _fmod
#undef _abs
#undef _trunc

void cmyk2rgb(const struct cmyk *in, struct rgb *out)
{
    out->r = (unsigned char) (255 * (1 - in->c) * (1 - in->k));
    out->g = (unsigned char) (255 * (1 - in->m) * (1 - in->k));
    out->b = (unsigned char) (255 * (1 - in->y) * (1 - in->k));
}

void rgba2rgb(const struct rgba *in, struct rgb *out)
{
    out->r = in->r;
    out->g = in->g;
    out->b = in->b;
}

void hex2rgb(const int *in, struct rgb *out)
{
    out->r = (unsigned char) (*in >> 16);
    out->g = (unsigned char) (*in >> 8);
    out->b = (unsigned char) (*in);
}

#define _channel_websafe(c) \
    ( (c) <= 0x19 ? 0x00    \
    : (c) <= 0x4C ? 0x33    \
    : (c) <= 0x7F ? 0x66    \
    : (c) <= 0xB2 ? 0x99    \
    : (c) <= 0xE5 ? 0xCC    \
    :               0xFF    )

void hex_websafe(int *color)
{
    int bits;
    for (bits = 16; bits >= 0; bits -= 8) {
        int mask = ~(0xFF << bits);
        unsigned char channel = *color >> bits;
        *color = (*color & mask) | (_channel_websafe(channel) << bits);
    }
}

#undef _channel_websafe

void hsl2hsv(const struct hsl *in, struct hsv *out)
{
    out->h = in->h;
    out->v = in->l + in->s * _min(in->l, 1 - in->l);
    if (out->v == 0)
        out->s = 0;
    else
        out->s = 2 * (1 - in->l / out->v);
}

void hsv2hsl(const struct hsv *in, struct hsl *out)
{
    out->h = in->h;
    out->l = in->v * (1 - in->s / 2);
    if (out->l == 0 || out->l == 1)
        out->s = 0;
    else
        out->s = (in->v - out->l) / _min(out->l, 1 - out->l);
}

void rgb_invert(struct rgb *color)
{
    color->r = ~color->r;
    color->g = ~color->g;
    color->b = ~color->b;
}

void rgb_blend(struct rgb *dst, const struct rgba *src)
{
    float a = src->a / 255.f;

    dst->r = dst->r * (1 - a) + src->r * a;
    dst->g = dst->g * (1 - a) + src->g * a;
    dst->b = dst->b * (1 - a) + src->b * a;
}

#undef _min
#undef _max

#endif /* COLOR_CONVERT_IMPLEMENTATION */
#endif /* COLOR_CONVERT_H */
