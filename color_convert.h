#ifndef COLOR_CONVERT_H
#define COLOR_CONVERT_H

typedef struct hsl {
    float h;
    float s;
    float l;
} hsl;

typedef struct hsv {
    float h;
    float s;
    float v;
} hsv;

typedef struct rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

struct rgb hsl_to_rgb(float h, float s, float l);
struct rgb hex_to_rgb(int code);
struct hsl rgb_to_hsl(float r, float g, float b);
struct hsv rgb2hsv(const struct rgb *);

void invert_rgb(struct rgb *);
void invert_hsl(struct hsl *);

#ifdef COLOR_CONVERT_IMPLEMENTATION

static float _hue_to_rgb(float p, float q, float t);

struct rgb hsl_to_rgb(float h, float s, float l)
{
    struct rgb color;
    
    if (s == 0)
        color.r = color.g = color.b = l;
    else {
        float q = l < 0.5f ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;

        color.r = _hue_to_rgb(p, q, h + 1/3.f) * 255;
        color.g = _hue_to_rgb(p, q, h) * 255;
        color.b = _hue_to_rgb(p, q, h - 1/3.f) * 255;
    }

    return color;
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

struct rgb hex_to_rgb(int code)
{
    struct rgb color = { code >> 16, code >> 8, code };
    return color;
}

struct hsl rgb_to_hsl(float r, float g, float b)
{
    struct hsl color;
    float max, min;

    r /= 255;
    g /= 255;
    b /= 255;

    max = r > (g > b ? g : b) ? r : g > b ? g : b;
    min = r < (g < b ? g : b) ? r : g < b ? g : b;

    color.h = color.s = color.l = (max + min) / 2;

    if (max == min)
        color.h = color.s = 0;
    else {
        float d = max - min;
        color.s = color.l > 0.5f ? d / (2 - max - min) : d / (max + min);

        if (max == r)
            color.h = (g - b) / d + (g < b ? 6 : 0);
        else if (max == g)
            color.h = (b - r) / d + 2;
        else if (max == b)
            color.h = (r - g) / d + 4;

        color.h /= 6;
    }

    return color;
}

struct hsv rgb2hsv(const struct rgb *color)
{
    float r = color->r / 255.f;
    float g = color->g / 255.f;
    float b = color->b / 255.f;

    float cmax = r > (g > b ? g : b) ? r : g > b ? g : b;
    float cmin = r < (g < b ? g : b) ? r : g < b ? g : b;

    float dif = cmax - cmin;

    struct hsv out;

    out.v = cmax;

    if (dif == 0)
        out.h = 0;
    else if (out.v == r)
        out.h = (g - b) / dif + (g < b ? 6 : 0);
    else if (out.v == g)
        out.h = (b - r) / dif + 2;
    else if (out.v == b)
        out.h = (r - g) / dif + 4;
    out.h /= 6;

    if (out.v == 0)
        out.s = 0;
    else
        out.s = dif / out.v;

    return out;
}

void invert_rgb(struct rgb *color)
{
    color->r = ~color->r;
    color->g = ~color->g;
    color->b = ~color->b;
}

void invert_hsl(struct hsl *color)
{
    color->h += color->h < 0.5f ? 0.5f : -0.5f;
    color->s = 1 - color->s;
    color->l = 1 - color->l;
}

#endif /* COLOR_CONVERT_IMPLEMENTATION */
#endif /* COLOR_CONVERT_H */
