#ifndef COLOR_CONVERT_H
#define COLOR_CONVERT_H

typedef struct hsl {
    float h;
    float s;
    float l;
} hsl_t;

typedef struct hsv {
    float h;
    float s;
    float v;
} hsv_t;

typedef struct rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb_t;

struct rgb rgb(unsigned char r, unsigned char g, unsigned char b);
struct hsl hsl(float hue, float saturation, float lightness);
struct hsv hsv(float hue, float saturation, float value);

int hsl_valid(const struct hsl *);
int hsv_valid(const struct hsv *);

struct rgb hsl2rgb(const struct hsl *);
struct rgb hex2rgb(int code);
struct hsl rgb2hsl(const struct rgb *);
struct hsv rgb2hsv(const struct rgb *);

void rgb_invert(struct rgb *);

#ifdef COLOR_CONVERT_IMPLEMENTATION

struct rgb rgb(unsigned char r, unsigned char g, unsigned char b)
{
    struct rgb color = { r, g, b };
    return color;
}

struct hsl hsl(float h, float s, float l)
{
    struct hsl color = { h, s, l };
    return color;
}

struct hsv hsv(float h, float s, float v)
{
    struct hsv color = { h, s, v };
    return color;
}

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

struct rgb hsl2rgb(const struct hsl *in)
{
    struct rgb out;

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

    out.r = (unsigned char) ((r + m) * 255);
    out.g = (unsigned char) ((g + m) * 255);
    out.b = (unsigned char) ((b + m) * 255);

    return out;
}

#undef _RGB
#undef _fmod
#undef _abs
#undef _trunc

struct rgb hex2rgb(int code)
{
    struct rgb out = { code >> 16, code >> 8, code };
    return out;
}

struct hsl rgb2hsl(const struct rgb *in)
{
    struct hsl out;

    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    float cmax = r > (g > b ? g : b) ? r : g > b ? g : b;
    float cmin = r < (g < b ? g : b) ? r : g < b ? g : b;

    out.l = (cmax + cmin) / 2;

    if (cmax == cmin)
        out.h = out.s = 0;
    else {
        float d = cmax - cmin;

        out.s = out.l > 0.5f ? d / (2 - cmax - cmin) : d / (cmax + cmin);

        if (cmax == r)
            out.h = (g - b) / d + (g < b ? 6 : 0);
        else if (cmax == g)
            out.h = (b - r) / d + 2;
        else if (cmax == b)
            out.h = (r - g) / d + 4;
        out.h *= 60;
    }

    return out;
}

struct hsv rgb2hsv(const struct rgb *in)
{
    struct hsv out;

    float r = in->r / 255.f;
    float g = in->g / 255.f;
    float b = in->b / 255.f;

    float cmax = r > (g > b ? g : b) ? r : g > b ? g : b;
    float cmin = r < (g < b ? g : b) ? r : g < b ? g : b;
    float d = cmax - cmin;

    out.v = cmax;

    if (d == 0)
        out.h = 0;
    else {
        if (cmax == r)
            out.h = (g - b) / d + (g < b ? 6 : 0);
        else if (cmax == g)
            out.h = (b - r) / d + 2;
        else if (cmax == b)
            out.h = (r - g) / d + 4;
        out.h *= 60;
    }

    if (cmax == 0)
        out.s = 0;
    else
        out.s = d / out.v;

    return out;
}

void rgb_invert(struct rgb *color)
{
    color->r = ~color->r;
    color->g = ~color->g;
    color->b = ~color->b;
}

#endif /* COLOR_CONVERT_IMPLEMENTATION */
#endif /* COLOR_CONVERT_H */
