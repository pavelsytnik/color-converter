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

typedef struct rgba {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} rgba_t;

typedef struct cmyk {
    float c;
    float m;
    float y;
    float k;
} cmyk_t;

int  hsl_valid(const struct hsl  *);
int  hsv_valid(const struct hsv  *);
int cmyk_valid(const struct cmyk *);

void  rgb2hsl (const struct rgb  *in, struct hsl  *out);
void  rgb2hsv (const struct rgb  *in, struct hsv  *out);
void  rgb2cmyk(const struct rgb  *in, struct cmyk *out);
void  rgb2hex (const struct rgb  *in,        int  *out);
void  hsl2rgb (const struct hsl  *in, struct rgb  *out);
void  hsv2rgb (const struct hsv  *in, struct rgb  *out);
void cmyk2rgb (const struct cmyk *in, struct rgb  *out);
void  hex2rgb (const        int  *in, struct rgb  *out);
void  hex2web (const        int  *in,        int  *out);
void  hsl2hsv (const struct hsl  *in, struct hsv  *out);
void  hsv2hsl (const struct hsv  *in, struct hsl  *out);

#define rgb_invert(color) rgb_inverted(color, color)
#define rgb_blend(dst, src) rgb_blended(dst, src, dst)

void rgb_inverted(const struct rgb *in, struct rgb *out);
void rgb_blended(const struct rgb *dst, const struct rgba *src, struct rgb *res);

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

void hex2rgb(const int *in, struct rgb *out)
{
    out->r = (unsigned char) (*in >> 16);
    out->g = (unsigned char) (*in >> 8);
    out->b = (unsigned char) (*in);
}

void hex2web(const int *in, int *out)
{
    unsigned char r = *in >> 16;
    unsigned char g = *in >> 8;
    unsigned char b = *in;

    unsigned char *c = &r;

start:
    if (*c <= 0x19)
        *c = 0x00;
    else if (*c <= 0x4C)
        *c = 0x33;
    else if (*c <= 0x7F)
        *c = 0x66;
    else if (*c <= 0xB2)
        *c = 0x99;
    else if (*c <= 0xE5)
        *c = 0xCC;
    else
        *c = 0xFF;

    if (c == &r) {
        c = &g;
        goto start;
    } else if (c == &g) {
        c = &b;
        goto start;
    }

    *out = r << 16 | g << 8 | b;
}

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

void rgb_inverted(const struct rgb *in, struct rgb *out)
{
    out->r = ~in->r;
    out->g = ~in->g;
    out->b = ~in->b;
}

void rgb_blended(const struct rgb *dst, const struct rgba *src, struct rgb *res)
{
    float a = src->a / 255.f;

    res->r = dst->r * (1 - a) + src->r * a;
    res->g = dst->g * (1 - a) + src->g * a;
    res->b = dst->b * (1 - a) + src->b * a;
}

#undef _min
#undef _max

#endif /* COLOR_CONVERT_IMPLEMENTATION */
#endif /* COLOR_CONVERT_H */
