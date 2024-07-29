#ifndef RGBHSL_H
#define RGBHSL_H

typedef struct hsl {
    float h;
    float s;
    float l;
} hsl;

typedef struct rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} rgb;

struct rgb hsl_to_rgb(float h, float s, float l);
struct hsl rgb_to_hsl(float r, float g, float b);

void invert_rgb(struct rgb *);
void invert_hsl(struct hsl *);

#ifdef RGBHSL_IMPLEMENTATION

static float _hue_to_rgb(float p, float q, float t);

struct rgb hsl_to_rgb(float h, float s, float l)
{
    struct rgb color;
    
    if (s == 0)
        color.r = color.g = color.b = l;
    else {
        float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
        float p = 2 * l - q;

        color.r = _hue_to_rgb(p, q, h + 1./3) * 255;
        color.g = _hue_to_rgb(p, q, h) * 255;
        color.b = _hue_to_rgb(p, q, h - 1./3) * 255;
    }

    return color;
}

static float _hue_to_rgb(float p, float q, float t)
{
    if (t < 0)
        t += 1;
    if (t > 1)
        t -= 1;

    if (t < 1./6)
        return p + (q - p) * 6 * t;
    if (t < 1./2)
        return q;
    if (t < 2./3)
        return p + (q - p) * (2./3 - t) * 6;
    return p;
}

struct hsl rgb_to_hsl(float r, float g, float b)
{
    struct hsl color;
    float max, min;

    r /= 255;
    g /= 255;
    b /= 255;

    max = r >= g && r >= b ? r
        : g >= r && g >= b ? g
        : b;
    min = r < g && r < b ? r
        : g < r && g < b ? g
        : b;

    color.h = color.s = color.l = (max + min) / 2;

    if (max == min)
        color.h = color.s = 0;
    else {
        float d = max - min;
        color.s = color.l > 0.5 ? d / (2 - max - min) : d / (max + min);

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

void invert_rgb(struct rgb *color)
{
    color->r = ~color->r;
    color->g = ~color->g;
    color->b = ~color->b;
}

void invert_hsl(struct hsl *color)
{
    color->h += color->h < 0.5f ? 0.5f : -0.5f;
    color->s = 100 - color->s;
    color->l = 100 - color->l;
}

#endif /* RGBHSL_IMPLEMENTATION */
#endif /* RGBHSL_H */
