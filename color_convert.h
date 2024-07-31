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

struct rgb hsl2rgb(const struct hsl *);
struct rgb hex2rgb(int code);
struct hsl rgb2hsl(const struct rgb *);
struct hsv rgb2hsv(const struct rgb *);

void rgb_invert(struct rgb *);

#ifdef COLOR_CONVERT_IMPLEMENTATION

static float _hue_to_rgb(float p, float q, float t);

struct rgb rgb(unsigned char r, unsigned char g, unsigned char b)
{
    struct rgb color = { r, g, b };
    return color;
}

struct hsl hsl(float h, float s, float l)
{
    struct hsl color = { h/360, s/100, l/100 };
    return color;
}

struct hsv hsv(float h, float s, float v)
{
    struct hsv color = { h/360, s/100, v/100 };
    return color;
}

struct rgb hsl2rgb(const struct hsl *in)
{
    struct rgb out;
    
    if (in->s == 0)
        out.r = out.g = out.b = in->l;
    else {
        float q = in->l < 0.5f ? in->l * (1 + in->s)
                               : in->l + in->s - in->l * in->s;
        float p = 2 * in->l - q;

        out.r = _hue_to_rgb(p, q, in->h + 1/3.f) * 255;
        out.g = _hue_to_rgb(p, q, in->h) * 255;
        out.b = _hue_to_rgb(p, q, in->h - 1/3.f) * 255;
    }

    return out;
}

static float _hue_to_rgb(float p, float q, float t)
{
    if (t < 0)
        t += 1;
    if (t > 1)
        t -= 1;

    if (t < 1/6.f)
        return p + (q - p) * 6 * t;
    if (t < 1/2.f)
        return q;
    if (t < 2/3.f)
        return p + (q - p) * (2/3.f - t) * 6;
    return p;
}

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
        out.h /= 6;
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
        out.h /= 6;
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
